//
// Event.hh for  in /home/lelabo_m/rendu/cpp_bomberman/Engine
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Wed May 21 14:43:33 2014 Marc Le Labourier
// Last update Thu Jun 12 11:33:26 2014 Marc Le Labourier
//

#ifndef EVENT_HH_
# define EVENT_HH_

#include <cstdlib>
#include <string>
#include "Prototype.hh"

namespace Bomb
{
  class IEntity;
}

namespace Event
{
  enum EventScope {DEFAULT, ENGINE, AUDIO, GAME, UI, RENDER, EVENT, INPUT, UNKNOW};

  class Event : public Pattern::IPrototype<Event>
  {
  public:
    Event(EventScope scp = DEFAULT, size_t subj = 0);
    Event(const Event&);
    Event&	operator=(const Event&);
    virtual	~Event() {};
    virtual	Event*	Clone() const;
    EventScope	Scope() const;
    void	SetScope(EventScope);
    size_t	Subject() const;
  protected:
    EventScope	_scope;
    size_t	_subject;
  };

  enum EngineSubject {ENGINERUN, ENGINEPAUSE, ENGINEQUIT, ENGINEERROR};

  class EngineEvent : public Event
  {
  public:
    EngineEvent(size_t subj = 0);
    ~EngineEvent() {};
    Event*			Clone() const;
  };

  class AudioEvent : public Event
  {
  public:
    AudioEvent(const std::string *p, const std::string *n, float v, size_t subj = 0);
    ~AudioEvent() {};
    Event*			Clone() const;
    const std::string		*path;
    const std::string		*name;
    float		volume;
  };

  class GraphicEvent : public Event
  {
  public:
    GraphicEvent(Bomb::IEntity*, size_t subj = 0);
    ~GraphicEvent() {};
    Event*			Clone() const;
    Bomb::IEntity*		obj;
  };

  class AnimeEvent : public GraphicEvent
  {
  public:
    AnimeEvent(Bomb::IEntity*, double x = 0.0, double y = 0.0, size_t l = 1, size_t subj = 0);
    ~AnimeEvent() {};
    Event*			Clone() const;
    double			posx;
    double			posy;
    size_t			life;
  };

  class UIEvent : public Event
  {
  public:
    UIEvent(size_t subj = 0);
    ~UIEvent() {};
  };

  enum GameEventValue {PLAYSOUND, DESTROY, DAMAGE, COLLIDE, SCORE, GAMEPAUSE};

  class GameEvent : public Event
  {
  public:
    GameEvent(const std::string& m, size_t subj = 0);
    GameEvent(GameEvent const &e) : Event(e)
    {
      this->msg = msg;
    }
    Event*	Clone() const;
    ~GameEvent() {};
    std::string	msg;
  };

  class DestroyEvent : public GameEvent
  {
  public:
    DestroyEvent(int id);
    DestroyEvent(DestroyEvent const &);
    Event *Clone() const;
    ~DestroyEvent() {};
    int id;
  };

  enum InputType {KEYBOARD, XBOX, LEAP, OTHER};

  class InputEvent : public Event
  {
  public:
    InputEvent(size_t subj = 0) : Event(INPUT, subj)
    {
    }

    ~InputEvent() {};

    Event*              Clone() const
    {
      return (new InputEvent(Subject()));
    }
  };

  // DEBUG
  void	DebugEvent(Event);
}

#endif /* !EVENT_HH_ */
