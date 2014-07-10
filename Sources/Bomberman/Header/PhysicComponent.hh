/*
** PhysicComponent.hh for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Bomberman/Header
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  mar. mai  27 13:37:41 2014 hadrien lejard
// Last update Wed Jun 11 00:51:48 2014 Marc Le Labourier
*/

#ifndef __PHYSICCOMPONENT_HH__
#define __PHYSICCOMPONENT_HH__

#include <cmath>
#include "Component.hh"
#include "MapComponent.hh"
#include "World.hh"

namespace Bomb
{

#define RAD(X)	(X * M_PI / 180.0)

  class PhysicComponent : public BaseComponent
  {
  public:
    PhysicComponent(double hitbox);

    void	Update();

    void	SetVelocity(double);
    void	SetVelocityBonus(double);

    double	GetVelocity() const;
    double	GetHitbox() const;

  private:
    double		_hitbox;
    double		_velocity;
    double		_velocityBonus;
    void	GetNewPosition(double *, double *, double) const;
  };
}

#endif
