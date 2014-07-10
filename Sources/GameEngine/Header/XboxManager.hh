//
// XboxManager.hh for  in /home/lelabo_m/rendu/cpp_bomberman/XboxController
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Sun Jun  8 12:12:51 2014 Marc Le Labourier
// Last update Sun Jun 15 18:35:28 2014 Marc Le Labourier
//


#ifndef XBOXMANAGER_HH_
# define XBOXMANAGER_HH_

#include <vector>
#include "SDL.h"
#include <math.h>
#include "Event.hpp"

#define XBOX_BUTTON 14

namespace Event
{
  typedef std::vector<std::vector<int>* >	XboxInput;

  class XboxManager
  {
  public:
    enum XboxCode { A, B, X, Y, LB, RB, BACK, START, MENU, LT, RT, STICK1, STICK2, HAT };
    XboxManager();
    ~XboxManager();
    size_t	NumJoystick();
    bool	HasUpdate();
    bool	HasUpdate(size_t);
    void	Reset();
    void	Update(size_t);
    void	Update();
    int		GetInput(size_t, XboxCode);
    XboxInput*	GetInput();
    void	SetButtons(size_t, size_t, int);
  private:
    std::vector<int>		_CorresHat;
    std::vector<bool>		_update;
    size_t			_num;
    std::vector<SDL_Joystick*>	_joysticks;
    XboxInput			_buttons;
  };

  class XboxEvent : public InputEvent
  {
  public:
    XboxEvent(XboxInput* d, int s, size_t subj = XBOX) : InputEvent(subj), slot(s), data(d)
    {
    }

    virtual Event*              Clone() const
    {
      return (new XboxEvent(data, slot, Subject()));
    }

    int		slot;
    XboxInput*	data;
  };
}

#endif /*!XBOXMANAGER_HH_*/
