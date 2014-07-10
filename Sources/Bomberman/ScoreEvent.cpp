/*
** ScoreEvent.cpp for Bomberman in /home/lejard_h/cpp_bomberman/Bomberman
**
** Made by hadrien lejard         
** Login   <lejard_h@epitech.net>
**
** Started on  mer. juin  11 00:32:15 2014 hadrien lejard         
** Last update mer. juin  11 00:32:15 2014 hadrien lejard         
*/

#include "ScoreEvent.hh"

Event::ScoreEvent::ScoreEvent(enum ScoreAction a, int i, int t) : GameEvent("ScoreEvent", SCORE),  action(a), id(i), targetId(t)
{
	this->action = a;
	this->id = i;
	this->targetId = t;
}

Event::ScoreEvent::ScoreEvent(ScoreEvent const &c) : GameEvent(c)
{
	this->action = c.action;
	this->id = c.id;
	this->targetId = c.targetId;
}

Event::Event	*Event::ScoreEvent::Clone() const
{
	return new ScoreEvent(*this);
}

Event::ScoreEvent::~ScoreEvent()
{
}