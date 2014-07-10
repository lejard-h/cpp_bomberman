//
// SysEvent.hh for  in /home/lelabo_m/rendu/cpp_bomberman/GameEngine
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Sun May 25 16:39:15 2014 Marc Le Labourier
// Last update Tue Jun 10 23:55:26 2014 Marc Le Labourier
//

#ifndef SYSEVENT_HH_
# define SYSEVENT_HH_

#include "KeyboardManager.hh"
#include "XboxManager.hh"
#include "LeapManager.hh"
#include "GraphicContext.hh"
#include "Fonctor.hpp"
#include "Thread.hh"
#include "Sys.hh"

namespace Event
{
  class SysEvent : public Bomb::ISys
  {
  public:
    SysEvent(Graphic::OGLContext*);
    ~SysEvent();
    bool	Init();
    void	Destroy();
    void	Update();
    static void	*MainLoop(void *);
    void	Loop();
    void	OnEvent(Event*);
  private:
    Thread			*_eventThread;
    Graphic::OGLContext		*_ogl;
    gdl::SdlContext		*_sdl;
    gdl::Input			*_input;
    KeyboardManager		_keymanager;
    LeapManager			*_leap;
    XboxManager			*_xbox;
    bool			_isdestroy;
    std::list<Event*>		_events;
    Mutex			_mutex;
  };
}

#endif /* !SYSEVENT_HH_ */
