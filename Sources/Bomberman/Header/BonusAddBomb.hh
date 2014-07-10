/*
** BonusAddBomb.hh for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Bomberman/Header
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  dim. juin  08 17:28:09 2014 hadrien lejard
// Last update Sat Jun 14 21:22:15 2014 Marc Le Labourier
*/

#ifndef __BONUSADDBOMB_HH__
#define __BONUSADDBOMB_HH__

#include "Event.hpp"
#include "GameObject.hh"
#include "BombComponent.hh"
#include "PositionComponent.hh"
#include "Player.hh"
#include "GraphicComponent.hh"

namespace Bomb
{
  class BonusAddBomb : public GameObject
  {
  public:
    BonusAddBomb();

    void	Start();
    void	Update();

    virtual void OnEvent(Event::Event *);

    virtual GameObject	*Clone() const;

  private:
    std::list<Event::Event *>	_events;
    std::string*		_sound;
    std::string*		_soundpath;
  };
}

#endif
