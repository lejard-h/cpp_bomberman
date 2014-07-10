//
// EventDispatcher.hh for  in /home/lelabo_m/rendu/cpp_bomberman/Engine
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Wed May 21 15:44:13 2014 Marc Le Labourier
// Last update Fri Jun 13 17:09:35 2014 Marc Le Labourier
//

#ifndef EVENTDISPATCHER_HH_
# define EVENTDISPATCHER_HH_

#include <map>
#include <list>
#include "Event.hpp"
#include "Mutex.hh"

namespace Event
{
  enum ChanLevel {COMMON, SYS, REPLAY, ABS}; // ABSOLUTE is always safe

  class ISubscriber
  {
  public:
    virtual		~ISubscriber() {};
    virtual void	OnEvent(Event *) = 0;
  };

  class EventDispatcher
  {
  public:
    EventDispatcher();
    ~EventDispatcher();
    void	AddSubscriber(EventScope, ISubscriber*);
    void	DelSubscriber(EventScope, ISubscriber*);
    bool	SwitchChannelState(ChanLevel);
    void	Channel(ChanLevel, bool);
    bool	Channel(ChanLevel);
    void	SendEvent(Event*, ChanLevel);
  private:
    std::map<ChanLevel, bool>				_channelStat;
    std::map<EventScope, std::list<ISubscriber*>* >	_channel;
    Mutex						_locker;
    bool						_isInside;
  };
}

extern Event::EventDispatcher	*G_EvDispatcher;

#endif /* !EVENTDISPATCHER_HH_ */
