/*
** ScoreComponent.hh for  in /home/lejard_h/cpp_bomberman/Bomberman/Header
**
** Made by hadrien lejard         
** Login   <lejard_h@epitech.net>
**
** Started on  mer. juin  11 00:25:30 2014 hadrien lejard         
** Last update mer. juin  11 00:25:30 2014 hadrien lejard         
*/

#ifndef __SCORECOMPONENT_HH__
# define __SCORECOMPONENT_HH__

#include <map>
#include "GameObject.hh"
#include "Component.hh"
#include "Settings.hpp"
#include "ScoreEvent.hh"
#include "Player.hh"

namespace Bomb
{

	class ScoreComponent : public BaseComponent
	{
	public:
		ScoreComponent();
		~ScoreComponent();

		virtual void	OnEvent(Event::Event *);

		void	Update();
		void	UpdateScore(enum Event::ScoreAction, int, int);

		int		GetScore() const;
		void	SetScore(int);
	private:
		int		_score;
		std::map<enum Event::ScoreAction, std::map<enum Settings::GameMode, int> >	_mapPoints;
		std::map<enum GameObjectTag, std::map<enum Settings::GameMode, int> >	_pointsByTarget;
		std::list<Event::Event *> _events;

	};

}

#endif