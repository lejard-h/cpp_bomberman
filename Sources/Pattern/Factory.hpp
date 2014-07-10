/*
** Factory.hpp for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Pattern
**
** Made by hadrien lejard         
** Login   <lejard_h@epitech.net>
**
** Started on  mar. mai  20 14:50:49 2014 hadrien lejard         
** Last update mar. mai  20 14:50:49 2014 hadrien lejard         
*/

#ifndef __FACTORY_HPP__
# define __FACTORY_HPP__

#include <map>
#include <string>
#include "Prototype.hh"

namespace Pattern
{
template <class Object, class Key = std::string>
  class Factory
  {
  private:
    static std::map<Key, Object *> 	map;
  public:
    static void Register(Key key,Object* obj)
    {
      if (map.find(key) == map.end())
        map[key] = obj;
    }

    Object* Create(const Key& key)
    {
      Object *tmp = 0;

      typename std::map<Key, Object*>::iterator it = map.find(key);
      if (it != map.end())
        tmp = ((*it).second)->Clone();
      return tmp;
    }
  };

  template <typename Object, typename Key>
  std::map<Key,Object*> Factory<Object,Key>::map = std::map<Key, Object*>();
}

#endif /* __FACTORY_HPP__ */