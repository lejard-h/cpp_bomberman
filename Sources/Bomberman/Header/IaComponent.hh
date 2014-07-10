/*
** IaComponent.hh for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Bomberman/Header
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  ven. mai  30 12:07:15 2014 hadrien lejard
// Last update Thu Jun  5 18:28:29 2014 Marc Le Labourier
*/

#ifndef __IACOMPONENT_HH__
#define __IACOMPONENT_HH__

#include <utility>
#include "InputComponent.hh"
#include "IAactions.hh"
#include "Settings.hpp"

namespace Bomb
{
  class IAactions;

  class IaComponent : public InputComponent
  {
  public:
    IaComponent(Settings::IAMode);
    IaComponent(IaComponent &);
    IaComponent	&operator=(IaComponent &);

    Settings::IAMode	GetMode();
    void	Update();
    void  moveIA(const IAactions &);
    
  private:
    Settings::IAMode	_IAmode;
    //IAactions         *_actions;
    bool                  goToCenter;
    std::pair<int, int>   prevSquare;

    void	EasyMode() const;
    void	MediumMode() const;
    void	HardMode() const;

    
  };
}

#endif
