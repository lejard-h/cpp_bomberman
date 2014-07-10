/*
** GameObject.hh for Bomberman in /home/lejard_h/rendu/cpp_bomberman/GameEngine
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  mar. mai  20 21:40:43 2014 hadrien lejard
// Last update Thu Jun  5 17:57:57 2014 Marc Le Labourier
*/

#ifndef __GAMEOBJECT_HH__
# define __GAMEOBJECT_HH__

#include <iostream>
#include <map>
#include "EventDispatcher.hh"
#include "Component.hh"
#include "Prototype.hh"
#include "Types.hh"


namespace Bomb
{

	class IComponent;

	class IEntity : public Pattern::IPrototype<IEntity>, public Event::ISubscriber
	{
	public:
		virtual ~IEntity() {};
		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void Destroy() = 0;

		virtual void AddComponent(IComponent *) = 0;
		virtual void RemoveComponent(enum ComponentType) = 0;
		virtual bool HasComponent(enum ComponentType) const = 0;
		virtual IComponent	*GetComponent(enum ComponentType) = 0;

		virtual int	GetId() const = 0;
		virtual enum GameObjectTag GetTag() const = 0;

		virtual void dump(void) const = 0;

		virtual IEntity *Clone() const = 0;

	};

	class EntityException : public EngineException
	{
	public:
		EntityException(std::string const &msg, IEntity *);
		virtual ~EntityException() throw ();

		IEntity	*Which();

	private:

		IEntity *_which;
	};

	class GameObject : public IEntity
	{
	public:
		GameObject();
		~GameObject();
		GameObject(GameObject &);
		void	ctor(enum GameObjectTag tag);

		int 	GetId() const;
		enum 	GameObjectTag	GetTag() const;
		std::map<enum ComponentType, IComponent *>	&GetComponentList();

		void	AddComponent(IComponent *);
		void	RemoveComponent(enum ComponentType);
		bool	HasComponent(enum ComponentType) const;
		IComponent	*GetComponent(enum ComponentType);
		virtual void Start();
		virtual void Update();
		virtual void Destroy();

		virtual void dump(void) const;
		virtual GameObject *Clone() const;

		virtual void OnEvent(Event::Event *);

		GameObject	&operator=(GameObject &);

	protected:
		int					_id;
		enum GameObjectTag	_tag;
		std::map<enum ComponentType, IComponent *>	_components;
		bool				_isDestroy;
	};
}

#endif /* __GAMEOBJECT_HH__ */
