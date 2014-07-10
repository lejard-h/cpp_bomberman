/*
** ScopedLock.cpp for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Thread
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  mar. mai  20 15:37:47 2014 hadrien lejard
// Last update Thu Jun  5 22:18:17 2014 Marc Le Labourier
*/

#include "ScopedLock.hh"

ScopedLock::ScopedLock(Mutex *mutex) : _mutex(mutex)
{
  this->_mutex->lock();
}

ScopedLock::~ScopedLock(void)
{
  this->_mutex->unlock();
}
