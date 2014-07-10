/*
** Mutex.hh for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Thread
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  mar. mai  20 15:33:54 2014 hadrien lejard
// Last update Thu Jun  5 16:17:22 2014 Marc Le Labourier
*/

#ifndef __IMUTEX_HH__
# define __IMUTEX_HH__

#include <pthread.h>

class Mutex
{
private:
  pthread_mutex_t       *_mutex;

public:
  Mutex();
  virtual ~Mutex(void);
  virtual void lock(void);
  virtual void unlock(void);
  virtual bool trylock(void);
  virtual pthread_mutex_t *getMutex(void) const;
};

#endif /* !__IMUTEX_HH__ */
