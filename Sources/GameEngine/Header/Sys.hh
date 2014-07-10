/*
** Engine.hh for Bomberman in /home/lejard_h/rendu/cpp_bomberman/GameEngine
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  mar. mai  20 20:59:48 2014 hadrien lejard
// Last update Wed May 28 10:18:16 2014 Marc Le Labourier
*/

#ifndef __SYS_HH__
# define __SYS_HH__

#include "EventDispatcher.hh"

namespace Bomb
{
  class ISys : public Event::ISubscriber
  {
  public:
    virtual ~ISys() {};
    virtual bool Init() = 0;
    virtual void Destroy() = 0;
    virtual void Update() = 0;
  };
}

#endif /* __SYS_HH__ */
