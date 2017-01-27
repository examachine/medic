/*
**
** Implementation file for module
**
**
**
** exa
**
*/

#include "KernelInterface.hxx"
#include <File_System>

StorageManager::StorageManager()
  : reference_counter(0), memory_usage(0)
{}

void StorageManager::init_class() {
  // check out the config file
  try {
    ifstream storage_config_file("etc/storage.txt");
			
    storage_config_file >> disk_capacity;
    storage_config_file >> memory_capacity;
    disk_capacity *= megabyte;
    memory_capacity *= megabyte;
			
    // check sane values
			
    storage_config_file.close();
  }
  catch (DException e) {
    e.why();
    dicom_app.exit();
  }
  catch (...) {
    DException err("Error while accessing etc/storage.txt");
    err.why();
    dicom_app.exit();
  }

  if (dicom_app.role == DApplication::viewing_application) {
    // load SOP instances from object-pool
    // determine object-pool contents

#ifdef _MSC_VER
    //CODE: move this functionality to platform!!
    CFileFind finder;
    BOOL bWorking = finder.FindFile( "object-pool/*.*" );
    while (bWorking) {
      bWorking = finder.FindNextFile();
      string filename = (LPCTSTR) finder.GetFileName() ;
      if (filename[0]!='.') {
	declare(filename);
      }
    }
#endif

  }

}


void StorageManager::sync() {
  // Synchronize secondary storage with the first
  map<UI, PageTableEntry>::iterator i, j = page_table.end();
  for ( i = page_table.begin(); i!=j; i++ ) {
    //SOP& sop = i->second.address;
    // KLUDGE --- only if modified
    store(i->second);
  }
}


bool StorageManager::check_instance(const UI &instance_id)
{
  return (page_table.find(instance_id) != page_table.end());
}

bool StorageManager::instance_in_memory(SOP* sop)
{
  return (inverted_page_table.find(sop) != inverted_page_table.end());
}

bool StorageManager::instance_in_memory(SOP* sop, UI &instance_id)
{
  UI& ref_ui = instance_id;
  if ( (instance_id.rep()).empty()) return false;
  PageTable::iterator i = page_table.find(instance_id);
  if (i != page_table.end()) {
    PageTableEntry& page = i->second;
    return (sop == page.address);
  }
  else
    return false;
}

UI StorageManager::gen_instance_uid()
{
  string uid_str = dicom_app.uid_suffix;
  string dot = ".";
#ifdef _MSC_VER
  // CODE: do this in a portable way!!
  // in win 98 there are negative thread id's!
  uid_str += dot + int_to_str(abs(AfxGetThread()->m_nThreadID));
  uid_str += dot + int_to_str(CTime::GetCurrentTime().GetTime());
#endif
  return UI(uid_str);
}

PageTableEntry& StorageManager::sel_instance_page(const UI &instance_id)
{
  return page_table[instance_id];
}

void StorageManager::make_reference(PageTableEntry& page)
{
  page.last_referenced = reference_counter++;
}

bool StorageManager::can_load(PageTableEntry& page)
{
  return can_load(page.size);
}

bool StorageManager::can_load(int size)
{
  return (memory_usage + size <= memory_capacity);
}

void StorageManager::claim_storage(PageTableEntry& page, unsigned int size)
{
  page.size = size;
  memory_usage += size;
}

// load disk page into memory
SOP& StorageManager::load(PageTableEntry& page)
{
  if (check_instance(page.sop_instance.instance_id)) return *page.address;

  while (!can_load(page)) { 		// check available storage
    // swap an SOP onto disk
    swap_lru();
  }
  DFileContext d(dicom_app.sop_filename(page.sop_instance.instance_id));
  SOP& sop =  d.read();
  return sop;
}

// load disk page into memory (which is not in memory)
void StorageManager::declare(const UI& instance_id)
{
  string filename = dicom_app.sop_filename(instance_id);

  // learn file's size
  File file(filename);
  int file_size = file.get_size();

  DFileContext d(filename);
  DFileHeader header;
  d.read_header(header);
  PageTableEntry & new_page = page_table[instance_id];
  new_page.sop_instance = DPtr(header.class_id, header.instance_id);
  new_page.last_referenced = 0;
  new_page.address = NULL;
  claim_storage(new_page, file_size);
  new_page.persistent = true;
}

void StorageManager::swap_lru()
{
  // find out SOP with smallest last_referenced
  PageTableEntry & lru_page = *find_lru();
  // CODE: portable assertions
#ifdef _MSC_VER
  ASSERT(lru_page.persistent);
#endif
  swap(lru_page);
}

void StorageManager::swap(PageTableEntry& page)
{
  store(page);
  delete page.address;
  page.address = NULL;
  memory_usage -= page.size;
}

void StorageManager::store(PageTableEntry& page)
{
  // page it onto disk
  DFileContext d(dicom_app.sop_filename(page.sop_instance.instance_id));
  d.write(*page.address);
}

PageTableEntry* StorageManager::find_lru()
{
  int least = 0x7fffffff;
  PageTableEntry* lru_page = NULL;
  map<UI, PageTableEntry>::iterator i, j = page_table.end();
  for ( i = page_table.begin(); i!=j; i++ )
    if (i->second.address &&
	i->second.persistent &&
	i->second.last_referenced < least) {
      least = i->second.last_referenced;
      lru_page = &(i->second);
    }
  return lru_page;
}

void StorageManager::make_transient_instance(SOP& sop)
{
  sop.mod_instance_id( gen_instance_uid() );
  const UI& instance_id = sop.sel_instance_id();
  PageTableEntry & new_page = page_table[instance_id];
  new_page.sop_instance.class_id = sop.sel_class_id();
  new_page.sop_instance.instance_id = instance_id;
  new_page.last_referenced = 0;
  new_page.address = &sop;
  new_page.size = 64;
  new_page.persistent = false;
  inverted_page_table[&sop] = &new_page;
}

void StorageManager::pre_make_persistent_instance(void* sop, const UI& instance_id)
{
  // declare a new sop instance
  PageTableEntry & new_page = page_table[instance_id];
  new_page.sop_instance.instance_id = instance_id;
  new_page.address = (SOP*)sop;
  inverted_page_table[(SOP*)sop] = &new_page;
}

void StorageManager::make_persistent_instance(SOP& sop)
{
  //PageTableEntry& page = page_table[sop.sel_instance_id()];
  PageTableEntry& page = *inverted_page_table[&sop];
  page.sop_instance.class_id = sop.sel_class_id();
  page.last_referenced = 0;
  page.address = &sop;
  page.size = 64;
  memory_usage += page.size;
  page.persistent = true;
  sop.mod_instance_id(page.sop_instance.instance_id);
  inverted_page_table.erase(&sop);
}

void StorageManager::remove_instance(SOP& sop)
{
  if (sop.prototype) return;
  // find the SOP instance
  map<UI, PageTableEntry>::iterator i =
    page_table.find(sop.sel_instance_id());

#ifdef _MSC_VER
  // CODE: use nana, do something, make these portable!
  ASSERT( i != page_table.end() );
#endif

  if (i->second.persistent) {
    memory_usage -= i->second.size;
    // remove file from disk
#ifdef _MSC_VER
    CFile::Remove(dicom_app.sop_filename(sop.sel_instance_id()).c_str());
#endif
  }
  page_table.erase(i);

  // remove from the inverted page table
  InvertedPageTable::iterator j = inverted_page_table.find(&sop);
#ifdef _MSC_VER
  ASSERT( j != inverted_page_table.end() );
#endif
  inverted_page_table.erase(j);
}
