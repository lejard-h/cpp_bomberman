/*
** InputComponent.hh for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Bomberman/Header
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  jeu. mai  29 14:19:36 2014 hadrien lejard
// Last update Wed Jun 11 00:36:19 2014 Marc Le Labourier
*/

#ifndef __PLAYERINPUTCOMPONENT_HH__
#define __PLAYERINPUTCOMPONENT_HH__

#include "KeyboardManager.hh"
#include "LeapManager.hh"
#include "XboxManager.hh"
#include "InputComponent.hh"

namespace Bomb
{
  class PlayerInputComponent : public InputComponent
  {
  public:
    PlayerInputComponent(int slot);
    void	Start();
    void	Update();
    int		GetSlot() const;
    void	EventKeyboard(Event::KeyboardEvent *);
    void	EventXbox(Event::XboxEvent *);
  private:
    int		_slot;
    Event::InputEvent*	_lastevent;
  };
}

#endif
