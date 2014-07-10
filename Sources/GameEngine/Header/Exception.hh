//
// Exception.hh for  in /home/lelabo_m/rendu/cpp_bomberman/GameEngine
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Wed Jun  4 21:31:21 2014 Marc Le Labourier
// Last update Thu Jun  5 10:36:13 2014 Marc Le Labourier
//

#ifndef EXCEPTION_HH_
# define EXCEPTION_HH_

#include <string>
#include <stdexcept>

namespace Bomb
{
  class EngineException : public std::runtime_error
  {
  public:
    EngineException(std::string const &msg);
    virtual ~EngineException() throw ();
  };
}

extern std::string*	exceptmsg;

#endif /* !EXCEPTION_HH_ */
