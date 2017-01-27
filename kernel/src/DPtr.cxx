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

DPtr DPtr::Null;


//CODE: A better interface for DPtr
SOP & DPtr::operator *() const
{
	// check validity of class_id 
	if ( (class_id->size()!=0) && (!dicom_app.sops.check_class(class_id)) )
		throw DPtrException("SOP Class unknown");
		
	// find out instance's vm page table entry
	if (! exists() )
		throw DPtrException("SOP Instance not present");

	PageTableEntry & page = dicom_app.storage_manager.sel_instance_page(instance_id);

	SOP* instance_address;
	if ( instance_address = page.address ) { // if in memory
	  //obtain address
		//return *address;
	} else {
	  // bring into memory
		instance_address = &dicom_app.storage_manager.load(page);
	}
		
	// set last reference
	dicom_app.storage_manager.make_reference(page);

	return *instance_address;
}

bool DPtr::exists () const
{
	return ( dicom_app.storage_manager.check_instance(instance_id) );
}
