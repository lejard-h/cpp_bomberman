//
// Exception.cpp for  in /home/lelabo_m/rendu/cpp_bomberman/GameEngine
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Wed Jun  4 21:34:31 2014 Marc Le Labourier
// Last update Thu Jun  5 10:35:27 2014 Marc Le Labourier
//

#include "Exception.hh"

std::string*	exceptmsg = 0;

Bomb::EngineException::EngineException(std::string const &msg) : std::runtime_error(msg.c_str())
{
}

Bomb::EngineException::~EngineException() throw()
{
}
