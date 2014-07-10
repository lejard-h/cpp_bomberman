/*
** BombComponent.cpp for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Bomberman
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  lun. juin  02 13:56:24 2014 hadrien lejard
// Last update Mon Jun  9 14:23:15 2014 Marc Le Labourier
*/

#include "BombComponent.hh"

Bomb::BombComponent::BombComponent()
{
	this->ctor(Bomb_c);
	this->_objects[Normal] = NormalBomb_o;
	this->_sizeBombs[Normal] = NORMAL_BOMB_SIZE;
}

Bomb::BombComponent::~BombComponent()
{
	
}

Bomb::BombComponent::BombComponent(BombComponent &b) : BaseComponent(b)
{
	this->_objects = b.GetMapObjectsBomb();
	this->_bombs = b.GetMapNbBomb();
}

Bomb::BombComponent	&Bomb::BombComponent::operator=(BombComponent &b)
{
	this->_objects = b.GetMapObjectsBomb();
	this->_bombs = b.GetMapNbBomb();
	return *this;
}

void	Bomb::BombComponent::SetNbBomb(BombType type, size_t nb)
{
	this->_bombs[type] = nb;
}

bool	Bomb::BombComponent::DropBomb(double x, double y, BombType type)
{
	if (this->_bombs.find(type) == this->_bombs.end() || this->_bombs[type] == 0)
		return false;
	ListObj	*objs;

	if (G_ObjectsContainer && (objs = G_ObjectsContainer->GetObjByTag(World_o)))
	{
		World	*world = static_cast<World *>(objs->front());
		if (world && G_EntityFactory)
		{
			this->RemoveBomb(type);
			DefaultBomb	*bomb
			= static_cast<DefaultBomb *>(G_EntityFactory->Create(this->_objects[type]));
			if (bomb && bomb->HasComponent(Position_c))
			{
				PositionComponent *pos = static_cast<PositionComponent *>(bomb->GetComponent(Position_c));
				pos->SetPosition(((size_t) x) + 0.5, ((size_t) y) + 0.5);
				G_ObjectsContainer->AddObj(bomb);
				bomb->SetOwner(this->_gameobj->GetId());
				world->AddEntity(bomb, x, y);
				bomb->SetSize(this->_sizeBombs[type]);
				bomb->Start();

				G_EvDispatcher->SendEvent(new Event::GraphicEvent(this->GetParent(),
					Graphic::MESHDEL), Event::COMMON);
				G_EvDispatcher->SendEvent(new Event::GraphicEvent(this->GetParent(),
					Graphic::MESHADD), Event::COMMON);

				return true;
			}
		}
	}
	return false;
}

void	Bomb::BombComponent::AddBomb(BombType type)
{
  if (this->_bombs.find(type) != this->_bombs.end())
    this->_bombs[type] += 1;
  else
    this->_bombs[type] = 1;
}

void	Bomb::BombComponent::RemoveBomb(BombType type)
{
	if (this->_bombs.find(type) != this->_bombs.end() && this->_bombs[type] > 0)
		this->_bombs[type] -= 1;
}

std::map<Bomb::BombType, size_t>	&Bomb::BombComponent::GetMapNbBomb()
{
	return this->_bombs;
}

std::map<Bomb::BombType, Bomb::GameObjectTag>	&Bomb::BombComponent::GetMapObjectsBomb()
{
	return this->_objects;
}

void	Bomb::BombComponent::IncreaseSizeBombs()
{
    this->_sizeBombs[Normal]++;
}

void	Bomb::BombComponent::SetSizeBomb(enum BombType type, size_t size)
{
	this->_sizeBombs[type] = size;
}

size_t	Bomb::BombComponent::GetSizeBomb(enum BombType type)
{
	return this->_sizeBombs[type];
}