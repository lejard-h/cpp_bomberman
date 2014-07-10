//
// LeapManager.hh for  in /home/lelabo_m/Bin/LEAP/LeapDeveloperKit/LeapSDK/samples
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Sun Jun  8 19:16:42 2014 Marc Le Labourier
// Last update Sat Jun 14 10:59:11 2014 Marc Le Labourier
//

#ifndef LEAPMANAGER_HH_
# define LEAPMANAGER_HH_

#include <map>
#include "Event.hpp"
#include "Leap.h"

namespace Event
{
  enum LeapGesture { NOGESTURE, CIRCLE, INVCIRCLE, SWIPE, KEYTAP, SCREENTAP };

  struct LeapData
  {
    bool		isHand;
    double		pitch;
    double		roll;
    double		yam;
    LeapGesture		gesture;
  };

  class LeapListener : public Leap::Listener
  {
  public:
    LeapListener();
    ~LeapListener();
    virtual void onInit(const Leap::Controller&);
    virtual void onConnect(const Leap::Controller&);
    virtual void onDisconnect(const Leap::Controller&);
    virtual void onExit(const Leap::Controller&);
    virtual void onFrame(const Leap::Controller&);
    virtual void onFocusGained(const Leap::Controller&);
    virtual void onFocusLost(const Leap::Controller&);
    // Add for the Manager
  private:
    std::map<int, LeapGesture>	_gesturemap;
    bool			_update;
    bool			_isHand;
    double			_pitch;
    double			_roll;
    double			_yam;
    LeapGesture			_gesture;
  public:
    void			Reset();
    bool			HasUpdate();
    LeapData			GetData();
  };

  class LeapManager
  {
  public:
    LeapManager();
    void		Connect();
    void		Disconnect();
    bool		HasUpdate();
    LeapData		GetLeapData();
    static void		DebugData(LeapData);
  private:
    bool			_isConnected;
    LeapListener		_listener;
    Leap::Controller		_ctrl;
  };

  class LeapEvent : public InputEvent
  {
  public:
    LeapEvent(LeapData d, size_t subj = LEAP) : InputEvent(subj), data(d)
    {
    }

    virtual Event*              Clone() const
    {
      return (new LeapEvent(data, Subject()));
    }

    LeapData	data;
  };

}

#endif /* !LEAPMANAGER_HH_ */
