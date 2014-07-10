/*
** TimerComponent.cpp for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Bomberman
**
** Made by hadrien lejard         
** Login   <lejard_h@epitech.net>
**
** Started on  mar. juin  03 17:24:01 2014 hadrien lejard         
** Last update mar. juin  03 17:24:01 2014 hadrien lejard         
*/

#include "TimerComponent.hh"

Bomb::TimerComponent::TimerComponent(int timer) : _timer(timer * 1000)
{
	this->ctor(Timer_c);
	this->_start = false;
	this->_done = false;
}

void	Bomb::TimerComponent::Start()
{
	this->_start = true;
	this->_counter.Reset();
}

void	Bomb::TimerComponent::OnEvent(Event::Event *ev)
{
	if (ev && ev->Scope() == Event::GAME && ev->Subject() == Event::GAMEPAUSE)
		this->_counter.Pause();
	delete ev;
}

void	Bomb::TimerComponent::Update()
{
	if (this->_start && this->_timer <= this->_counter.GetTime())
		this->_done = true;
}

bool	Bomb::TimerComponent::IsDone() const
{
	return this->_done;
}

bool	Bomb::TimerComponent::IsStart() const
{
	return this->_start;
}