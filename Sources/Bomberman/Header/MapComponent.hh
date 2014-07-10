/*
** MapComponent.hh for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Bomberman/Header
**
** Made by hadrien lejard         
** Login   <lejard_h@epitech.net>
**
** Started on  dim. mai  25 15:57:49 2014 hadrien lejard         
** Last update dim. mai  25 15:57:49 2014 hadrien lejard         
*/

#ifndef __MAPCOMPONENT_HH__
# define __MAPCOMPONENT_HH__

#include <cmath>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include "Settings.hpp"
#include "Component.hh"
#include "SysGame.hh"
#include "PositionComponent.hh"
#include "PhysicComponent.hh"

namespace Bomb
{

	#define SQUARE(X)	(X*X)

	class MapComponent : public BaseComponent
	{
	public:
		MapComponent();
		MapComponent(size_t size_x, size_t size_y);
		MapComponent(std::string const &);

		void	dump() const;
		void	AddEntity(IEntity *);
		void	AddEntity(IEntity *, size_t, size_t);
		void	RemoveEntity(size_t, size_t, int id = -1);
		bool	EmptyCell(size_t, size_t) const;
		bool	ValidCell(size_t, size_t) const;
		bool	Collider(IEntity *, double x, double y) const;
		bool	IsOnCell(size_t, size_t, int id) const;
		bool	IsTypeOnCell(size_t, size_t, enum GameObjectTag) const;
		std::vector<IEntity *>	*OnCell(size_t, size_t);
		void	UpdateEntity(IEntity *, size_t, size_t);
		std::string	Load(std::string const &);
		void	LoadPlayer(std::vector<Settings::SavePlayer *> &);
		void	Save(std::string const &);

		size_t	GetWidth() const;
		size_t	GetHeight() const;
		void	Start();
		void	Update();
		void	Destroy();

	private:
		size_t	_x;
		size_t	_y;
		std::string	_fileMap;
		std::vector<std::vector<IEntity *>*>	*_map;
		void	RandomMap();
		void	DelimitMap();
		bool	IsEnoughSpace(size_t, size_t);
		void	ParseMap(std::iostream &);
		void	CreateMap();
		void	InitPlayers();
	};
}

#endif