//
// CondVar.hh for  in /home/lelabo_m
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Wed May 28 16:37:57 2014 Marc Le Labourier
// Last update Wed May 28 17:50:09 2014 Marc Le Labourier
//

#ifndef CONDVAR_HH_
# define CONDVAR_HH_

#include <pthread.h>
#include "Mutex.hh"

class CondVar
{
private:
  pthread_cond_t	*_cond;
  Mutex			*_mutex;
  bool			_islock;
public:
  CondVar(Mutex *);
  virtual ~CondVar(void);
  virtual void wait(void);
  virtual void signal(void);
  virtual void broadcast(void);
};

#endif /* !CONDVAR_HH_ */
