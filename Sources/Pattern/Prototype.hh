/*
** Prototype.hh for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Pattern
**
** Made by hadrien lejard         
** Login   <lejard_h@epitech.net>
**
** Started on  mar. mai  20 14:56:30 2014 hadrien lejard         
** Last update mar. mai  20 14:56:30 2014 hadrien lejard         
*/

#ifndef __PROTOTYPE_HH__
# define __PROTOTYPE_HH__

namespace Pattern
{
template <typename T>
	class IPrototype
	{
	public:
		virtual ~IPrototype() {};
		virtual T*	Clone() const = 0;
	};
}

#endif /*__PROTOTYPE_HH__ */