/*
** PositionComponent.cpp for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Bomberman
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  ven. mai  23 11:23:31 2014 hadrien lejard
// Last update Fri Jun  6 11:31:41 2014 Marc Le Labourier
*/

#include "PositionComponent.hh"

Bomb::PositionComponent::PositionComponent()
{
	this->ctor(Position_c);
	this->_position[X] = 0.0;
	this->_position[Y] = 0.0;
	this->_rotation = 0.0;
	this->_initialPosition[X] = -1.0;
	this->_initialPosition[Y] = -1.0;
}

Bomb::PositionComponent::PositionComponent(double x, double y, double r)
{
	this->ctor(Position_c);
	this->_position[X] = x;
	this->_position[Y] = y;
	this->_rotation = r;
	this->_initialPosition[X] = x;
	this->_initialPosition[Y] = y;
}

void	Bomb::PositionComponent::SetPosition(double x, double y)
{
	this->_position[X] = x;
	this->_position[Y] = y;
}

double Bomb::PositionComponent::GetPosition(enum POS pos) const
{
	return this->_position[pos];
}

void	Bomb::PositionComponent::SetRotation(double r)
{
	this->_rotation = r;
}

double	Bomb::PositionComponent::GetRotation() const
{
	return this->_rotation;
}

void	Bomb::PositionComponent::dump() const
{
  std::cout << "PositionComponent { " << this->_position[X] << ", "
	    << this->_position[Y] << " }"<< std::endl;
}

void	Bomb::PositionComponent::Respawn()
{
	this->_position[X] = this->_initialPosition[X];
	this->_position[Y] = this->_initialPosition[Y];
}

void	Bomb::PositionComponent::SetSpawn(double x, double y)
{
	this->_initialPosition[X] = x;
	this->_initialPosition[Y] = y;
}