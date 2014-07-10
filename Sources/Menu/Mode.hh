//
// Mode.hh for  in /home/maigna_j/rendu/cpp_bomberman/Menu
//
// Made by jeremy maignan
// Login   <maigna_j@epitech.net>
//
// Started on  Thu May 29 17:20:44 2014 jeremy maignan
// Last update Sun Jun 15 18:58:20 2014 jeremy maignan
//

#ifndef MODE_HH_
#define MODE_HH_

#include "Graphics.hpp"
#include <vector>

#include "Menu.hh"
#include "Player.hh"

class Mode : public Menu
{
private:
  static Mode			*_Inst;
  Player			*_Player;
  std::vector<std::string>	_Description;
public:
  Mode();
  ~Mode();
  void			Run();
  void			Display();
  static Mode		*Instance();
};
#endif
