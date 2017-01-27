/*
** Interface file for module
**
**
**
** exa
**
*/

#ifndef PrintManagement_Interface
#define PrintManagement_Interface 1

/*
class PrintClient
{
	void n_action
};
*/

class PrintServer
{
public:
	bool own_service(const UI& class_ui);
	void serve_naction(const DPtr ptr, unsigned short action_type);
};

#endif
