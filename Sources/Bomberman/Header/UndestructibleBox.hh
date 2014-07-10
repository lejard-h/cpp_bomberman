/*
** UndestructibleBox.hh for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Bomberman/Header
**
** Made by hadrien lejard         
** Login   <lejard_h@epitech.net>
**
** Started on  lun. mai  26 16:49:27 2014 hadrien lejard         
** Last update lun. mai  26 16:49:27 2014 hadrien lejard         
*/

#ifndef __UNDESTRUCTIBLEBOX_HH_
#define __UNDESTRUCTIBLEBOX_HH_

#include "GameObject.hh"
#include "PositionComponent.hh"
#include "PhysicComponent.hh"
#include "GraphicComponent.hh"

namespace Bomb
{

	#define UNDESTRUCTIBLE_BOX_HITBOX	(0.5)

	class UndestructibleBox : public GameObject
	{
	public:
		UndestructibleBox();

		virtual GameObject *Clone() const;
	};
}

#endif