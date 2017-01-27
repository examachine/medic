/*
** Interface file for ImageStacker module
**
**
**
** exa
**
*/

#ifndef DImageStacker_Interface
#define DImageStacker_Interface 1

#ifdef MEDIC_PACS
#include "Message1.h"

class DImageStacker
{
public:
  DImageStacker() : timer_valid(false) { }

  //class SeriesInfo : public CMessage1 {
  //DPtr ptr;
  //};

  typedef map< UI, DPtr > ImageMap;
  typedef map< UI, ImageMap > SeriesMap;
  typedef map< UI, CMessage1* > MessageMap;

  void stack(DPtr&);
	
  SeriesMap series_map;
  MessageMap message_map;

  CWinThread* image_manager;
  bool timer_valid;
  int timer_id;
};

#endif // MEDIC_PACS

#endif
