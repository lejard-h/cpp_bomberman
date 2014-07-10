//
// XboxManager.cpp for  in /home/lelabo_m/rendu/cpp_bomberman/XboxController
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Sun Jun  8 16:06:44 2014 Marc Le Labourier
// Last update Sun Jun 15 18:38:22 2014 Marc Le Labourier
//

#include <iostream>
#include <unistd.h>
#include "XboxManager.hh"

Event::XboxManager::XboxManager()
{
  if (SDL_WasInit(SDL_INIT_JOYSTICK))
    SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
  SDL_InitSubSystem(SDL_INIT_JOYSTICK);
  SDL_JoystickEventState(SDL_ENABLE);
  _num = SDL_NumJoysticks();
  for (size_t x = 0; x < _num; ++x)
    {
      usleep(500000);
      std::vector<int>	*buttons = new std::vector<int>();
      for (size_t i = 0; i < XBOX_BUTTON; ++i)
	buttons->push_back(0);
      _buttons.push_back(buttons);
      _update.push_back(false);
      _joysticks.push_back(SDL_JoystickOpen(x));
    }
  _CorresHat.push_back(-1);	//0
  _CorresHat.push_back(90);	//1
  _CorresHat.push_back(0);	//2
  _CorresHat.push_back(45);	//3
  _CorresHat.push_back(270);	//4
  _CorresHat.push_back(-1);	//5
  _CorresHat.push_back(315);	//6
  _CorresHat.push_back(-1);	//7
  _CorresHat.push_back(180);	//8
  _CorresHat.push_back(135);	//9
  _CorresHat.push_back(-1);	//10
  _CorresHat.push_back(-1);	//11
  _CorresHat.push_back(225);	//12
}

Event::XboxManager::~XboxManager()
{
  // XBOX : NumJoystick fail, it return 2 when 1 is connected.
  // for (size_t x = 0; x < _num; ++x)
  //   SDL_JoystickClose(_joysticks[x]);
  _joysticks.clear();
  _buttons.clear();
  _CorresHat.clear();
  _update.clear();
}

size_t	Event::XboxManager::NumJoystick()
{
  return _num;
}

bool	Event::XboxManager::HasUpdate()
{
  for (size_t x = 0; x < _num; ++x)
    {
      if (HasUpdate(x))
	return true;
    }
  return false;
}

bool	Event::XboxManager::HasUpdate(size_t id)
{
  if (id < _num)
    return _update[id];
  return false;
}

void	Event::XboxManager::SetButtons(size_t id, size_t x, int value)
{
  if ((*_buttons[id])[x] != value)
    {
      _update[id] = true;
      (*_buttons[id])[x] = value;
    }
}

int	find_angle(int x, int y)
{
  if (sqrt(pow(x, 2.0) + pow(y, 2.0)) < 6400)
    return 0;
  if (x >= 0)
    {
      if (y >= 0)
	return ((180.0 * atan(y / (double)x)) / M_PI);
      else
	return (360.0 + (180.0 * atan(y / (double)x)) / M_PI);
    }
  else
    {
      if (y >= 0)
	return (180.0 + (180.0 * atan(y / (double)x)) / M_PI);
      else
	return (180.0 + (180.0 * atan(y / (double)x)) / M_PI);
    }
  return 0;
}

void	Event::XboxManager::Update(size_t id)
{
  if (!(id < _num) || _joysticks[id] == 0)
    return ;
  // BUTTON
  for (size_t x = 0; x < 9; ++x)
    {
      int	state = SDL_JoystickGetButton(_joysticks[id], x);
      SetButtons(id, x, state);
    }
  // LT + RT : CALC POWER
  SetButtons(id, LT, SDL_JoystickGetAxis(_joysticks[id], 2));
  SetButtons(id, RT, SDL_JoystickGetAxis(_joysticks[id], 5));
  // STICK1
  int	x1 = SDL_JoystickGetAxis(_joysticks[id], 0);
  int	y1 = SDL_JoystickGetAxis(_joysticks[id], 1);
  SetButtons(id, STICK1, find_angle(x1, y1));
  // STICK2
  int	x2 = SDL_JoystickGetAxis(_joysticks[id], 3);
  int	y2 = SDL_JoystickGetAxis(_joysticks[id], 4);
  SetButtons(id, STICK2, find_angle(x2, y2));
  // HAT
  int	hat = SDL_JoystickGetHat(_joysticks[id], 0);
  SetButtons(id, HAT, _CorresHat[hat]);
}

void	Event::XboxManager::Update()
{
  for (size_t x = 0; x < _num; ++x)
    Update(x);
}

void	Event::XboxManager::Reset()
{
  for (size_t x = 0; x < _num; ++x)
    _update[x] = false;
}

int	Event::XboxManager::GetInput(size_t id, XboxCode code)
{
  if (id < _num || _joysticks[id] != 0)
    return (*_buttons[id])[(int)code];
  return 0;
}

Event::XboxInput*	Event::XboxManager::GetInput()
{
  return &_buttons;
}
