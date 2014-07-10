//
// Cam.hh for  in /home/lelabo_m/rendu/cpp_bomberman/Bomberman
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Sat Jun  7 17:40:28 2014 Marc Le Labourier
// Last update Sat Jun  7 17:58:11 2014 Marc Le Labourier
//

#ifndef CAM_HH_
# define CAM_HH_

#include "GameObject.hh"
#include "CamInputComponent.hh"

namespace Bomb
{
  class GameCam : public GameObject
  {
  public:
    GameCam();
    void	Start();
    virtual GameObject  *Clone() const;
  private:
    void        InitInput();
  };
}

#endif /* !CAM_HH_ */
