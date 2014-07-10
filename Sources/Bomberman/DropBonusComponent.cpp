/*
** DropBonusComponent.cpp for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Bomberman
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  lun. juin  09 17:25:49 2014 hadrien lejard
// Last update Wed Jun 11 14:21:01 2014 Marc Le Labourier
*/

#include "GraphicComponent.hh"
#include "DropBonusComponent.hh"

Bomb::DropBonusComponent::DropBonusComponent()
{
	srand(time(0));
	this->_dropped = false;
}

Bomb::DropBonusComponent::~DropBonusComponent()
{
	this->Destroy();
}

void	Bomb::DropBonusComponent::Update()
{
  PositionComponent *pos
    = static_cast<PositionComponent *>(this->GetParent()->GetComponent(Position_c));
  LifeComponent *life
    = static_cast<LifeComponent *>(this->GetParent()->GetComponent(Life_c));
  enum GameObjectTag	bonusTab[3];

  bonusTab[0] = BonusSpeed_o;
  bonusTab[1] = BonusAddBomb_o;
  bonusTab[2] = BonusSizeBomb_o;
  ListObj	*list_world = G_ObjectsContainer->GetObjByTag(World_o);
  if (list_world && life && life->GetLife() <= 0 && !this->_dropped)
    {
      IEntity	*world = list_world->front();
      if (world)
	{
	  MapComponent	*map = static_cast<MapComponent *>(world->GetComponent(Map_c));
	  if (pos && map)
	    {
	      double posX = pos->GetPosition(PositionComponent::X);
	      double posY = pos->GetPosition(PositionComponent::Y);

	      if (rand() % 10 < 4)
		{
		  IEntity	*bonus = G_EntityFactory->Create(bonusTab[rand() % 3]);

		  if (bonus)
		    {
		      pos = static_cast<PositionComponent *>(bonus->GetComponent(Position_c));

		      G_ObjectsContainer->AddObj(bonus);
		      G_EvDispatcher->SendEvent(new Event::GraphicEvent(bonus, Graphic::MESHADD),
		      				Event::COMMON);
		      pos->SetPosition(posX, posY);
		      map->AddEntity(bonus, posX, posY);
		      bonus->Start();
		      this->_dropped = true;
		    }
		}
	    }
	}
    }
}
