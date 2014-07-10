/*
** Component.cpp for Bomberman in /home/lejard_h/rendu/cpp_bomberman/GameEngine
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  mar. mai  20 23:48:52 2014 hadrien lejard
// Last update Wed May 21 22:08:34 2014 Marc Le Labourier
*/

#include <ostream>
#include "Component.hh"

Bomb::BaseComponent::BaseComponent()
{
	this->_gameobj = 0;
	this->_type = Undefined_c;
	G_EvDispatcher->AddSubscriber(Event::GAME, this);
}

Bomb::BaseComponent::~BaseComponent()
{
	this->Destroy();
}

Bomb::BaseComponent::BaseComponent(BaseComponent &b)
{
	this->_gameobj = b.GetParent();
	this->_type = b.GetType();
	G_EvDispatcher->AddSubscriber(Event::GAME, this);
}

Bomb::BaseComponent	&Bomb::BaseComponent::operator=(BaseComponent &b)
{
	this->_gameobj = b.GetParent();
	this->_type = b.GetType();
	return *this;
}

void	Bomb::BaseComponent::ctor(enum ComponentType componentType)
{
	this->_type = componentType;
}

enum Bomb::ComponentType	Bomb::BaseComponent::GetType() const
{
	return this->_type;
}

void	Bomb::BaseComponent::OnEvent(Event::Event *)
{
}

void	Bomb::BaseComponent::Start()
{
}

void	Bomb::BaseComponent::Update()
{
}

void	Bomb::BaseComponent::Destroy()
{
}

void Bomb::BaseComponent::dump(void) const
{
	std::cout << "BaseComponent" << std::endl;
}

void	Bomb::BaseComponent::AssignEntity(IEntity *entity)
{
	this->_gameobj = entity;
}

Bomb::IEntity	*Bomb::BaseComponent::GetParent() const
{
	return this->_gameobj;
}

Bomb::ComponentException::ComponentException(std::string const &msg, IComponent *component) : EngineException(msg), _which(component)
{
}

Bomb::ComponentException::~ComponentException() throw()
{
}

Bomb::IComponent	*Bomb::ComponentException::Which()
{
	return this->_which;
}