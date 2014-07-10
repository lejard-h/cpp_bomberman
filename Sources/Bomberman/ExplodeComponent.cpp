/*
** ExplodeComponent.cpp for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Bomberman
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  mar. juin  03 17:18:46 2014 hadrien lejard
// Last update Tue Jun 10 21:51:49 2014 Marc Le Labourier
*/

#include "Bomb.hh"
#include "SysGraphic.hh"
#include "DamageEvent.hh"
#include "ExplodeComponent.hh"
#include "ScoreEvent.hh"

Bomb::ExplodeComponent::ExplodeComponent(int power, int size) : _power(power), _size(size)
{
	this->ctor(Explode_c);
	this->_explode = false;
}

Bomb::ExplodeComponent::ExplodeComponent(ExplodeComponent &e) : BaseComponent(e)
{
	this->_power = e.GetPower();
	this->_size = e.GetSize();
	this->_owner = e.GetOwner();
	this->_explode = false;
}

Bomb::ExplodeComponent	&Bomb::ExplodeComponent::operator=(ExplodeComponent &e)
{
	this->_power = e.GetPower();
	this->_size = e.GetSize();
	this->_owner = e.GetOwner();
	this->_explode = false;
	return *this;
}

void	Bomb::ExplodeComponent::SetSize(int s)
{
	this->_size = s;
}

int	Bomb::ExplodeComponent::GetSize() const
{
	return this->_size;
}

int	Bomb::ExplodeComponent::GetPower() const
{
	return this->_power;
}

void	Bomb::ExplodeComponent::Update()
{
  if (G_ObjectsContainer && this->GetParent() && !this->_explode)
    {
      this->_explode = true;
      ListObj  *list_world = G_ObjectsContainer->GetObjByTag(World_o);
      World	*world;

      if (list_world && (world = static_cast<World *>(list_world->front())))
	{
	  MapComponent	*map = static_cast<MapComponent *>(world->GetComponent(Map_c));
	  PositionComponent	*pos
	    = static_cast<PositionComponent *>(this->GetParent()->GetComponent(Position_c));

	  if (map && pos)
	    {
	      bool	left = false;
	      bool	right = false;
	      bool	up = false;
	      bool	down = false;

	     for (int size = 1; size <= this->_size; ++size)
		{
		  this->SendWave(pos->GetPosition(PositionComponent::X) - size,
				 pos->GetPosition(PositionComponent::Y), *map, &left);

		  this->SendWave(pos->GetPosition(PositionComponent::X) + size,
				 pos->GetPosition(PositionComponent::Y), *map, &right);

		  this->SendWave(pos->GetPosition(PositionComponent::X),
			  			pos->GetPosition(PositionComponent::Y) - size, *map, &up);

		  this->SendWave(pos->GetPosition(PositionComponent::X),
				 pos->GetPosition(PositionComponent::Y) + size, *map, &down);
		}
	      bool	center = false;
	      this->SendWave(pos->GetPosition(PositionComponent::X),
			     pos->GetPosition(PositionComponent::Y), *map, &center);
	    }
	}
    }
}

bool	Bomb::ExplodeComponent::SendWave(size_t x, size_t y, MapComponent &map, bool *blocked) const
{
	std::vector<IEntity *>	*tmp = map.OnCell(x, y);
	IEntity	*FireAnim = G_EntityFactory->Create(FireAnim_o);

	if (*blocked == false)
	{
		if (tmp && tmp->size())
		{
			for (std::vector<IEntity *>::iterator it = tmp->begin();
				it != tmp->end() && !(*blocked);
				++it)
			{
				if ((*it)->GetId() != this->GetParent()->GetId())
				{
					NormalBomb	*bombParent = static_cast<NormalBomb *>(this->GetParent());
					if (bombParent)
					{
						IEntity	*bombOwner = G_ObjectsContainer->GetObjById(bombParent->GetOwner());
						if (bombOwner)
						{
							G_EvDispatcher->SendEvent(new Event::DamageEvent(1, (*it)->GetId(), bombOwner->GetId()), Event::COMMON);
							G_EvDispatcher->SendEvent(new Event::ScoreEvent(Event::DamageScoring, bombOwner->GetId(), (*it)->GetId()), Event::COMMON);
							G_EvDispatcher->SendEvent(new Event::ScoreEvent(Event::TakeDamageScoring, (*it)->GetId(), bombOwner->GetId()), Event::COMMON);
						}
					}
					if ((*it)->GetTag() == UndestructibleBox_o || (*it)->GetTag() == DestructibleBox_o ||
						(*it)->GetTag() == Player_o)
						*blocked = true;
				}
			}
		}
		G_EvDispatcher->SendEvent(new Event::AnimeEvent(FireAnim, x, y, 10, Graphic::ANIMADD), Event::COMMON);
	}
	return true;
}

void	Bomb::ExplodeComponent::SetOwner(int owner)
{
	this->_owner = owner;
}

int 	Bomb::ExplodeComponent::GetOwner() const
{
	return this->_owner;
}
