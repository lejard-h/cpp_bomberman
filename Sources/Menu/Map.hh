//
// Map.hh for  in /home/maigna_j/rendu/cpp_bomberman/Menu
//
// Made by jeremy maignan
// Login   <maigna_j@epitech.net>
//
// Started on  Thu May 29 14:34:21 2014 jeremy maignan
// Last update Sun Jun 15 18:55:01 2014 jeremy maignan
//

#ifndef MAP_HH_
#define MAP_HH_

#include "Graphics.hpp"
#include <string>
#include <vector>
#include <iostream>

#include "Menu.hh"
#include "Opponent.hh"

class Map : public Menu
{
private:
  static Map			*_Inst;
  Opponent			*_Opponent;
  std::vector<sf::Sprite *>	_Map;
  std::vector<std::string>	_Name;
  int				_Number;
public:
  Map();
  ~Map();
  void			Run();
  void			Display();
  static Map		*Instance();
  void			LoadMaps();
};
#endif
