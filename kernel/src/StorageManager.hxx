/*
** Interface file for StorageManager module
**
**
**
** exa
**
*/

#ifndef StorageManager_Interface
#define StorageManager_Interface 1

#include "General.hxx"
#include "VR.hxx"
#include "DPtr.hxx"

	// again VC5 cannot handle nested classes!!
	struct PageTableEntry {
		DPtr sop_instance; // reflective
		int last_referenced; // when the instance has last been referenced
		SOP* address; // ptr to SOP instance in memory or NULL
		int size; // approximate size of object
		bool persistent; // is this object persistent
	};


typedef map<UI, PageTableEntry> PageTable;
typedef map<SOP*, PageTableEntry*> InvertedPageTable;

// Primitive virtual memory manager
class StorageManager
{
public:
	enum {megabyte = 1024*1024};

	StorageManager();

	void init_class();
	void sync();
	bool check_instance(const UI &);
	bool instance_in_memory(SOP*);
	bool instance_in_memory(SOP*, UI &);
	UI gen_instance_uid();
	PageTableEntry & sel_instance_page(const UI &);
	void make_reference(PageTableEntry&);
	void declare(const UI& instance_id);
	SOP& load(PageTableEntry&);
	void store(PageTableEntry& page);
	void make_transient_instance(SOP&);
	void pre_make_persistent_instance(void*, const UI&);
	void make_persistent_instance(SOP&);
	void remove_instance(SOP&);

protected:
	bool can_load(PageTableEntry&);
	bool can_load(int size);
	void claim_storage(PageTableEntry& page, unsigned int size);
	void swap_lru();
	void swap(PageTableEntry& page);
	PageTableEntry* find_lru();

	PageTable page_table; // page table for SOP instances
        friend class Type_Query;
	InvertedPageTable inverted_page_table;
	int reference_counter;
	int disk_capacity;
	int memory_capacity;
	int memory_usage; // approximate usage
};

#endif
