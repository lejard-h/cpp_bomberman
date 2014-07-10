/*
** ExplodeComponent.hh for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Bomberman/Header
**
** Made by hadrien lejard         
** Login   <lejard_h@epitech.net>
**
** Started on  mar. juin  03 17:15:46 2014 hadrien lejard         
** Last update mar. juin  03 17:15:46 2014 hadrien lejard         
*/

#ifndef __EXPLODECOMPONENT_HH__
#define __EXPLODECOMPONENT_HH__

#include "Component.hh"
#include "PositionComponent.hh"
#include "MapComponent.hh"
#include "World.hh"
#include "SysGame.hh"
#include "LifeComponent.hh"

namespace Bomb
{
	class MapComponent;

	class ExplodeComponent : public BaseComponent
	{
	public:
		ExplodeComponent(int power, int size);
		ExplodeComponent(ExplodeComponent &);
		ExplodeComponent &operator=(ExplodeComponent &);

		void	Update();
		bool	SendWave(size_t x, size_t y, MapComponent &, bool *) const;
		void	SetOwner(int);
		void	SetSize(int);
		int		GetOwner() const;
		int		GetPower() const;
		int		GetSize() const;

	private:
		int		_power;
		int		_size;
		int		_owner;
		bool	_explode;
	};
}

#endif