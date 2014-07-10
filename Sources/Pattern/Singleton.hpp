/*
** Singleton.hpp for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Pattern
**
** Made by hadrien lejard         
** Login   <lejard_h@epitech.net>
**
** Started on  mar. mai  20 11:55:36 2014 hadrien lejard         
** Last update mar. mai  20 11:55:36 2014 hadrien lejard         
*/

#ifndef __SINGELTON_HPP__
# define __SINGELTON_HPP__

#include "Mutex.hh"
#include "ScopedLock.hh"

namespace Pattern
{
  template <typename T> 
  class Singleton
  {
  public:
    static T* Get()
    {
      if (!instance)
      {
        ScopedLock lock(mutex);
        if (!instance)
          instance = new T();
      }
      return instance;
    }

    static void Kill()
    {
      if (instance)
        delete instance;
      instance = 0;
    }

  protected:
    static T* instance;
    static Mutex  mutex;

  private:
    T& operator= (const T&){}
  };

template <class T> T* Singleton<T>::instance = 0;
}

#endif /* __SINGLETON_HPP__ */