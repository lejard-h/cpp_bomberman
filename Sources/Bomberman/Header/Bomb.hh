/*
** Bomb.hh for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Bomberman/Header
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  lun. juin  02 16:27:51 2014 hadrien lejard
// Last update Sat Jun 14 18:54:06 2014 Marc Le Labourier
*/

#ifndef __BOMB_HH__
#define __BOMB_HH__

#include "GameObject.hh"
#include "World.hh"
#include "TimerComponent.hh"
#include "ExplodeComponent.hh"
#include "PositionComponent.hh"
#include "GraphicComponent.hh"
#include "Player.hh"

namespace Bomb
{

	#define NORMAL_BOMB_TIMER	(3)
	#define NORMAL_BOMB_POWER	(1)
	#define NORMAL_BOMB_SIZE	(1)

	class DefaultBomb : public GameObject
	{
	public:
		DefaultBomb();
		int		GetOwner();
		void	SetOwner(int id);

		virtual void	SetSize(int) = 0;

	};

	class NormalBomb : public DefaultBomb
	{
	public:
	  NormalBomb();
	  ~NormalBomb();

	  bool	IsDone();

	  void	Update();
	  void	Destroy();

	  virtual void OnEvent(Event::Event *);
	  void	EventTreatment();
	  virtual GameObject	*Clone() const;
	  void		SetSize(int);
	  size_t	GetSize();

	private:
	  std::list<Event::Event *>	_events;
	  std::string*			_sound;
	  std::string*			_soundpath;
	};
}

#endif
