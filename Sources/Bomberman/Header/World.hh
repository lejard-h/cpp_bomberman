/*
** World.hh for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Bomberman/Header
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  jeu. mai  29 12:21:15 2014 hadrien lejard
// Last update Sat Jun  7 19:01:26 2014 Marc Le Labourier
*/

#ifndef __WORLD_H__
#define __WORLD_H__

#include <vector>
#include "GameObject.hh"
#include "MapComponent.hh"

namespace Bomb
{
	class World : public GameObject
	{
	public:
		World();

		virtual GameObject	*Clone() const;
		bool	Collider(IEntity *, double, double);
		void	RemoveEntity(size_t, size_t, int id = -1);
		void	AddEntity(IEntity *, size_t, size_t);
		std::vector<IEntity *>	*OnCell(size_t, size_t);
	};
}

#endif
