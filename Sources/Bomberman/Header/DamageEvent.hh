/*
** DamageEvent.hh for Bomberman in /home/lejard_h/cpp_bomberman/Bomberman/Header
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  dim. juin  08 00:22:14 2014 hadrien lejard
// Last update Tue Jun 10 23:32:37 2014 Marc Le Labourier
*/

#ifndef __DAMAGEEVENT_HH__
#define __DAMAGEEVENT_HH__

#include "Event.hpp"

namespace Event
{
	class DamageEvent : public GameEvent
	{
	public:
		DamageEvent(int damage, int id, int);
		DamageEvent(DamageEvent const &);
		~DamageEvent();
		int			id;
		int			damage;
		int			sender;
		Event	*Clone() const;
	};
}

#endif
