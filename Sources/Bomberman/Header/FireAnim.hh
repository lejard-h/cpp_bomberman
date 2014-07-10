//
// FireAnim.hh for  in /home/lelabo_m/rendu/cpp_bomberman/Bomberman
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Tue Jun 10 15:54:37 2014 Marc Le Labourier
// Last update Tue Jun 10 16:37:22 2014 Marc Le Labourier
//

#ifndef FIREANIM_HH_
# define FIREANIM_HH_

#include "GameObject.hh"
#include "AudioComponent.hh"
#include "GraphicComponent.hh"

namespace Bomb
{
  class FireAnim : public GameObject
  {
  public:
    FireAnim();
    void		Start();
    virtual GameObject*	Clone() const;
  };
}

#endif /* !FIREANIM_HH_ */
