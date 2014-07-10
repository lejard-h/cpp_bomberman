/*
** IAactions.cpp for Bomber in /home/thomas_1/Desktop/Projets/Bomberman/cpp_bomberman/Bomberman/IA
**
** Made by Pierre-Yves THOMAS
** Login   <thomas_1@epitech.net>
**
** Started on  Tue Jun  10 21:57:14 2014 Pierre-Yves THOMAS
** Last update Tue Jun  10 21:57:14 2014 Pierre-Yves THOMAS
*/

#include <cstdlib>
#include "IAactions.hh"
#include "Astar.hh"
#include "PositionComponent.hh"

Bomb::IAactions::IAactions(Bomb::IaComponent *Ia)
{
	ListObj 			*objs;

	// Recuperation de la map
	if (G_ObjectsContainer && (objs = G_ObjectsContainer->GetObjByTag(World_o)))
    {
    	World	*world = static_cast<World *>(objs->front());
      	this->_map = (world && G_EntityFactory) ? (dynamic_cast<MapComponent *>(world->GetComponent(Map_c))) : (0);
	}
	else
		this->_map = 0;


	// Recuperation des bombes
	this->_bombs = (G_ObjectsContainer) ? (G_ObjectsContainer->GetObjByTag(NormalBomb_o)) : (0);

	// Recuperation des IA
	this->_AI = (G_ObjectsContainer) ? (G_ObjectsContainer->GetObjByTag(Player_o)) : (0);

	this->_ia = Ia;
}

Bomb::IAactions::~IAactions()
{

}

bool 	Bomb::IAactions::getDestructibleObjectAtRange(int range)
{
	int angle 	= 0;
	bool res 	= false;
	PositionComponent 		*positionIA;
	std::pair<int, int> 	posDep;
	std::pair<int, int> 	posEnd;

	this->_safePaths.clear();
	if (_ia)
	{
		positionIA = dynamic_cast<PositionComponent *>(_ia->GetParent()->GetComponent(Position_c));
		if (positionIA)
		{
			int sX = positionIA->GetPosition(PositionComponent::X);
			int sY = positionIA->GetPosition(PositionComponent::Y);
			while (angle < 360)
			{
				posDep = std::pair<int, int>(sX + FCOS(angle % 360) * range, sY - FSIN(angle % 360) * range);
				posEnd = std::pair<int, int>(sX + FCOS((angle + 90) % 360) * range, sY - FSIN((angle + 90) % 360) * range);
				while (posDep != posEnd)
				{
					if (this->_map->ValidCell(posDep.first, posDep.second)
						&& isSafe(posDep.first, posDep.second)
						&& isDestructibleObjectOnRange(posDep.first, posDep.second))
					{
						res = true;
						this->_destructiblePaths.push_front(std::pair<int, int>(posDep));
					}
					posDep.first 	+= INCRS(posDep.first, posEnd.first);
					posDep.second	+= INCRS(posDep.second, posEnd.second);
				}
				angle += 90;
			}
		}
	}
	return (res);
}

bool 	Bomb::IAactions::isDestructibleObjectOnRange(double posX, double posY)
{
	if (_ia && this->_map)
	{
		BombComponent		*bomb = static_cast<BombComponent *>(_ia->GetParent()->GetComponent(Bomb_c));
		PositionComponent 	*positionIA = dynamic_cast<PositionComponent *>(_ia->GetParent()->GetComponent(Position_c));

		if (positionIA && bomb)
		{
			size_t count;
			size_t i 	= 0;
			int angle 	= rand() % 4 * 90;
			int incrX 	= 0;
			int incrY 	= 0;
			int sX 		= static_cast<size_t>(posX);
			int sY 		= static_cast<size_t>(posY);
			while (i < 4)
			{
				incrX = FCOS(angle);
				incrY = FSIN(angle);
				count = 1;
				// Check cases par cases
				while (count <= bomb->GetSizeBomb(Bomb::Normal))
				{

					// Vérifie si la case est une box
					if (this->_map->IsTypeOnCell(sX + incrX * count, sY + incrY * count, DestructibleBox_o)
						|| (this->_map->IsTypeOnCell(sX + incrX * count, sY + incrY * count, Player_o)
						&&	!this->_map->IsOnCell(sX + incrX * count, sY + incrY * count, this->_ia->GetParent()->GetId())))
						return (true);
					else if (this->_map->IsTypeOnCell(sX + incrX * count, sY + incrY * count, UndestructibleBox_o))
						count = bomb->GetSizeBomb(Bomb::Normal);
					++count;
				}
				angle = (angle + 90) % 360;
				++i;
			}
		}
	}
	return (false);
}

bool 	Bomb::IAactions::isDestructibleObjectOnRange()
{
	if (_ia && this->_map)
	{
		BombComponent		*bomb = static_cast<BombComponent *>(_ia->GetParent()->GetComponent(Bomb_c));
		PositionComponent 	*positionIA = dynamic_cast<PositionComponent *>(_ia->GetParent()->GetComponent(Position_c));

		if (positionIA && bomb)
		{
			size_t count;
			size_t i 	= 0;
			int angle 	= rand() % 4 * 90;
			int incrX 	= 0;
			int incrY 	= 0;
			int sX 		= static_cast<size_t>(positionIA->GetPosition(PositionComponent::X));
			int sY 		= static_cast<size_t>(positionIA->GetPosition(PositionComponent::Y));
			while (i < 4)
			{
				incrX = FCOS(angle);
				incrY = FSIN(angle);
				count = 1;
				// Check cases par cases
				while (count <= bomb->GetSizeBomb(Bomb::Normal))
				{

					// Vérifie si la case est une box
					if (this->_map->IsTypeOnCell(sX + incrX * count, sY + incrY * count, DestructibleBox_o)
						|| (this->_map->IsTypeOnCell(sX + incrX * count, sY + incrY * count, Player_o)
						&&	!this->_map->IsOnCell(sX + incrX * count, sY + incrY * count, this->_ia->GetParent()->GetId())))
						return (true);
					else if (this->_map->IsTypeOnCell(sX + incrX * count, sY + incrY * count, UndestructibleBox_o))
						count = bomb->GetSizeBomb(Bomb::Normal);
					++count;
				}
				angle = (angle + 90) % 360;
				++i;
			}
		}
	}
	return (false);
}

bool 	Bomb::IAactions::findShortestPath(const std::list<std::pair<int, int> > &list)
{
	std::list<std::pair <int, int> >::const_iterator	it;
	std::list<std::pair <double, double> >					path;
	PositionComponent 	*positionIA;
	Algo::Astar 		astar;
	bool 				res = false;
	
	this->_shortestPath.clear();
	if (_ia && this->_map)
	{
		positionIA = dynamic_cast<PositionComponent *>(_ia->GetParent()->GetComponent(Position_c));
		if (positionIA)
		{
			astar.updateMap(this->_map);
			astar.updatePosition(positionIA->GetPosition(PositionComponent::X), positionIA->GetPosition(PositionComponent::Y));

			for (it = list.begin() ; it != list.end(); ++it)
			{
				astar.updateReach((*it).first, (*it).second);
				if (astar.calculatePath() == true)
				{
					res = true;
					path = astar.getPath();
					if (this->_shortestPath.empty() || path.size() < this->_shortestPath.size())
						this->_shortestPath = path;
				}
				astar.clearNodes();
				astar.clearPath();				
			}
		}
	}
	return (res);
}



bool 	Bomb::IAactions::findOtherAI()
{
	PositionComponent 	*positionIA 	= 0;
	PositionComponent	*positionMe 	= 0;
	Player 				*player 		= 0;
	std::list<IEntity *>::iterator 	it;
	bool				res = false;

	this->_otherAIPaths.clear();
	if (this->_AI)
		for (it = _AI->Begin() ; it != _AI->End() ; ++it)
		{
			player = dynamic_cast<Player *>(*it);
			if (player && _ia)
			{ 
				positionIA = dynamic_cast<PositionComponent *>(player->GetComponent(Position_c));
				positionMe = dynamic_cast<PositionComponent *>(_ia->GetParent()->GetComponent(Position_c));
				if (positionIA && positionMe)
				{
					int sX = positionIA->GetPosition(PositionComponent::X);
					int sY = positionIA->GetPosition(PositionComponent::Y);
					int mX = positionMe->GetPosition(PositionComponent::X);
					int mY = positionMe->GetPosition(PositionComponent::Y);

					if (sX != mX || sY != mY)
					{
						this->_otherAIPaths.push_back(std::pair<int, int>(sX, sY));
						res = true;
					}
				}
			}
		}
	return (res);
}

bool 	Bomb::IAactions::getPathAtRange(int range)
{
	int angle 	= 0;
	bool res 	= false;
	PositionComponent 		*positionIA;
	std::pair<int, int> 	posDep;
	std::pair<int, int> 	posEnd;

	this->_safePaths.clear();
	if (_ia)
	{
		positionIA = dynamic_cast<PositionComponent *>(_ia->GetParent()->GetComponent(Position_c));
		if (positionIA)
		{
			int sX = positionIA->GetPosition(PositionComponent::X);
			int sY = positionIA->GetPosition(PositionComponent::Y);
			while (angle < 360)
			{
				posDep = std::pair<int, int>(sX + FCOS(angle % 360) * range, sY - FSIN(angle % 360) * range);
				posEnd = std::pair<int, int>(sX + FCOS((angle + 90) % 360) * range, sY - FSIN((angle + 90) % 360) * range);
				while (posDep != posEnd)
				{
					if (this->_map->ValidCell(posDep.first, posDep.second)
						&& isSafe(posDep.first, posDep.second))
					{
						res = true;
						this->_safePaths.push_front(std::pair<int, int>(posDep));
					}
					posDep.first 	+= INCRS(posDep.first, posEnd.first);
					posDep.second	+= INCRS(posDep.second, posEnd.second);
				}
				angle += 90;
			}
		}
	}
	return (res);
}

bool 	Bomb::IAactions::getBonusAtRange(int range)
{
	int angle 	= rand() % 4 * 90;
	int count   = 0;
	bool res 	= false;
	PositionComponent 		*positionIA;
	std::pair<int, int> 	posDep;
	std::pair<int, int> 	posEnd;

	this->_bonusPaths.clear();
	if (_ia)
	{
		positionIA = dynamic_cast<PositionComponent *>(_ia->GetParent()->GetComponent(Position_c));
		if (positionIA)
		{
			int sX = positionIA->GetPosition(PositionComponent::X);
			int sY = positionIA->GetPosition(PositionComponent::Y);
			while (count < 4)
			{
				posDep 	= std::pair<int, int>(sX + FCOS(angle % 360) * range, sY - FSIN(angle % 360) * range);
				posEnd 	= std::pair<int, int>(sX + FCOS((angle + 90) % 360) * range, sY - FSIN((angle + 90) % 360) * range);
 				
				while (posDep != posEnd)
				{
					if (this->_map->IsTypeOnCell(posDep.first, posDep.second, BonusSpeed_o)
						|| this->_map->IsTypeOnCell(posDep.first, posDep.second, BonusAddBomb_o)
						|| this->_map->IsTypeOnCell(posDep.first, posDep.second, BonusSizeBomb_o))
					{			
						this->_bonusPaths.push_front(std::pair<int, int>(posDep));
						res = true;
					}
					posDep.first 	+= INCRS(posDep.first, posEnd.first);
					posDep.second	+= INCRS(posDep.second, posEnd.second);
				}
				angle = (angle + 90) % 360;
				++count;
			}
		}
	}
	return (res);
}

bool 	Bomb::IAactions::isExplodingAt(Bomb::NormalBomb * const bomb) const
{
	IComponent 	*BombCompo;
	IComponent 	*IaCompo;

	PositionComponent 	*positionBomb 	= 0;
	PositionComponent 	*positionIA 	= 0;

	if (bomb && _ia)
		{
			// Recuperation du contenu
			BombCompo 		= bomb->GetComponent(Position_c);
			IaCompo 		= _ia->GetParent()->GetComponent(Position_c);
			positionBomb 	= dynamic_cast<PositionComponent *>(BombCompo);
			positionIA 		= dynamic_cast<PositionComponent *>(IaCompo);

			if (!positionIA || !positionBomb)
				return (false);

			// Initialisation des positions de départ
			int sX = positionBomb->GetPosition(PositionComponent::X);
			int sY = positionBomb->GetPosition(PositionComponent::Y);

			// Check lignes par lignes
			size_t count;
			int angle = 0;
			int incrX = 0;
			int incrY = 0;
			while (angle < 360)
			{
				incrX = FCOS(angle);
				incrY = FSIN(angle);
				count = 0;

				// Check cases par cases
				while (count <= bomb->GetSize())
				{
					if (sX + incrX * count == static_cast<size_t>(positionIA->GetPosition(PositionComponent::X)) &&
						sY + incrY * count == static_cast<size_t>(positionIA->GetPosition(PositionComponent::Y)))
						return (true);

					// Vérifie si la case est une box
					if (this->_map->IsTypeOnCell(sX + incrX * count, sY + incrY * count, Bomb::DestructibleBox_o)
						|| this->_map->IsTypeOnCell(sX + incrX * count, sY + incrY * count, Bomb::UndestructibleBox_o))
							count = bomb->GetSize();

					++count;
				}
				angle += 90;
			}
		}
	return (false);
}

bool 	Bomb::IAactions::isExplodingAt(Bomb::NormalBomb * const bomb, int posX, int posY) const
{
	IComponent 			*BombCompo;
	PositionComponent 	*positionBomb 	= 0;

	if (bomb && _ia && _map)
		{
			// Recuperation du contenu
			BombCompo 		= bomb->GetComponent(Position_c);
			positionBomb 	= dynamic_cast<PositionComponent *>(BombCompo);

			if (!positionBomb)
				return (false);

			// Initialisation des positions de départ
			int sX = positionBomb->GetPosition(PositionComponent::X);
			int sY = positionBomb->GetPosition(PositionComponent::Y);

			// Check lignes par lignes
			size_t count;
			int angle = 0;
			int incrX = 0;
			int incrY = 0;
			while (angle < 360)
			{
				incrX = FCOS(angle);
				incrY = FSIN(angle);
				count = 0;

				// Check cases par cases
				while (count <= bomb->GetSize())
				{
					if (sX + incrX * count == static_cast<size_t>(posX) &&
						sY + incrY * count == static_cast<size_t>(posY))
						return (true);

					// Vérifie si la case est une box
					if (this->_map->IsTypeOnCell(sX + incrX * count, sY + incrY * count, Bomb::DestructibleBox_o)
						|| this->_map->IsTypeOnCell(sX + incrX * count, sY + incrY * count, Bomb::UndestructibleBox_o))
							count = bomb->GetSize();

					++count;
				}
				angle += 90;
			}
		}
	return (false);
}

bool 	Bomb::IAactions::isSafe()
{
	std::list<IEntity *>::iterator 	it;

	if (_bombs)
		for (it = _bombs->Begin() ; it != _bombs->End() ; ++it)
		{
			if (this->isExplodingAt(dynamic_cast<NormalBomb *>(*it)) == true)
				return (false);
		}
	return (true);
}

bool 	Bomb::IAactions::isSafe(int posX, int posY)
{
	std::list<IEntity *>::iterator 	it;

	if (_bombs)
		for (it = _bombs->Begin() ; it != _bombs->End() ; ++it)
		{
			if (this->isExplodingAt(dynamic_cast<NormalBomb *>(*it), posX, posY) == true)
				return (false);
		}
	return (true);
}

const std::list<std::pair<double, double> > &Bomb::IAactions::getShortestPath() const
{
	return (this->_shortestPath);
}

const std::list<std::pair<int, int> > &Bomb::IAactions::getOtherAIPath() const
{
	return (this->_otherAIPaths);
}

const std::list<std::pair<int, int> > &Bomb::IAactions::getSafePath() const
{
	return (this->_safePaths);
}

const std::list<std::pair<int, int> > &Bomb::IAactions::getBonusPath() const
{
	return (this->_bonusPaths);
}

const std::list<std::pair<int, int> > &Bomb::IAactions::getDestruciblePath() const
{
	return (this->_destructiblePaths);
}
