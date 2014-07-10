/*
** ScoreEvent.hh for Bomberman in /home/lejard_h/cpp_bomberman/Bomberman/Header
**
** Made by hadrien lejard         
** Login   <lejard_h@epitech.net>
**
** Started on  mer. juin  11 00:27:21 2014 hadrien lejard         
** Last update mer. juin  11 00:27:21 2014 hadrien lejard         
*/

#ifndef __SCOREEVENT_HH__
#define __SCOREEVENT_HH__

#include "EventDispatcher.hh"

namespace Event
{

	enum ScoreAction { DamageScoring, KillTargetScoring, TakeDamageScoring, DeathScoring, WinGame};

	class ScoreEvent : public GameEvent
	{
	public:
		ScoreEvent(enum ScoreAction, int id, int targetID = -1);
		ScoreEvent(ScoreEvent const &);
		
		Event	*Clone() const;
		~ScoreEvent();

		enum ScoreAction	action;
		int					id;
		int					targetId;

	};

}

#endif