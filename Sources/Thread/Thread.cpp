/*
** Thread.cpp for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Thread
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  mar. mai  20 15:26:14 2014 hadrien lejard
// Last update Thu Jun  5 10:36:00 2014 Marc Le Labourier
*/

#include <stdexcept>
#include <iostream>
#include "Thread.hh"

Thread::ThreadException::ThreadException(std::string const &msg) : std::runtime_error(msg.c_str())
{
}

Thread::ThreadException::~ThreadException() throw ()
{
}

Thread::Thread()  : _func(0), _arg(0), _status(Sleeping)
{
}

Thread::Thread(fct f, void *arg)  : _func(f), _arg(arg), _status(Sleeping)
{
}

Thread::~Thread(void)
{
  _thread = 0;
}

void    Thread::run(void)
{
  if (pthread_create(&this->_thread, 0, Thread::routine, this))
    throw ThreadException("fail to create thread.");
  this->_status = Running;
}

void Thread::join(void)
{
  if (pthread_join(this->_thread, 0))
    {
      this->_status = Dead;
      throw ThreadException("fail to join thread.");
    }
  this->_status = Sleeping;
}

enum Thread::Status Thread::getStatus(void) const
{
  return this->_status;
}

void            *Thread::routine(void *arg)
{
  Thread  *th = reinterpret_cast<Thread *>(arg);
  
  pthread_exit((*th)());
  return 0;
}

void            Thread::setRoutine(fct func)
{
  this->_func = func;
}

void            Thread::setArg(void * arg)
{
  this->_arg = arg;
}

void			*Thread::operator()(void)
{
  return this->_func(this->_arg);
}

/**************/
/* TaskThread */
/**************/

TaskThread::TaskThread(fct init, fct f, void *arg)
{
  _init = init;
  _func = f;
  _arg = arg;
  _th = new Thread(&TaskThread::loop, this);
  _mutex = new Mutex();
  _cond = new CondVar(_mutex);
  _running = false;
}

TaskThread::~TaskThread()
{
  delete _th;
  delete _mutex;
  delete _cond;
}

void	TaskThread::run(void)
{
  _running = true;
  _th->run();
}

void	TaskThread::join(void)
{
  _running = false;
  _cond->signal();
  try
    {
      _th->join();
    }
  catch (Thread::ThreadException& e)
    {
      std::cerr << e.what() << std::endl;
    }
}

void	TaskThread::update(void)
{
  _mutex->lock();
  _cond->signal();
}

void	TaskThread::wait(void)
{
  _cond->signal();
  _cond->wait();
  _mutex->unlock();
}

void	*TaskThread::loop(void *param)
{
  TaskThread*     obj = reinterpret_cast<TaskThread*>(param);

  obj->mainloop();
  return 0;
}

void	TaskThread::mainloop(void)
{
  if (_init)
    (_init)(_arg);
  while (_running)
    {
      _finish = false;
      _mutex->lock();
      _cond->signal();
      _cond->wait();
      if (_running)
	_func(_arg);
      _mutex->unlock();
    }
}

void	TaskThread::stop()
{
  _running = false;
  _cond->signal();
  _mutex->unlock();
  _th->join();
}
