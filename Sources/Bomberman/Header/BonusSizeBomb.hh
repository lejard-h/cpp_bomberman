/*
** BonusSizeBomb.hh for Bomberman in /home/lejard_h/cpp_bomberman/Bomberman/Header
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  mar. juin  10 23:26:17 2014 hadrien lejard
// Last update Sat Jun 14 21:51:06 2014 Marc Le Labourier
*/

#ifndef __BONUSSIZEBOMB_HH__
#define __BONUSSIZEBOMB_HH__

#include "Event.hpp"
#include "GameObject.hh"
#include "BombComponent.hh"
#include "PositionComponent.hh"
#include "Player.hh"
#include "GraphicComponent.hh"


namespace Bomb
{

  class BonusSizeBomb : public GameObject
  {
  public:
    BonusSizeBomb();

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
