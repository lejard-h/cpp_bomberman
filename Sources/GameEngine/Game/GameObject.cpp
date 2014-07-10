/*
** GameObject.cpp for Bomberman in /home/lejard_h/rendu/cpp_bomberman/GameEngine
**
** Made by hadrien lejard         
** Login   <lejard_h@epitech.net>
**
** Started on  mar. mai  20 22:24:08 2014 hadrien lejard         
** Last update mar. mai  20 22:24:08 2014 hadrien lejard         
*/

#include "GameObject.hh"
#include "EventDispatcher.hh"

Bomb::GameObject::GameObject()
{
	static int	id = 0;

	this->_id = id++;
	this->_tag = Undefined_o;
	this->_isDestroy = true;
	G_EvDispatcher->AddSubscriber(Event::GAME, this);
}

Bomb::GameObject::~GameObject()
{
	if (!this->_isDestroy)
		this->Destroy();
}

Bomb::GameObject::GameObject(GameObject &o)
{
	this->_components = o.GetComponentList();
	this->_id = o.GetId();
	this->_tag = o.GetTag();
	this->_isDestroy = true;
	G_EvDispatcher->AddSubscriber(Event::GAME, this);
}

Bomb::GameObject	&Bomb::GameObject::operator=(GameObject &o)
{
	this->_components = o.GetComponentList();
	this->_id = o.GetId();
	this->_tag = o.GetTag();
	return *this;
}

void Bomb::GameObject::OnEvent(Event::Event *e)
{
	delete e;
}

std::map<enum Bomb::ComponentType, Bomb::IComponent *>	&Bomb::GameObject::GetComponentList()
{
	return this->_components;
}

void	Bomb::GameObject::ctor(enum GameObjectTag tag)
{
	this->_tag = tag;
}

int		Bomb::GameObject::GetId() const
{
	return this->_id;
}

enum Bomb::GameObjectTag	Bomb::GameObject::GetTag() const
{
	return this->_tag;
}

void	Bomb::GameObject::AddComponent(IComponent *component)
{
	if (component)
		this->_components[component->GetType()] = component;
}

void	Bomb::GameObject::RemoveComponent(enum ComponentType type)
{
	if (this->HasComponent(type))
	{
		delete this->_components[type];
		this->_components.erase(type);
	}
}

bool	Bomb::GameObject::HasComponent(enum ComponentType type) const
{
	return (this->_components.find(type) != this->_components.end());
}

Bomb::IComponent	*Bomb::GameObject::GetComponent(enum ComponentType type)
{
	if (this->HasComponent(type))
		return this->_components[type];
	return 0;
}

void	Bomb::GameObject::Start()
{
	this->_isDestroy = false;
	for (std::map<enum ComponentType, IComponent *>::const_iterator it = this->_components.begin();
		it != this->_components.end(); ++it)
	{
		it->second->Start();
	}
}

void	Bomb::GameObject::Update()
{
	for (std::map<enum ComponentType, IComponent *>::const_iterator it = this->_components.begin();
		it != this->_components.end() && !this->_isDestroy;
		++it)
		it->second->Update();
}

void	Bomb::GameObject::Destroy()
{	
	for (std::map<enum ComponentType, IComponent *>::const_iterator it = this->_components.begin();
		it != this->_components.end(); ++it)
	{
		it->second->Destroy();
		delete it->second;
	}
	this->_isDestroy = true;
}

void Bomb::GameObject::dump(void) const
{
  std::cout << "GameObject {tag : " << this->_tag << ", id : " << this->_id << " }" << std::endl;
  for (std::map<enum ComponentType, IComponent *>::const_iterator it = this->_components.begin();
  	it != this->_components.end(); ++it)
  {
  	it->second->dump();
  }
}

Bomb::GameObject	*Bomb::GameObject::Clone() const
{
	return new GameObject();
}

Bomb::EntityException::EntityException(std::string const &msg, IEntity *entity) : EngineException(msg), _which(entity)
{

}

Bomb::EntityException::~EntityException() throw ()
{

}

Bomb::IEntity	*Bomb::EntityException::Which()
{
	return this->_which;
}