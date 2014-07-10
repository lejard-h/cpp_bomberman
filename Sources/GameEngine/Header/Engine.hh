/*
** Engine.hh for Bomberman in /home/lejard_h/rendu/cpp_bomberman/GameEngine
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  mar. mai  20 20:59:48 2014 hadrien lejard
// Last update Fri Jun 13 17:03:39 2014 Marc Le Labourier
*/

#ifndef __ENGINE_HH__
# define __ENGINE_HH__

/*
* TODO:
* class Engine
*/

#include <list>
#include "Sys.hh"
#include "SysEvent.hh"
#include "SysAudio.hh"
#include "SysGame.hh"
#include "SysGraphic.hh"
#include "Exception.hh"

namespace Bomb
{
  class Engine : public Event::ISubscriber
  {
    enum EngineState {SLEEP, RUNNING, PAUSED, END, ERROR};
  private:
    std::list<ISys *>		_system;
    EngineState			_state;
    std::map<int, int>		_enginestate;
    std::list<Event::Event*>	_events;
    Mutex			_m;
    bool			_isdestroy;
    bool			_isInside;

  public:
    Engine(Graphic::OGLContext *, SysGame::Initializer, SysGame::Initializer);
    ~Engine();
    void	Init();
    void	Start();
    void	Update();
    void	OnEvent(Event::Event *);
    void	TreatEvent();
    bool	EngineEvent(Event::EngineEvent*);
    void	KeyboardEvent(Event::KeyboardEvent*);
    void	MainLoop();
    void	Stop();
    void	Destroy();
    void	DisplayStatut();
    void	Pause();
  };
}

#endif /* __ENGINE_HH__ */
