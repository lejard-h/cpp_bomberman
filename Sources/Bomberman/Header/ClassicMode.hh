/*
** ClassicModeComponent.hh for Bomberman in /home/lejard_h/cpp_bomberman/Bomberman/Header
**
** Made by hadrien lejard         
** Login   <lejard_h@epitech.net>
**
** Started on  mer. juin  11 13:18:16 2014 hadrien lejard         
** Last update mer. juin  11 13:18:16 2014 hadrien lejard         
*/

#ifndef __CLASSICMODE_HH__
# define __CLASSICMODE_HH__

#include "GameObject.hh"
#include "TimerComponent.hh"
#include "SysGame.hh"
#include "Types.hh"
#include "ScoreComponent.hh"

namespace Bomb
{

	class ClassicMode : public GameObject
	{
	public:
		ClassicMode();
		~ClassicMode();

		void	Update();
		void	Destroy();

		void	SaveScore();

		GameObject	*Clone() const;

	};

}

#endif