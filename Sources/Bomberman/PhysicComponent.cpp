/*
** PhysicComponent.cpp for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Bomberman
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  mar. mai  27 13:48:01 2014 hadrien lejard
// Last update Wed Jun 11 00:51:26 2014 Marc Le Labourier
*/

#include "PhysicComponent.hh"

Bomb::PhysicComponent::PhysicComponent(double hitbox)
  :  _hitbox(hitbox), _velocity(0.0f), _velocityBonus(1.0)
{
  this->ctor(Physics_c);
}

void	Bomb::PhysicComponent::Update()
{
  if (this->_velocity > 0.0f && this->GetParent()->HasComponent(Position_c))
  {
    PositionComponent *pos
      = static_cast<PositionComponent *>(this->GetParent()->GetComponent(Position_c));
    ListObj  *list_world = G_ObjectsContainer->GetObjByTag(World_o);
    World	*world;

    if (list_world && (world = static_cast<World *>(list_world->front())) && pos)
    {
      double	new_x = pos->GetPosition(PositionComponent::X);
      double	new_y = pos->GetPosition(PositionComponent::Y);

      this->GetNewPosition(&new_x, &new_y, pos->GetRotation());

      if (!world->Collider(this->GetParent(), new_x, new_y))
      {
        pos->SetPosition(new_x, new_y);
      }
    }
  }
  this->_velocity = 0.0f;
}

void	Bomb::PhysicComponent::SetVelocity(double v)
{
  this->_velocity = v * this->_velocityBonus;
  this->_velocityBonus = 1.0;
}

double		Bomb::PhysicComponent::GetVelocity() const
{
  return this->_velocity;
}

void	Bomb::PhysicComponent::GetNewPosition(double *x, double *y, double rotation) const
{
  double	tmp_x = std::cos(std::abs(RAD(rotation))) * std::abs(this->_velocity);
  double	tmp_y = std::sin(std::abs(RAD(rotation))) * std::abs(this->_velocity);

  *x += tmp_x;
  *y += tmp_y;
}

double Bomb::PhysicComponent::GetHitbox() const
{
  return this->_hitbox;
}

void  Bomb::PhysicComponent::SetVelocityBonus(double b)
{
  this->_velocityBonus = b;
}
