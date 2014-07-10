/*
** Astar.cpp for Bomber in /home/thomas_1/Desktop/Projets/Bomberman/cpp_bomberman/IA
**
** Made by Pierre-Yves THOMAS
** Login   <thomas_1@epitech.net>
**
** Started on  Thu Jun  05 11:31:26 2014 Pierre-Yves THOMAS
** Last update Thu Jun  05 11:31:26 2014 Pierre-Yves THOMAS
*/

#include <iostream>
#include <cmath>
#include "Astar.hh"

/*
** node Astar
*/

Algo::nodeAstar::nodeAstar(int posX, int posY, nodeAstar * const parent)
{
	this->_position = position(posX, posY);
	this->_parent 	= parent;
	this->_range 	= 0;
}

Algo::nodeAstar::nodeAstar(const position &pos, nodeAstar * const parent)
{
	this->_position = pos;
	this->_parent 	= parent;
	this->_range 	= 0;
}

Algo::nodeAstar::~nodeAstar()
{}

void 	Algo::nodeAstar::calcRange(const position &pos)
{
	this->_range 	= pow(pos.first - this->_position.first, 2) + pow(pos.second - this->_position.second, 2);
}

void 	Algo::nodeAstar::calcRange(int posX, int posY)
{
	this->_range	= pow(posX - this->_position.first, 2) + pow(posY - this->_position.second, 2);
}

int		Algo::nodeAstar::getRange() const
{
	return (this->_range);
}

const Algo::position &Algo::nodeAstar::getPosition() const
{
	return (this->_position);
}

Algo::nodeAstar *Algo::nodeAstar::getParent() const
{
	return (this->_parent);
}

/*
** Astar
*/

Algo::Astar::Astar()
{
	this->_map 		= 0;
	this->_begin 	= position(0, 0);
	this->_end 		= position(0, 0);
}

Algo::Astar::~Astar()
{
	this->_path.clear();
	this->_closedNodes.clear();
	this->_openedNodes.clear();
}

void 	Algo::Astar::updateMap(Bomb::MapComponent * const map)
{
	this->_map = map;
}

void 	Algo::Astar::updatePosition(int posX, int posY)
{
	this->_begin = position(posX, posY);
}

void 	Algo::Astar::updatePosition(const position &pos)
{
	this->_begin = pos;
}

void 	Algo::Astar::updateReach(int posX, int posY)
{
	this->_end = position(posX, posY);
}

void 	Algo::Astar::updateReach(const position &pos)
{
	this->_end = pos;
}

const Algo::pathD &Algo::Astar::getPath() const
{
	return (this->_path);
}

bool 	Algo::Astar::insertNodeInList(int posX, int posY, nodeAstar * const node, const position &end)
{
	nodeAstar 								*newNode;
	listNodeIt								ite;

	if (this->_map)
	{
		// Verification de la case
		if (this->_map->IsTypeOnCell(posX, posY, Bomb::DestructibleBox_o)
			|| this->_map->IsTypeOnCell(posX, posY, Bomb::UndestructibleBox_o)
			|| this->_map->IsTypeOnCell(posX, posY, Bomb::NormalBomb_o))
			return (false);

		newNode = new Algo::nodeAstar(posX, posY, node);
		newNode->calcRange(end);

		// Verification si la node n'existe pas dans les deux listes
		for (ite = this->_closedNodes.begin() ; ite != this->_closedNodes.end() ; ++ite)
			if ((*ite)->getPosition() == std::pair<int, int>(posX, posY))
				{
					delete newNode;
					return (false);
				}
		for (ite = this->_openedNodes.begin() ; ite != this->_openedNodes.end() ; ++ite)
			if ((*ite)->getPosition() == std::pair<int, int>(posX, posY))
				{
					delete newNode;
					return (false);
				}
		this->_openedNodes.push_back(newNode);
		return (true);
	}
	return (false);
}

Algo::nodeAstar *Algo::Astar::defineNextNode() const
{
	listNodeItConst	it;
	nodeAstar 		*node;

	node = 0;
	for (it = this->_openedNodes.begin() ; it != this->_openedNodes.end() ; ++it)
		if (!node || node->getRange() > (*it)->getRange())
			node = *it;
	return (node);
}

bool 	Algo::Astar::calculateNodesAround(nodeAstar * const node, const position &end)
{
	position 				pos;
	if (!node)
		return (false);

	pos = node->getPosition();
	insertNodeInList(pos.first, pos.second - 1, node, end);
	insertNodeInList(pos.first + 1, pos.second, node, end);
	insertNodeInList(pos.first, pos.second + 1, node, end);
	insertNodeInList(pos.first - 1, pos.second, node, end);
	return (true);
}

bool 	Algo::Astar::calculatePath()
{
	Algo::nodeAstar *node;
	position 		tmp;

	if (!_map)
	{
		std::cerr << "Error : MapComponent not found" << std::endl;
		return (false);
	}
	tmp = this->_begin;
	node = new nodeAstar(tmp, 0);

	this->_closedNodes.push_front(node);
	while (node->getPosition() != this->_end)
	{
		if (this->calculateNodesAround(node, this->_end) == false
			|| ((node = this->defineNextNode()) == false))
		{
			this->_closedNodes.clear();
			this->_openedNodes.clear();
			return(false);
		}
		this->_closedNodes.push_front(node);
		this->_openedNodes.remove(node);
	}
	this->createPath();
	this->_closedNodes.clear();
	this->_openedNodes.clear();
	return (true);
}

void 	Algo::Astar::createPath()
{
	nodeAstar 	*node;
	positionD 	pos;

	node = this->_closedNodes.front();
	while (node)
	{
		// Cet ajout permet de garder l'IA le plus au centre possible lors du mouvement
		pos = node->getPosition();
		pos.first += 0.5;
		pos.second += 0.5;
		this->_path.push_front(pos);
		node = node->getParent();
	}
}

void 	Algo::Astar::displayPath() const
{
	pathDItConst it;
	for (it = this->_path.begin() ; it != this->_path.end() ; ++it)
		std::cout << "x = " << (*it).first << " ; y = " << (*it).second << std::endl;
}

void 	Algo::Astar::reset()
{
	this->_map 		= 0;
	this->_begin 	= position(0, 0);
	this->_end 		= position(0, 0);
	this->_openedNodes.clear();
	this->_closedNodes.clear();
	this->_path.clear();
}

void 	Algo::Astar::clearNodes()
{
	this->_openedNodes.clear();
	this->_closedNodes.clear();
}

void 	Algo::Astar::clearPath()
{
	this->_path.clear();
}