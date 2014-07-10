/*
** BombComponent.hh for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Bomberman/Header
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  lun. juin  02 13:49:46 2014 hadrien lejard
// Last update Mon Jun  9 14:11:13 2014 Marc Le Labourier
*/

#ifndef __BOMBCOMPONENT_HH__
#define __BOMBCOMPONENT_HH__

#include <map>
#include "Component.hh"
#include "SysGame.hh"
#include "World.hh"
#include "Bomb.hh"

namespace Bomb
{
	enum BombType	{ Normal };

	class BombComponent : public BaseComponent
	{
	public:
		BombComponent();
		BombComponent(BombComponent &);
		BombComponent	&operator=(BombComponent &);
		virtual ~BombComponent();

		std::map<BombType, size_t>	&GetMapNbBomb();
		std::map<BombType, GameObjectTag>	&GetMapObjectsBomb();

		bool	DropBomb(double x, double y, BombType);

		void	IncreaseSizeBombs();

//		void	Start();

		size_t	GetSizeBomb(BombType);
		void	SetSizeBomb(BombType, size_t);

		void	SetNbBomb(BombType, size_t);
		void	AddBomb(BombType);
		void	RemoveBomb(BombType);

	private:
		std::map<BombType, size_t>	_sizeBombs;
		std::map<BombType, size_t>	_bombs;
		std::map<BombType, GameObjectTag>	_objects;
	};
}

#endif
