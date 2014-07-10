/*
** InputComponent.cpp for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Bomberman
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  jeu. mai  29 14:32:00 2014 hadrien lejard
// Last update Sun Jun 15 18:09:10 2014 Marc Le Labourier
*/

#include "InputComponent.hh"
#include "Player.hh"

Bomb::InputComponent::InputComponent()
{
	this->ctor(Input_c);
	this->_rMap["up"] = 270.0;
	this->_rMap["down"] = 90.0;
	this->_rMap["right"] = 0.0;
	this->_rMap["left"] = 180.0;
}

void	Bomb::InputComponent::Destroy()
{
	this->_events.clear();
}

void	Bomb::InputComponent::OnEvent(Event::Event *ev)
{
	if (ev->Scope() == Event::INPUT)
		this->_events.push_back(ev);
	else
		delete ev;
}

void	Bomb::InputComponent::Move(std::string const &action) const
{
  std::map<std::string, double>::const_iterator it = this->_rMap.find(action);

  if (this->GetParent()->HasComponent(Physics_c) &&
      this->GetParent()->HasComponent(Position_c))
    {
      PhysicComponent *physic
	= static_cast<PhysicComponent *>(this->GetParent()->GetComponent(Physics_c));
      physic->SetVelocity(PLAYER_VELOCITY);
      PositionComponent *pos
	= static_cast<PositionComponent *>(this->GetParent()->GetComponent(Position_c));
      if (it != this->_rMap.end())
	pos->SetRotation(it->second);
    }
}

void	Bomb::InputComponent::Move(int angle) const
{
	if (this->GetParent()->HasComponent(Physics_c) &&
		this->GetParent()->HasComponent(Position_c))
	{
		PhysicComponent *physic
		= static_cast<PhysicComponent *>(this->GetParent()->GetComponent(Physics_c));
		physic->SetVelocity(PLAYER_VELOCITY);
		PositionComponent *pos
		= static_cast<PositionComponent *>(this->GetParent()->GetComponent(Position_c));
		pos->SetRotation(angle);
	}
}

void	Bomb::InputComponent::PutBomb() const
{
  PositionComponent	*pos
    = static_cast<PositionComponent *>(this->GetParent()->GetComponent(Position_c));
  BombComponent		*bomb
    = static_cast<BombComponent *>(this->GetParent()->GetComponent(Bomb_c));
  ListObj				*list_world	= G_ObjectsContainer->GetObjByTag(World_o);

  if (list_world)
    {
      IEntity	*world = list_world->front();
      if (world)
	{
	  MapComponent	*map
	    = static_cast<MapComponent *>(world->GetComponent(Map_c));
	  if (pos && bomb && map && !map->IsTypeOnCell(pos->GetPosition(PositionComponent::X),
						       pos->GetPosition(PositionComponent::Y),
						       NormalBomb_o))
	    bomb->DropBomb(pos->GetPosition(PositionComponent::X),
			   pos->GetPosition(PositionComponent::Y), Normal );
	}
    }
}
