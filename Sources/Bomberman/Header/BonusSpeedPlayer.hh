/*
** BonusSpeedPlayer.hh for Bomberman in /home/lejard_h/cpp_bomberman/Bomberman/Header
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  mar. juin  10 21:28:20 2014 hadrien lejard
// Last update Sat Jun 14 22:18:31 2014 Marc Le Labourier
*/

#ifndef __BONUSSPEEDPLAYER_HH__
# define __BONUSSPEEDPLAYER_HH__

#include "Event.hpp"
#include "GameObject.hh"
#include "BombComponent.hh"
#include "PositionComponent.hh"
#include "Player.hh"
#include "GraphicComponent.hh"
#include "TimerComponent.hh"
#include "PhysicComponent.hh"
#include "ColliderEvent.hh"

namespace Bomb
{
  class BonusSpeedPlayer : public GameObject
  {
  public:
    BonusSpeedPlayer();

    void	Start();
    void	Update();

    virtual void OnEvent(Event::Event *);

    virtual GameObject	*Clone() const;
    void	EventTreatment();

  private:
    std::list<Event::Event *>	_events;
    int				_idTarget;
    std::string*		_sound;
    std::string*		_soundpath;
  };
}

#endif
