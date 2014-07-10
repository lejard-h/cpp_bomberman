/*
** ScopedLock.hh for Bomberman7 in /home/lejard_h/rendu/cpp_bomberman/Thread
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  mar. mai  20 15:36:41 2014 hadrien lejard
// Last update Thu Jun  5 22:18:32 2014 Marc Le Labourier
*/

#ifndef __SCOPEDLOCK_HH__
# define __SCOPEDLOCK_HH__

#include "Mutex.hh"

class ScopedLock
{
private:
  Mutex        *_mutex;

public:
  ScopedLock(Mutex *);
  ~ScopedLock(void);
};

#endif /* !__SCOPEDLOCK_HH__ */
