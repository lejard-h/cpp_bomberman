//
// Event.cpp for  in /home/lelabo_m/rendu/cpp_bomberman/Engine
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Wed May 21 14:47:55 2014 Marc Le Labourier
// Last update Thu Jun 12 13:28:18 2014 Marc Le Labourier
//

#include <map>
#include <string>
#include <iostream>
#include "Event.hpp"
#include "Component.hh"

void	Event::DebugEvent(Event e)
{
  std::map<EventScope, std::string>	ScopeId;

  ScopeId[ENGINE] = "ENGINE";
  ScopeId[AUDIO] = "AUDIO";
  ScopeId[RENDER] = "GRAPHIC";
  ScopeId[UI] = "UI";
  ScopeId[GAME] = "GAME";
  std::cout << "Event is " << ScopeId[e.Scope()]
	    << " and subject = " << e.Subject() << std::endl;
}

Event::Event::Event(EventScope scp, size_t subj)
{
  _scope = scp;
  _subject = subj;
}

Event::Event::Event(const Event& ev)
{
  _scope = ev.Scope();
  _subject = ev.Subject();
}

Event::Event	&Event::Event::operator=(const Event& ev)
{
  _scope = ev.Scope();
  _subject = ev.Subject();
  return *this;
}

Event::EventScope	Event::Event::Scope() const
{
  return _scope;
}

void			Event::Event::SetScope(EventScope scp)
{
  _scope = scp;
}

size_t		Event::Event::Subject() const
{
  return _subject;
}

Event::Event*	Event::Event::Clone() const
{
  return (new Event(*this));
}

Event::EngineEvent::EngineEvent(size_t subj) : Event(ENGINE, subj)
{
}

Event::Event*	Event::EngineEvent::Clone() const
{
  return (new EngineEvent(this->Subject()));
}

Event::AudioEvent::AudioEvent(const std::string *p, const std::string *n,
			      float v, size_t subj) : Event(AUDIO, subj), path(p), name(n), volume(v)
{
}

Event::Event*	Event::AudioEvent::Clone() const
{
  return (new AudioEvent(path, name, volume, _subject));
}

Event::GraphicEvent::GraphicEvent(Bomb::IEntity* gameobject, size_t subj)
  : Event(RENDER, subj), obj(gameobject)

{
}

Event::Event*	Event::GraphicEvent::Clone() const
{
  return (new GraphicEvent(this->obj, this->Subject()));
}

Event::AnimeEvent::AnimeEvent(Bomb::IEntity* gameobject, double x, double y, size_t l, size_t subj)
  : GraphicEvent(gameobject, subj), posx(x), posy(y), life(l)
{
}

Event::Event*	Event::AnimeEvent::Clone() const
{
  return (new AnimeEvent(this->obj, this->posx, this->posy, this->life, this->Subject()));
}

Event::UIEvent::UIEvent(size_t subj) : Event(UI, subj)
{
}

Event::Event*	Event::GameEvent::Clone() const
{
  return (new GameEvent(this->msg, Subject()));
}

Event::GameEvent::GameEvent(const std::string& m, size_t subj) : Event(GAME, subj), msg(m)
{
}

Event::DestroyEvent::DestroyEvent(int value) : GameEvent("DestroyEvent", DESTROY), id(value)
{
}

Event::DestroyEvent::DestroyEvent(DestroyEvent const &d) : GameEvent(d)
{
  this->id = d.id;
}

Event::Event  *Event::DestroyEvent::Clone() const
{
  return new DestroyEvent(*this);
}
