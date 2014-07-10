//
// EventDispatcher.cpp for  in /home/lelabo_m/rendu/cpp_bomberman/GameEngine
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Wed May 21 22:16:12 2014 Marc Le Labourier
// Last update Sat Jun 14 18:42:27 2014 Marc Le Labourier
//

#include <iostream>
#include "EventDispatcher.hh"

Event::EventDispatcher	*G_EvDispatcher = 0;

Event::EventDispatcher::EventDispatcher()
{
  _channelStat[COMMON] = true;
  _channelStat[SYS] = true;
  _channelStat[REPLAY] = true;
  _channelStat[ABS] = true;
  _channel[DEFAULT] = new std::list<ISubscriber*>();
  _channel[ENGINE] = new std::list<ISubscriber*>();
  _channel[AUDIO] = new std::list<ISubscriber*>();
  _channel[GAME] = new std::list<ISubscriber*>();
  _channel[UI] = new std::list<ISubscriber*>();
  _channel[RENDER] = new std::list<ISubscriber*>();
  _channel[EVENT] = new std::list<ISubscriber*>();
  _channel[INPUT] = new std::list<ISubscriber*>();
  _channel[UNKNOW] = new std::list<ISubscriber*>();
  _isInside = false;
}

Event::EventDispatcher::~EventDispatcher()
{
  _channel[DEFAULT]->clear();
  _channel[ENGINE]->clear();
  _channel[AUDIO]->clear();
  _channel[GAME]->clear();
  _channel[UI]->clear();
  _channel[RENDER]->clear();
  _channel[EVENT]->clear();
  _channel[INPUT]->clear();
  _channel[UNKNOW]->clear();
  delete _channel[DEFAULT];
  delete _channel[ENGINE];
  delete _channel[AUDIO];
  delete _channel[GAME];
  delete _channel[UI];
  delete _channel[RENDER];
  delete _channel[EVENT];
  delete _channel[INPUT];
  delete _channel[UNKNOW];
}

void	Event::EventDispatcher::AddSubscriber(EventScope e, ISubscriber* newsub)
{
  bool	islock = false;

  if (!_isInside)
    {
      _isInside = true;
      islock = true;
      _locker.lock();
    }
  if (_channel[e])
    _channel[e]->push_back(newsub);
  if (islock)
    _locker.unlock();
  _isInside = false;
}

void	Event::EventDispatcher::DelSubscriber(EventScope e, ISubscriber* sub)
{
  bool	islock = false;

  if (!_isInside)
    {
      _isInside = true;
      islock = true;
      _locker.lock();
    }
  if (_channel[e])
    _channel[e]->remove(sub);
  if (islock)
    _locker.unlock();
  _isInside = false;
}

bool	Event::EventDispatcher::Channel(ChanLevel chan)
{
  bool	islock = false;

  if (!_isInside)
    {
      _isInside = true;
      islock = true;
      _locker.lock();
    }
  bool state = _channelStat[chan];
  if (islock)
    _locker.unlock();
  _isInside = false;
  return state;
}

void	Event::EventDispatcher::Channel(ChanLevel chan, bool state)
{
  bool	islock = false;

  if (!_isInside)
    {
      _isInside = true;
      islock = true;
      _locker.lock();
    }
  if (chan != ABS)
    _channelStat[chan] = state;
  if (islock)
    _locker.unlock();
  _isInside = false;
}

bool	Event::EventDispatcher::SwitchChannelState(ChanLevel chan)
{
  bool	islock = false;

  if (!_isInside)
    {
      _isInside = true;
      islock = true;
      _locker.lock();
    }
  if (chan != ABS)
    {
      _channelStat[chan] = !_channelStat[chan];
      if (islock)
	_locker.unlock();
      return _channelStat[chan];
    }
  if (islock)
    _locker.unlock();
  _isInside = false;
  return true;
}

// Attention :: we delete ev pass through this function
void	Event::EventDispatcher::SendEvent(Event *ev, ChanLevel lev)
{
  bool	islock = false;

  if (!_isInside)
    {
      _isInside = true;
      islock = true;
      _locker.lock();
    }
  if (_channelStat[lev])
    {
      std::list<ISubscriber *>	*l = _channel[ev->Scope()];
      if (!l)
	{
	  if (islock)
	    _locker.unlock();
	  _isInside = false;
	  return ;
	}
      for (std::list<ISubscriber*>::iterator it = l->begin(); it != l->end(); ++it)
	(*it)->OnEvent(ev->Clone());
    }
  delete ev;
  if (islock)
    _locker.unlock();
  _isInside = false;
}
