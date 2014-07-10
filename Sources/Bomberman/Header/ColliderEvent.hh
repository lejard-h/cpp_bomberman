/*
** ColliderEvent.hh for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Bomberman/Header
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  dim. juin  08 18:00:38 2014 hadrien lejard
// Last update Tue Jun 10 23:29:35 2014 Marc Le Labourier
*/

#ifndef __COLLIDEEVENT_HH__
#define __COLLIDEEVENT_HH__

#include "Event.hpp"

namespace Event
{
	class CollideEvent : public GameEvent
	{
	public:
		CollideEvent(int, int, size_t, size_t);
		CollideEvent(CollideEvent const &);
		Event	*Clone() const;
		~CollideEvent();

		int			id1;
		int			id2;
		size_t		posX;
		size_t		posY;
	};
}

#endif
