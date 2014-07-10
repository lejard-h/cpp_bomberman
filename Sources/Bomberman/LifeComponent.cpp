/*
** LifeComponent.cpp for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Bomberman
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  dim. mai  25 14:43:50 2014 hadrien lejard
// Last update Thu Jun 12 01:05:30 2014 Marc Le Labourier
*/

#include "ScoreEvent.hh"
#include "Event.hpp"
#include "LifeComponent.hh"
#include "ScoreEvent.hh"

Bomb::LifeComponent::LifeComponent() : _life(0), _maxLife(0)
{
	this->ctor(Life_c);
	this->isDead = false;
}

Bomb::LifeComponent::LifeComponent(int life, int maxLife) : _life(life), _maxLife(maxLife)
{
	this->ctor(Life_c);
	this->isDead = false;
}

void	Bomb::LifeComponent::dump() const
{
  std::cout << "LifeComponent (" << this->_life << ")" << std::endl;
}

int		Bomb::LifeComponent::GetLife() const
{
	return this->_life;
}

void	Bomb::LifeComponent::Damage(int damage)
{
  this->_life -= damage;
  if (this->_life < 0)
    this->_life = 0;
}

void	Bomb::LifeComponent::Heal(int heal)
{
  this->_life += heal;

  if (this->_maxLife != 0 && this->_life > (int) this->_maxLife)
    this->_life = this->_maxLife;
}

void  Bomb::LifeComponent::SetLife(int life)
{
  this->_life = life;
}

void	Bomb::LifeComponent::SetMaxLife(unsigned int max)
{
  this->_maxLife = max;
}

unsigned int	Bomb::LifeComponent::GetMaxLife() const
{
  return this->_maxLife;
}

void	Bomb::LifeComponent::Respawn()
{
  this->_life = this->_maxLife;
  this->isDead = false;
}

void	Bomb::LifeComponent::Update()
{
  if (this->_life <= 0 && !this->isDead)
  {
    if (this->GetParent())
    {
      G_EvDispatcher->SendEvent(new Event::DestroyEvent(this->GetParent()->GetId()),
        Event::COMMON);
      this->isDead = true;
    }
  }
}
