/*
** TimerComponent.hh for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Bomberman/Header
**
** Made by hadrien lejard         
** Login   <lejard_h@epitech.net>
**
** Started on  mar. juin  03 17:20:47 2014 hadrien lejard         
** Last update mar. juin  03 17:20:47 2014 hadrien lejard         
*/

#ifndef __TIMERCOMPONENT_HH__
# define __TIMERCOMPONENT_HH__

#include <sys/time.h>
#include "Timer.hh"
#include "Component.hh"

namespace Bomb
{
	class TimerComponent : public BaseComponent
	{
	public:
		TimerComponent(int timer);

		void	Start();
		void	Update();
		void	OnEvent(Event::Event *);

		bool 	IsDone() const;
		bool	IsStart() const;

	private:
		int		_timer;
		bool	_start;
		bool	_done;
		TimeCounter	_counter;
	};
}

#endif