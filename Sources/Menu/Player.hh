//
// Player.hh for  in /home/maigna_j/rendu/cpp_bomberman/Menu
//
// Made by jeremy maignan
// Login   <maigna_j@epitech.net>
//
// Started on  Thu May 29 17:26:26 2014 jeremy maignan
// Last update Thu Jun 12 12:31:39 2014 jeremy maignan
//

#ifndef PLAYER_HH_
#define PLAYER_HH_

#include "Graphics.hpp"
#include <map>
#include <vector>

#include "Menu.hh"
#include "Map.hh"

class Player : public Menu
{
 private:
  static Player			*_Inst;
  Map				*_Map;
  std::vector<sf::Sprite *>      _Character;
  std::vector<std::string>      _Control;
  int				_Index[8];
  std::string			_Name1;
  std::string			_Name2;
  std::string			_Name3;
  std::string			_Name4;
  std::string			_Error;
public:
  Player();
  ~Player();
  void			Run();
  void			Display(int flag = 0);
  void			InitIndex();
  static Player		*Instance();
  void			CatchName(const sf::Event &);
  void			NameInput(std::string *, int);
  int			CheckError();
  void			DisplayName(int);
  void			InitCharacter();
  void			CatchCharacter(const sf::Event &);
  void			CatchController(const sf::Event &);
  void			DisplayCharacter();
  void			DisplayController();
  int			LoadCharacter();
};

#endif
