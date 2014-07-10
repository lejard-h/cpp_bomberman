/*
** DropBonusComponent.hh for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Bomberman/Header
**
** Made by hadrien lejard         
** Login   <lejard_h@epitech.net>
**
** Started on  lun. juin  09 17:21:58 2014 hadrien lejard         
** Last update lun. juin  09 17:21:58 2014 hadrien lejard         
*/

#ifndef __DROPBONUSCOMPONENT_HH__
# define __DROPBONUSCOMPONENT_HH__

#include <cstdlib>
#include "Component.hh"
#include "SysGame.hh"
#include "MapComponent.hh"
#include "LifeComponent.hh"


namespace Bomb
{
	class DropBonusComponent : public BaseComponent
	{
	public:
		DropBonusComponent();
		~DropBonusComponent();

		void	Update();
	private:
		bool	_dropped;
	};
}

#endif