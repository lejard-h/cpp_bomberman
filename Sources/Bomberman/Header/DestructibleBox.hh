/*
** DestructibleBox.hh for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Bomberman/Header
**
** Made by hadrien lejard         
** Login   <lejard_h@epitech.net>
**
** Started on  lun. mai  26 16:59:02 2014 hadrien lejard         
** Last update lun. mai  26 16:59:02 2014 hadrien lejard         
*/

#ifndef __DESTRUCTIBLE_HH__
#define __DESTRUCTIBLE_HH__

#include <list>
#include "GameObject.hh"
#include "LifeComponent.hh"
#include "PositionComponent.hh"
#include "PhysicComponent.hh"
#include "GraphicComponent.hh"
#include "AudioComponent.hh"
#include "DamageEvent.hh"

namespace Bomb
{

	#define DESTRUCTIBLE_BOX_HITBOX	(0.5)

	class DestructibleBox : public GameObject
	{
	public:
		DestructibleBox();

		virtual GameObject *Clone() const;
		virtual void OnEvent(Event::Event *);
		void  EventTreatment();
		void	Update();

	private:
		std::list<Event::Event *>	_events;
		
	};
}

#endif