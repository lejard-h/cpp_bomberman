/*
** Component.hh for Bomberman in /home/lejard_h/rendu/cpp_bomberman/GameEngine
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  mar. mai  20 21:32:14 2014 hadrien lejard
// Last update Wed May 21 22:06:43 2014 Marc Le Labourier
*/

#ifndef __COMPONENT_HH__
# define __COMPONENT_HH__

#include <iostream>
#include "Exception.hh"
#include "GameObject.hh"
#include "EventDispatcher.hh"
#include "Types.hh"

namespace Bomb
{

  class IEntity;

  class IComponent : public Event::ISubscriber
  {
  public:
    virtual ~IComponent() {};
    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual void Destroy() = 0;
    virtual enum ComponentType	GetType() const = 0;
    virtual void dump(void) const = 0;
    virtual void AssignEntity(IEntity *) = 0;
    virtual IEntity *GetParent() const = 0;
  };

  class ComponentException : public EngineException
  {
  public:
    ComponentException(std::string const &msg, IComponent *);
    virtual ~ComponentException() throw ();

    IComponent  *Which();
  private:
    IComponent  *_which;
  };

  class BaseComponent : public IComponent
  {
  public:
    BaseComponent();
    ~BaseComponent();
    BaseComponent(BaseComponent &);

    BaseComponent &operator=(BaseComponent &);
    void ctor(enum ComponentType);
    void AssignEntity(IEntity *);
    enum ComponentType	GetType() const;
    IEntity *GetParent() const;

    virtual void OnEvent(Event::Event *);

    virtual void Start();
    virtual void Update();
    virtual void Destroy();
    virtual void dump(void) const;

  protected:
    IEntity	*_gameobj;
    enum ComponentType	_type;
  };
}

#endif /* __COMPONENT_HH__ */
