/*
** LifeComponent.hh for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Bomberman/Header
**
** Made by hadrien lejard         
** Login   <lejard_h@epitech.net>
**
** Started on  dim. mai  25 14:38:24 2014 hadrien lejard         
** Last update dim. mai  25 14:38:24 2014 hadrien lejard         
*/

#ifndef __LIFECOMPONENT_HH__
#define __LIFECOMPONENT_HH__

#include "Component.hh"

namespace Bomb
{
	class LifeComponent : public BaseComponent
	{
	public:
		LifeComponent();
		LifeComponent(int life, int maxLife = 0);

		void dump() const;

		int		GetLife() const;
		void	Damage(int);
		void	Heal(int);
		void	SetMaxLife(unsigned int);
		void	SetLife(int);
		unsigned int		GetMaxLife() const;
		void	Update();
		void	Respawn();
	private:
		int		_life;
		unsigned int		_maxLife;
		bool	isDead;
	};
}

#endif