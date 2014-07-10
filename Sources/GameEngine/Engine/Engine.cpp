//
// ENgine.cpp for  in /home/lelabo_m/rendu/cpp_bomberman/GameEngine
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Thu May 22 12:47:48 2014 Marc Le Labourier
// Last update Sun Jun 15 14:21:42 2014 Marc Le Labourier
//

#include <unistd.h>
#include <iostream>
#include "Engine.hh"
#include "Settings.hpp"
#include "EventDispatcher.hh"

Bomb::Engine::Engine(Graphic::OGLContext *ogl, SysGame::Initializer init,
		     SysGame::Initializer destroy)
{
  _state = SLEEP;
  _enginestate[Event::ENGINERUN] = RUNNING;
  _enginestate[Event::ENGINEPAUSE] = PAUSED;
  _enginestate[Event::ENGINEQUIT] = END;
  _isdestroy = false;
  if (!G_EvDispatcher)
    G_EvDispatcher = new Event::EventDispatcher();
  if (!G_GameSettings)
    G_GameSettings = new Settings::GameContext();
  G_EvDispatcher->AddSubscriber(Event::ENGINE, this);
  Event::SysEvent	*Events = new Event::SysEvent(ogl);
  Audio::SysAudio	*Audio = new Audio::SysAudio(ogl);
  Graphic::SysGraphic	*Render = new Graphic::SysGraphic(ogl);
  Bomb::SysGame		*Game = new Bomb::SysGame(ogl, init, destroy);
  G_Renderer = Render;
  _isInside = false;
  _system.push_front(Events);
  _system.push_front(Audio);
  _system.push_front(Game);
  _system.push_front(Render);
}

Bomb::Engine::~Engine()
{
  if (!_isdestroy)
    Destroy();
  if (G_EvDispatcher)
    {
      delete G_EvDispatcher;
      G_EvDispatcher = 0;
    }
}

void	Bomb::Engine::Init()
{
  for (std::list<ISys *>::iterator it = _system.begin();
   it != _system.end(); ++it)
  {
    if ((*it)->Init() == false)
    {
     std::cerr << "Engine error : fail to initialize a system" << std::endl;
     G_EvDispatcher->SendEvent(new Event::EngineEvent(Event::ENGINEERROR), Event::COMMON);
     G_GameSettings->gameState = Settings::END;
   }
 }
}

void	Bomb::Engine::Update()
{
  for (std::list<ISys *>::iterator it = _system.begin();
       it != _system.end(); ++it)
    (*it)->Update();
}

void	Bomb::Engine::Start()
{
  G_GameSettings->gameState = Settings::RUNNING;
  _state = RUNNING;
  try
  {
    MainLoop();
  }
  catch (std::exception &e)
    {
      std::cerr << "Engine error : fail to initialize a system" << std::endl;
      throw Bomb::EngineException("Engine Quit.");
    }
}

void	   Bomb::Engine::MainLoop()
{
  while (_state == RUNNING || _state == PAUSED)
    {
      _m.lock();
      TreatEvent();
      _m.unlock();
      usleep(5000);
      Update();
    }
  usleep(50000);
}

void	Bomb::Engine::Stop()
{
  _state = END;
  Destroy();
}

void	Bomb::Engine::Destroy()
{
  G_GameSettings->gameState = Settings::END;
  _isdestroy = true;
  for (std::list<ISys *>::iterator it = _system.begin();
       it != _system.end(); ++it)
    {
      (*it)->Destroy();
      delete (*it);
    }
  _system.clear();
  DisplayStatut();
}

void	Bomb::Engine::DisplayStatut()
{
  if (exceptmsg)
    {
      std::cerr << exceptmsg->c_str() << std::endl;
      delete exceptmsg;
      exceptmsg = 0;
    }
}

void	Bomb::Engine::OnEvent(Event::Event* ev)
{
  bool	islock = false;

  if (!_isInside)
    {
      islock = true;
      _m.lock();
    }
  _isInside = true;
  _events.push_back(ev);
  if (islock)
    _m.unlock();
  _isInside = false;
}

bool	Bomb::Engine::EngineEvent(Event::EngineEvent *ev)
{
  Event::EngineSubject value = (Event::EngineSubject)ev->Subject();
  if (value == Event::ENGINERUN || value == Event::ENGINEQUIT)
    _state = (EngineState)_enginestate[value];
  else if (value == Event::ENGINEERROR)
    {
      exceptmsg = new std::string("Engine Error : an error happen in some system");
      _state = END;
      return false;
    }
  if (value == Event::ENGINEPAUSE)
    Pause();
  else if (value == Event::ENGINEQUIT)
    _state = END;
  return true;
}

void	Bomb::Engine::Pause()
{
  G_EvDispatcher->SwitchChannelState(Event::COMMON);
  ListObj                         *MenuList = G_ObjectsContainer->GetObjByTag(Menu_o);
  std::list<IEntity *>::iterator  obj = MenuList->Begin();
  (*obj)->Start();
  if (_state != PAUSED)
    {
      G_GameSettings->gameState = Settings::PAUSED;
      G_EvDispatcher->SendEvent(new Event::GameEvent("", Event::GAMEPAUSE),
				Event::SYS);
      G_EvDispatcher->SendEvent(new Event::AudioEvent(0, 0, 0.5, Audio::PAUSE),
				Event::SYS);
      _state = PAUSED;
      G_EvDispatcher->SendEvent(new Event::GraphicEvent(*obj, Graphic::MESHADD), Event::SYS);
    }
  else
    {
      G_GameSettings->gameState = Settings::RUNNING;
      _state = RUNNING;
      G_EvDispatcher->SendEvent(new Event::GraphicEvent(*obj, Graphic::MESHDEL), Event::SYS);
      G_EvDispatcher->SendEvent(new Event::AudioEvent(0, 0, 0.5, Audio::UNPAUSE),
				Event::SYS);
      G_EvDispatcher->SendEvent(new Event::GameEvent("", Event::GAMEPAUSE),
				Event::SYS);
    }
}

void	Bomb::Engine::KeyboardEvent(Event::KeyboardEvent* ev)
{
  if (ev->data[SDL_QUIT] == true)
    _state = END;
  else if (ev->data[SDLK_ESCAPE] == true)
    Pause();
}

void	Bomb::Engine::TreatEvent()
{
  while (_events.size())
    {
      Event::Event*	ev = _events.front();
      _events.pop_front();

      if (ev->Scope() != Event::ENGINE)
	{
	  delete ev;
	  continue;
	}
      Event::EngineEvent*	ev_engine = dynamic_cast<Event::EngineEvent*>(ev);
      if (ev_engine)
	{
	  if (EngineEvent(ev_engine))
	    return ;
	}
      else
	{
	  Event::KeyboardEvent* ev_input = dynamic_cast<Event::KeyboardEvent*>(ev);
	  if (ev_input)
	    KeyboardEvent(ev_input);
	}
      delete ev;
    }
}
