//
// fonctor.hh for  in /home/lelabo/rendu/cpp_nibbler/game/patern
//
// Made by lelabo_m
// Login   <lelabo@epitech.net>
//
// Started on  Tue Apr  1 11:50:28 2014 lelabo_m
// Last update Sun May 25 18:36:12 2014 Marc Le Labourier
//

#ifndef FONCTOR_HH_
# define FONCTOR_HH_

#include <iostream>

template <typename T, typename P>
class Fonctor
{
public:
  Fonctor(T* obj, void *(T::*func)(P))
  {
    _inst = obj;
    _func = func;
  }

  ~Fonctor()
  {
  }

  void	*operator()(P data)
  {
    return (_inst->*_func)(data);
  }

  T*	GetInst()
  {
    return _inst;
  }

  void	SetInst(T* newobj)
  {
    _inst = newobj;
  }

  void	SetFunc(void *(T::*func)(P))
  {
    _func = func;
  }

private:
  T	*_inst;
  void	*(T::*_func)(P);
};

#endif /* !FONCTOR_HH_ */
