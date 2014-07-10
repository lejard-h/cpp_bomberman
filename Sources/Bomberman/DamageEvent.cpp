/*
** DamageEvent.cpp for Bomberman in /home/lejard_h/cpp_bomberman/Bomberman
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  dim. juin  08 00:24:21 2014 hadrien lejard
// Last update Tue Jun 10 23:32:26 2014 Marc Le Labourier
*/

#include "DamageEvent.hh"

Event::DamageEvent::DamageEvent(int dam, int i, int i2) : GameEvent("DamageEvent", DAMAGE),  id(i), damage(dam), sender(i2)
{
}

Event::DamageEvent::DamageEvent(DamageEvent const &e) : GameEvent(e)
{
	this->sender = e.sender;
	this->id = e.id;
	this->damage = e.damage;
}

Event::Event	*Event::DamageEvent::Clone() const
{
	return new DamageEvent(*this);
}

Event::DamageEvent::~DamageEvent()
{
}
