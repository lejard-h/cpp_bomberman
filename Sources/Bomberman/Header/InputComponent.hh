/*
** InputComponent.hh for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Bomberman/Header
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  jeu. mai  29 14:19:36 2014 hadrien lejard
// Last update Sat Jun 14 10:59:46 2014 Marc Le Labourier
*/

#ifndef __INPUTCOMPONENT_HH__
# define __INPUTCOMPONENT_HH__

#include <queue>
#include "SysGame.hh"
#include "Component.hh"
#include "EventDispatcher.hh"
#include "Settings.hpp"
#include "PositionComponent.hh"
#include "PhysicComponent.hh"
#include "KeyboardManager.hh"
#include "LeapManager.hh"

namespace Bomb
{
	class InputComponent : public BaseComponent
	{
	public:
		InputComponent();

    void	Destroy();

    void	OnEvent(Event::Event *);

  protected:
    std::list<Event::Event *> _events;
    std::map<std::string, double>	_rMap;

    void	Move(std::string const &) const;
    void  Move(int) const;
    void	PutBomb() const;
  };
}

#endif
