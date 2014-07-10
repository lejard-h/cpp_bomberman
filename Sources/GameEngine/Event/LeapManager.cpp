//
// Sample.cpp for  in /home/lelabo_m/Bin/LEAP/LeapDeveloperKit/LeapSDK/samples
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Sun Jun  8 21:12:37 2014 Marc Le Labourier
// Last update Sat Jun 14 14:59:13 2014 Marc Le Labourier
//

#include "LeapManager.hh"

Event::LeapListener::LeapListener()
{
  _gesturemap[Leap::Gesture::TYPE_CIRCLE] = CIRCLE;
  _gesturemap[Leap::Gesture::TYPE_KEY_TAP] = KEYTAP;
  _gesturemap[Leap::Gesture::TYPE_SCREEN_TAP] = SCREENTAP;
  _gesturemap[Leap::Gesture::TYPE_SWIPE] = SWIPE;
  _update = false;
  _isHand = false;
  _gesture = NOGESTURE;
}

Event::LeapListener::~LeapListener()
{
  _gesturemap.clear();
}

void	Event::LeapListener::onInit(const Leap::Controller&)
{
}

void	Event::LeapListener::onConnect(const Leap::Controller& controller)
{
  controller.enableGesture(Leap::Gesture::TYPE_CIRCLE);
  controller.enableGesture(Leap::Gesture::TYPE_KEY_TAP);
  controller.enableGesture(Leap::Gesture::TYPE_SCREEN_TAP);
  controller.enableGesture(Leap::Gesture::TYPE_SWIPE);
}

void	Event::LeapListener::onDisconnect(const Leap::Controller&)
{
}

void	Event::LeapListener::onExit(const Leap::Controller&)
{
}

void	Event::LeapListener::onFrame(const Leap::Controller& controller)
{
  const Leap::Frame frame = controller.frame();
  // HAND
  _isHand = false;
  if (!frame.hands().isEmpty())
    {
      if (!_isHand)
	_update = true;
      _isHand = true;
      const Leap::Hand hand = frame.hands()[0];
      const Leap::Vector normal = hand.palmNormal();
      const Leap::Vector direction = hand.direction();

      double p = direction.pitch() * Leap::RAD_TO_DEG;
      double r = normal.roll() * Leap::RAD_TO_DEG;
      double y = direction.yaw() * Leap::RAD_TO_DEG;
      if (p != _pitch || r != _roll || _yam != y)
	_update = true;
      _pitch = p;
      _roll = r;
      _yam = y;
    }

  // GESTURES
  LeapGesture lastg = _gesture;
  _gesture = NOGESTURE;
  const Leap::GestureList gestures = frame.gestures();
  for (int g = 0; g < gestures.count(); ++g)
    {
      Leap::Gesture gesture = gestures[g];
      if (_gesturemap.find(gesture.type()) != _gesturemap.end())
	_gesture = _gesturemap[gesture.type()];
      if (_gesture == CIRCLE)
	{
	  Leap::CircleGesture circle = gesture;
	  if (!(circle.pointable().direction().angleTo(circle.normal()) <= Leap::PI/4))
	    _gesture = INVCIRCLE;
	}
    }
  if (lastg != _gesture)
    _update = true;
}

void	Event::LeapListener::onFocusGained(const Leap::Controller&)
{
  std::cout << "Focus Gained" << std::endl;
}

void	Event::LeapListener::onFocusLost(const Leap::Controller&)
{
  std::cout << "Focus Lost" << std::endl;
}

bool	Event::LeapListener::HasUpdate()
{
  return _update;
}

void	Event::LeapListener::Reset()
{
  _update = false;
}

Event::LeapData	Event::LeapListener::GetData()
{
  LeapData	data;

  data.isHand = _isHand;
  data.pitch = _pitch;
  data.roll = _roll;
  data.yam = _yam;
  data.gesture = _gesture;
  return data;
}

Event::LeapManager::LeapManager()
{
  _isConnected = false;
}

void	Event::LeapManager::Connect()
{
  _ctrl.addListener(_listener);
  _isConnected = true;
}

void	Event::LeapManager::Disconnect()
{
  _ctrl.removeListener(_listener);
  _isConnected = false;
}

bool	Event::LeapManager::HasUpdate()
{
  if (!_isConnected)
    return false;
  return _listener.HasUpdate();
}

Event::LeapData	Event::LeapManager::GetLeapData()
{
  return _listener.GetData();
}

void	Event::LeapManager::DebugData(LeapData data)
{
  std::map<int, std::string>	debug;

  debug[NOGESTURE] = "No gesture";
  debug[CIRCLE] = "Circle clockwise";
  debug[INVCIRCLE] = "Circle counterclockwise";
  debug[SWIPE] = "Swipe";
  debug[KEYTAP] = "Key tap";
  debug[SCREENTAP] = "Screen tap";
  if (data.isHand)
    {
      std::cout << "pitch: " << data.pitch
		<< " roll: " << data.roll
		<< " yam: " << data.yam << std::endl;
      std::cout << "Gesture : " << debug[data.gesture] << std::endl;
    }
  else
    std::cout << "No hand detect by leap" << std::endl;
}
