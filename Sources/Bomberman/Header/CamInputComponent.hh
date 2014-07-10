//
// CamInputComponent.hh for  in /home/lelabo_m/rendu/cpp_bomberman/Bomberman
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Sat Jun  7 14:50:36 2014 Marc Le Labourier
// Last update Sat Jun 14 10:48:58 2014 Marc Le Labourier
//

#ifndef CAMINPUTCOMPONENT_HH_
# define CAMINPUTCOMPONENT_HH_

#include "InputComponent.hh"
#include "GraphicContext.hh"

namespace Bomb
{
  class CamInputComponent : public InputComponent
  {
    typedef void (CamInputComponent::*CamFunc)();
  public:
    CamInputComponent(int slot);
    ~CamInputComponent();
    void	Start();
    void	Update();
    int		GetSlot() const;
    void	Up();
    void	Down();
    void	Left();
    void	Right();
    void	Back();
    void	Front();
    glm::mat4	CalcCam();
    void	KeyboardEvent(Event::KeyboardEvent*);
    void	LeapEvent(Event::LeapEvent*);
  private:
    double	GetTime();
    int		_slot;
    bool	_update;
    glm::vec3	_pos;
    glm::vec3	_dir;
    glm::vec3	_up;
    std::map<std::string, CamFunc>	_op;
    Graphic::OGLContext*		_ogl;
    Event::InputEvent*			_lastevent;
  };
}

#endif /* !CAMINPUTCOMPONENT_HH_ */
