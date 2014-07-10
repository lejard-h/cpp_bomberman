//
// Cam.cpp for  in /home/lelabo_m/rendu/cpp_bomberman/Bomberman
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Sat Jun  7 17:50:26 2014 Marc Le Labourier
// Last update Sat Jun  7 19:06:36 2014 Marc Le Labourier
//

#include "Settings.hpp"
#include "Cam.hh"

Bomb::GameCam::GameCam()
{
  this->ctor(Cam_o);
  this->_isDestroy = true;
}

void  Bomb::GameCam::Start()
{
  this->InitInput();
  this->_isDestroy = false;
  for (std::map<enum ComponentType, IComponent *>::const_iterator it = this->_components.begin();
       it != this->_components.end(); ++it)
    {
      it->second->Start();
    }
}

Bomb::GameObject        *Bomb::GameCam::Clone() const
{
  return new GameCam();
}

void    Bomb::GameCam::InitInput()
{
  size_t        nb = NB_KEYBOARD - 1;
  CamInputComponent      *input = new CamInputComponent(nb);
  input->AssignEntity(this);
  this->AddComponent(input);
}
