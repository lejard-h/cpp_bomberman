//
// CamInputComponent.cpp for  in /home/lelabo_m/rendu/cpp_bomberman/Bomberman
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Sat Jun  7 14:52:50 2014 Marc Le Labourier
// Last update Sun Jun 15 19:55:42 2014 Marc Le Labourier
//

#include <math.h>
#include "SysGame.hh"
#include "World.hh"
#include "CamInputComponent.hh"
#include "GraphicComponent.hh"

glm::mat3	buildXMatrix(double degree)
{
  double	rad = M_PI * (degree / 180);
  return (glm::mat3(1, 0, 0,  0, cos(rad), -sin(rad), 0, sin(rad), cos(rad)));
}

glm::mat3	buildYMatrix(double degree)
{
  double	rad = M_PI * (degree / 180);
  return (glm::mat3(cos(rad), 0, sin(rad), 0, 1, 0, -sin(rad), 0, cos(rad)));
}

glm::mat3	buildZMatrix(double degree)
{
  double	rad = M_PI * (degree / 180);
  return (glm::mat3(cos(rad), -sin(rad), 0, sin(rad), cos(rad), 0, 0, 0, 1));
}

Bomb::CamInputComponent::CamInputComponent(int slot) : _slot(slot)
{
  this->ctor(CamInput_c);
  size_t  posX = G_GameSettings->map.x;
  size_t  posY = G_GameSettings->map.y;

  ListObj *list_world;
  if (G_ObjectsContainer && (list_world = G_ObjectsContainer->GetObjByTag(World_o)))
  {
    IEntity *world = list_world->front();
    if (world)
    {
      MapComponent  *map = static_cast<MapComponent *>(world->GetComponent(Map_c));
      if (map)
      {
        posX = map->GetWidth();
        posY = map->GetHeight();
      }
    }
  }
  _ogl = G_Renderer->GetContext();
  _update = false;
  _lastevent = 0;
  _op["up"] = &CamInputComponent::Up;
  _op["down"] = &CamInputComponent::Down;
  _op["left"] = &CamInputComponent::Left;
  _op["right"] = &CamInputComponent::Right;
  _op["back"] = &CamInputComponent::Back;
  _op["front"] = &CamInputComponent::Front;
  _pos = glm::vec3(0, (posX > posY) ?
		   (posX + 5) : (posY + 5), 10);
  _dir = glm::vec3(0, 0, 0);
  _up = glm::vec3(0, 1, 0);
}

Bomb::CamInputComponent::~CamInputComponent()
{
  _op.clear();
}

void	Bomb::CamInputComponent::Start()
{
  G_EvDispatcher->AddSubscriber(Event::INPUT, this);
}

glm::mat4	Bomb::CamInputComponent::CalcCam()
{
  return glm::lookAt(_pos, _dir, _up);
}

bool	IsEvent(Event::LeapEvent* ev)
{
  if (!ev->data.isHand)
    return false;
  if (ev->data.roll > 30.0 || ev->data.roll < -30.0)
    return true;
  else if (ev->data.pitch > 30.0 || ev->data.pitch < -30.0)
    return true;
  return false;
}

void	Bomb::CamInputComponent::Update()
{
  while (this->_events.size() && G_GameSettings->cam)
    {
      Event::InputEvent *ev = static_cast<Event::InputEvent *>(this->_events.front());
      Event::LeapEvent*	leapev
	= dynamic_cast<Event::LeapEvent*>(ev);
      this->_events.pop_front();
      if (!ev || (leapev && (leapev->data.isHand == false
			     || IsEvent(leapev) == false)))
	{
	  leapev = 0;
	  if (ev)
	    delete ev;
	  continue;
	}
      if (_lastevent)
	delete _lastevent;
      _lastevent = ev;
      break;
    }
  if (!_lastevent)
    return ;
  if (_lastevent->Subject() == Event::KEYBOARD)
    {
      Event::KeyboardEvent*	keyev
	  = dynamic_cast<Event::KeyboardEvent*>(_lastevent);
      if (keyev)
	KeyboardEvent(keyev);
    }
  else if (_lastevent->Subject() == Event::LEAP)
    {
      Event::LeapEvent*	leapev
	= dynamic_cast<Event::LeapEvent*>(_lastevent);
      if (leapev)
	LeapEvent(leapev);
      this->_events.clear();
      delete _lastevent;
      _lastevent = 0;
    }
}

void	Bomb::CamInputComponent::LeapEvent(Event::LeapEvent* ev)
{
  std::string			action;

  _update = false;
  if (ev->data.isHand)
    {
      _update = true;
      if (ev->data.roll > 35.0 || ev->data.roll < -35.0)
	action = (ev->data.roll < 0.0) ? ("left") : ("right");
      else if (ev->data.pitch > 35.0 || ev->data.pitch < -35.0)
	action = (ev->data.pitch > 0.0) ? ("up") : ("down");
      if (this->_op.find(action) != this->_op.end())
	(this->*_op[action])();
    }
  if (_update)
    {
      _ogl->Lock();
      glm::mat4	vec = this->CalcCam();
      _ogl->SetCamTransfo(vec);
      _ogl->AskCamUpdate();
      _ogl->Unlock();
    }
}

void	Bomb::CamInputComponent::KeyboardEvent(Event::KeyboardEvent* ev)
{
  for (std::map<int, std::string>::iterator it
  	 = G_GameSettings->cam->keyconf.begin();
       it != G_GameSettings->cam->keyconf.end();
       ++it)
    {
      int   key = it->first;
      std::string action = it->second;
      keyMap_itConst        it_key = ev->data.find(key);
      if (it_key != ev->data.end() && it_key->second == true)
  	{
  	  _update = true;
  	  if (this->_op.find(action) != this->_op.end())
  	    (this->*_op[action])();
  	}
    }
  if (_update)
    {
      _ogl->Lock();
      _update = false;
      glm::mat4	vec = this->CalcCam();
      _ogl->SetCamTransfo(vec);
      _ogl->AskCamUpdate();
      _ogl->Unlock();
    }
}

int	Bomb::CamInputComponent::GetSlot() const
{
  return this->_slot;
}

double	Bomb::CamInputComponent::GetTime()
{
  double	time;

  _ogl->Lock();
  gdl::Clock*	clock = _ogl->GetClock();
  time = clock->getElapsed();
  _ogl->Unlock();
  return time;
}

void	Bomb::CamInputComponent::Up()
{
  glm::vec3 vec = buildXMatrix(-3.0 * GetTime()) * glm::vec3(0, 0, 1);
  _pos -= vec;
  if (_pos.z == 0)
    _pos.z = 1;
}

void	Bomb::CamInputComponent::Down()
{
  glm::vec3 vec = buildXMatrix(3.0 * GetTime()) * glm::vec3(0, 0, 1);
  _pos += vec;
}

void	Bomb::CamInputComponent::Left()
{
  _pos = buildYMatrix(60.0 * GetTime()) * _pos;
}

void	Bomb::CamInputComponent::Right()
{
  _pos = buildYMatrix(-60.0 * GetTime()) * _pos;
}

void	Bomb::CamInputComponent::Back()
{
  _pos += glm::vec3(0, 20.0 * GetTime(), 0);
}

void	Bomb::CamInputComponent::Front()
{
  _pos -= glm::vec3(0, 20.0 * GetTime(), 0);
}
