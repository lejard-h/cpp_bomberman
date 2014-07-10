/*
** SysAudio.cpp for Bomber in /home/thomas_1/Desktop/Projets/Bomberman/cpp_bomberman/GameEngine/Event
**
** Made by Pierre-Yves THOMAS
** Login   <thomas_1@epitech.net>
**
** Started on  Thu May  29 17:31:14 2014 Pierre-Yves THOMAS
// Last update Sat Jun 14 22:09:31 2014 Marc Le Labourier
*/

#include <unistd.h>
#include "SysAudio.hh"
#include "Settings.hpp"
#include "Exception.hh"
#include "EventDispatcher.hh"

static void     wait_system()
{
  int   count = 0;
  while (!G_GameSettings && count < 1000)
    {
      usleep(50000);
      ++count;
    }
}

Audio::SysAudio::SysAudio(Graphic::OGLContext*)
{
  _isdestroy = true;
  _mapSysAudioFunc[LOAD] = &SysAudio::LoadSound;
  _mapSysAudioFunc[PLAY] = &SysAudio::PlaySound;
  _mapSysAudioFunc[PAUSE] = &SysAudio::PauseSound;
  _mapSysAudioFunc[UNPAUSE] = &SysAudio::UnpauseSound;
  _mapSysAudioFunc[UPDATEVOLUME] = &SysAudio::UpdateVolumeSound;
}

Audio::SysAudio::~SysAudio()
{
  if (!_isdestroy)
    Destroy();
}

bool	Audio::SysAudio::Init()
{
   if (!G_EvDispatcher)
     {
       exceptmsg = new std::string("Initialization of Audio sytem failed : No event dispatcher.");
       return false;
     }
  G_EvDispatcher->AddSubscriber(Event::AUDIO, this);
  _playlist = Playlist::getPlaylist();
  if (!_playlist)
     {
       exceptmsg = new std::string("Initialization of Audio sytem failed : No playlist.");
       return false;
     }
  _isdestroy = false;
  _eventThread = new Thread(&SysAudio::MainLoop, this);
  _eventThread->run();
  return true;
}

void	Audio::SysAudio::Update()
{
  // _mutex.lock();
  // _mutex.unlock();
}

void	Audio::SysAudio::Destroy()
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
    }
}

void	*Audio::SysAudio::MainLoop(void * param)
{
  SysAudio*	obj = reinterpret_cast<SysAudio*>(param);

  obj->Loop();
  return 0;
}

void	Audio::SysAudio::Loop()
{
  Event::AudioEvent 	*event;
  EventAudio		value;
  funcSysAudio	func;

  wait_system();
  while (G_GameSettings && G_GameSettings->gameState != Settings::END)
    {
      _mutex.lock();
      while (G_EvDispatcher && _events.size())
    	{
    	  event = dynamic_cast<Event::AudioEvent *>(_events.front());
    	  _events.pop_front();
    	   if (event)
    	     {
    	       value = (EventAudio)(event->Subject());
    	       func = _mapSysAudioFunc[value];
    	       if (func)
    		          (this->*func)(event);
    	       delete event;
    	     }
      }
    _mutex.unlock();
    usleep(5000);
    }
}

void	Audio::SysAudio::OnEvent(Event::Event *ev)
{
  _mutex.lock();
  if (ev)
    _events.push_back(ev);
  _mutex.unlock();
}

bool Audio::SysAudio::LoadSound(const Event::AudioEvent *event)
{
  return(_playlist->loadSound(*event->path, *event->name));
}

bool Audio::SysAudio::PlaySound(const Event::AudioEvent *event)
{
  Sound 	*sound;

  _playlist->playSound(*event->name);
  sound = _playlist->getMusic(*event->name);
  if (sound)
    sound->setVolume(event->volume);
  return true;
}

bool Audio::SysAudio::PauseSound(const Event::AudioEvent *event)
{
  Sound 	*sound;

  if (event->name)
    {
      sound = _playlist->getMusic(*event->name);
      if (sound)
	return(sound->pauseSound());
    }
  else
    {
      _playlist->pausePlaylist();
      return true;
    }
  return (false);
}

bool Audio::SysAudio::UnpauseSound(const Event::AudioEvent *event)
{
  Sound 	*sound;

  if (event->name)
    {
      sound = _playlist->getMusic(*event->name);
      if (sound)
	return(sound->unpauseSound());
    }
  else
    {
      _playlist->unpausePlaylist();
      return true;
    }
  return (false);
}

bool Audio::SysAudio::UpdateVolumeSound(const Event::AudioEvent *event)
{
  Sound 	*sound;

  sound = _playlist->getMusic(*event->name);
  if (sound)
    return(sound->setVolume(event->volume));
  return (false);
}
