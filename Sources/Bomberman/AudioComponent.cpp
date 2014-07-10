//
// AudioComponent.cpp for  in /home/lelabo_m/rendu/cpp_bomberman/Bomberman
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Thu May 29 17:12:47 2014 Marc Le Labourier
// Last update Sun Jun 15 15:08:42 2014 Marc Le Labourier
//

#include <iostream>
#include "AudioComponent.hh"
#include "Event.hpp"
#include "SysAudio.hh"

Bomb::AudioComponent::AudioComponent(int chan = (int)Event::COMMON)
{
  _chan = chan;
  this->ctor(Audio_c);
  if (G_EvDispatcher)
    G_EvDispatcher->AddSubscriber(Event::GAME, this);
  _isdestroy = false;
  _isInside = false;
}

Bomb::AudioComponent::~AudioComponent()
{
  if (!_isdestroy)
    Destroy();
}

void        Bomb::AudioComponent::Start()
{
  bool	islock = false;

  if (!_isInside)
    {
      _isInside = true;
      islock = true;
      _mutex.lock();
    }
  for (std::map<std::string*, std::string*>::iterator it = _sound.begin();
       it != _sound.end(); ++it)
    {
      if (G_EvDispatcher)
	G_EvDispatcher->SendEvent(new Event::AudioEvent(it->second, it->first,
							G_GameSettings->volume,
							Audio::LOAD),
				  (Event::ChanLevel)_chan);
    }
  if (islock)
    _mutex.unlock();
  _isInside = false;
}

void        Bomb::AudioComponent::OnEvent(Event::Event *ev)
{
  bool	islock = false;

  if (!_isInside)
    {
      _isInside = true;
      islock = true;
      _mutex.lock();
    }
  _events.push_back(ev);
  if (islock)
    _mutex.unlock();
  _isInside = false;
}

void        Bomb::AudioComponent::Update()
{
  bool	islock = false;

  if (!_isInside)
    {
      _isInside = true;
      islock = true;
      _mutex.lock();
    }
  while (_events.size())
    {
      Event::Event *ev = _events.front();
      if (ev->Subject() == Event::PLAYSOUND)
	{
	  Event::GameEvent	*Gev = dynamic_cast<Event::GameEvent *>(ev);
	  if (Gev)
	    if (PlaySound(&Gev->msg))
	      std::cerr << "Warning : this song could't be played!" << std::endl;
	}
      _events.pop_front();
    }
  if (islock)
    _mutex.unlock();
  _isInside = false;
}

void        Bomb::AudioComponent::Destroy()
{
  _isdestroy = true;
  if (_sound.size())
    {
      for (std::map<std::string*, std::string*>::const_iterator it = _sound.begin();
	   it != _sound.end(); ++it)
	{
	  delete it->first;
	  delete it->second;
	}
      _sound.clear();
    }
}

void        Bomb::AudioComponent::dump() const
{
  std::cout << "AudioComponent :" << std::endl;
  for (std::map<std::string*, std::string*>::const_iterator it = _sound.begin();
       it != _sound.end(); ++it)
    std::cout << " -" << it->first << " : " << it->second << std::endl;
}

void	Bomb::AudioComponent::AddSound(std::string* path, std::string* name)
{
  _sound[name] = path;
}

bool	Bomb::AudioComponent::PlaySound(std::string* name, double volume)
{
  if (!G_EvDispatcher)
    return false;
  for (std::map<std::string*, std::string*>::iterator it = _sound.begin();
       it != _sound.end(); ++it)
    {
      if (name == it->first)
	{
	  G_EvDispatcher->SendEvent(new Event::AudioEvent(it->second, name, volume, Audio::PLAY),
				    (Event::ChanLevel)_chan);
	  return true;
	}
    }
  return false;
}
