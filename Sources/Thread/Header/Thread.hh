/*
** Thread.hh for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Thread
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  mar. mai  20 15:19:07 2014 hadrien lejard
// Last update Thu Jun  5 10:36:07 2014 Marc Le Labourier
*/

#ifndef __THREAD_HH__
# define __THREAD_HH__

#include <string>
#include <pthread.h>
#include <stdexcept>
#include "Mutex.hh"
#include "CondVar.hh"

typedef void * (*fct)(void *);

class Thread
{
public:
  class ThreadException : public std::runtime_error
  {
  public:
    ThreadException(std::string const &msg);
    virtual ~ThreadException() throw ();
  };
  enum Status { Sleeping, Running, Dead};

  Thread(void);
  Thread(fct f, void *arg);
  ~Thread(void);

  void 			run(void);
  void 			join(void);

  enum Status   	getStatus(void) const;

  void          	setRoutine(fct);
  void          	setArg(void *);
  void			*operator()(void);

private:
  static void		*routine(void *arg);
  fct			_func;
  void			*_arg;
  Status		_status;
  pthread_t		_thread;
};

class TaskThread
{
public:
  TaskThread(fct init, fct f, void *arg);
  ~TaskThread(void);
  void 			run(void);
  void 			join(void);
  void			update(void);
  void			wait(void);
  void			stop(void);
  static void		*loop(void *);
  void			mainloop(void);
private:
  Thread		*_th;
  Mutex			*_mutex;
  CondVar		*_cond;
  bool			_running;
  fct			_init;
  fct			_func;
  void			*_arg;
  bool			_finish;
};

#endif /* !__THREAD_HH__ */
