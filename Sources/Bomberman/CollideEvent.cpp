/*
** CollideEvent.cpp for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Bomberman
**
** Made by hadrien lejard         
** Login   <lejard_h@epitech.net>
**
** Started on  dim. juin  08 18:02:26 2014 hadrien lejard         
** Last update dim. juin  08 18:02:26 2014 hadrien lejard         
*/

#include "ColliderEvent.hh"

Event::CollideEvent::CollideEvent(int i1, int i2, size_t x, size_t y) : GameEvent("CollideEvent", COLLIDE),  id1(i1), id2(i2), posX(x), posY(y)
{
}

Event::CollideEvent::CollideEvent(CollideEvent const &c) : GameEvent(c)
{
	this->id1 = c.id1;
	this->id2 = c.id2;
	this->posX = c.posX;
	this->posY = c.posY;
}

Event::Event	*Event::CollideEvent::Clone() const
{
	return new CollideEvent(*this);
}

Event::CollideEvent::~CollideEvent()
{
}
