//
// Env.hpp for  in /home/lelabo_m/rendu/cpp_bomberman
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Sat Jun 14 22:56:45 2014 Marc Le Labourier
// Last update Sat Jun 14 23:35:40 2014 Marc Le Labourier
//

#ifndef ENV_HPP_
# define ENV_HPP_

#include <stdlib.h>

class EnvChecker
{
public:
  EnvChecker()
  {
  }
  ~EnvChecker()
  {
  }
  bool	IsSafe() const
  {
    if (!getenv("PATH") || !getenv("USER") || !getenv("_")
	|| !getenv("DISPLAY") || !getenv("TERM") || !getenv("SHELL"))
      return false;
    return true;
  }
  int	Return() const
  {
    if (!IsSafe())
      return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
  }
};

#endif /* !ENV_HPP_ */
