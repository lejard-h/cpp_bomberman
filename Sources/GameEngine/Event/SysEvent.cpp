//
// SysEvent.cpp for  in /home/lelabo_m/rendu/cpp_bomberman/GameEngine
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Sun May 25 16:42:31 2014 Marc Le Labourier
// Last update Sun Jun 15 18:29:37 2014 Marc Le Labourier
//

#include <unistd.h>
#include "SysEvent.hh"
#include "Settings.hpp"
#include "EventDispatcher.hh"

static void	wait_systen()
{
  int	count = 0;
  while (!G_GameSettings && count < 1000)
    {
      usleep(5000);
      ++count;
    }
  usleep(5000);
}

Event::SysEvent::SysEvent(Graphic::OGLContext* ogl)
{
  _ogl = ogl;
  _isdestroy = true;
}

Event::SysEvent::~SysEvent()
{
  if (!_isdestroy)
    Destroy();
}

bool	Event::SysEvent::Init()
{
  _xbox = 0;
  _leap = 0;
  _keymanager.setValue(false);
  _isdestroy = false;
  _eventThread = new Thread(&SysEvent::MainLoop, this);
  _eventThread->run();
  return true;
}

void	Event::SysEvent::Update()
{
  // _mutex.lock();
  // _mutex.unlock();
}

void	Event::SysEvent::Destroy()
{
  if (_isdestroy)
    return ;
  _isdestroy = true;
  try
    {
      _eventThread->join();
      delete _eventThread;
    }
  catch (Thread::ThreadException &e)
    {
      std::cerr << e.what() << std::endl;
    }
  _events.clear();
}

void	*Event::SysEvent::MainLoop(void * param)
{
  SysEvent*	obj = reinterpret_cast<SysEvent*>(param);

  obj->Loop();
  return 0;
}

void	Event::SysEvent::Loop()
{
  _xbox = new XboxManager();
  _leap = new LeapManager();
  _leap->Connect();
  wait_systen();
  while (G_GameSettings && G_GameSettings->gameState != Settings::END)
    {
      if (_ogl->IsInit() && _ogl->IsClose() == false)
	{
	  _sdl = _ogl->GetContext();
	  _input = _ogl->GetInput();
	  _ogl->Lock();
	  _sdl->updateInputs(*_input);
	  _ogl->Unlock();
	  _keymanager.updateValue(*_input);
	  _xbox->Reset();
	  _xbox->Update();
	  if (G_EvDispatcher)
	    {
	      if (_keymanager.isUpdated() == true)
		{
		  G_EvDispatcher->SendEvent(new KeyboardEvent(_keymanager.getKeyboard()), COMMON);
		  KeyboardEvent	*sysev = new KeyboardEvent(_keymanager.getKeyboard());
		  sysev->SetScope(ENGINE);
		  G_EvDispatcher->SendEvent(sysev, SYS);
		}
	      if (_leap->HasUpdate())
		G_EvDispatcher->SendEvent(new LeapEvent(_leap->GetLeapData()), COMMON);
	      if (_xbox->HasUpdate())
		G_EvDispatcher->SendEvent(new XboxEvent(_xbox->GetInput(),
							_xbox->NumJoystick()),
					  COMMON);
	    }
	}
      usleep(5000);
    }
  _leap->Disconnect();
  delete _xbox;
  delete _leap;
}

void	Event::SysEvent::OnEvent(Event *ev)
{
  _mutex.lock();
  _events.push_back(ev);
  _mutex.unlock();
}
