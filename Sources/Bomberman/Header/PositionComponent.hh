/*
** PositionComponent.hh for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Bomberman/Header
**
** Made by hadrien lejard         
** Login   <lejard_h@epitech.net>
**
** Started on  ven. mai  23 11:11:33 2014 hadrien lejard         
** Last update ven. mai  23 11:11:33 2014 hadrien lejard         
*/

#ifndef __POSISITIONCOMPONENT_HH__
#define __POSISITIONCOMPONENT_HH__

#include "Component.hh"

namespace Bomb
{
	class PositionComponent : public BaseComponent
	{
	public:
		PositionComponent();
		PositionComponent(double, double, double);

		enum POS { X, Y };

		void 	SetPosition(double x, double y);
		double	GetPosition(enum POS) const;

		void	SetRotation(double r);
		double	GetRotation() const;

		void	Respawn();
		void	SetSpawn(double, double);
		void dump() const;

	private:
		double	_position[2];
		double	_initialPosition[2];
		double	_rotation;
	};

}
#endif