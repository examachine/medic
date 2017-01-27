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
#include "SOPClasses.hxx"

bool PrintServer::own_service(const UI& class_id)
{
	return ( (class_id == BasicFilmSessionSOPClass::UID) ||
					 (class_id == BasicFilmBoxSOPClass::UID) ||
					 (class_id == BasicGrayscaleImageBoxSOPClass::UID) ||
					 (class_id == BasicColorImageBoxSOPClass::UID)
					);
}

void PrintServer::serve_naction(const DPtr ptr, unsigned short action_type)
{
	if (ptr.class_id == BasicFilmSessionSOPClass::UID) {
	}
	else
	if (ptr.class_id == BasicFilmBoxSOPClass::UID) {
	}
	else
	if (ptr.class_id == BasicGrayscaleImageBoxSOPClass::UID) {
	}
	else
	if (ptr.class_id == BasicFilmSessionSOPClass::UID) {
	}
}
