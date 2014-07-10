//
// Podium.hh for  in /home/maigna_j/rendu/cpp_bomberman/Sources/Menu
//
// Made by jeremy maignan
// Login   <maigna_j@epitech.net>
//
// Started on  Sat Jun 14 17:57:48 2014 jeremy maignan
// Last update Sun Jun 15 20:03:03 2014 Imad Roughi
//

#ifndef PODIUM_HH_
#define PODIUM_HH_

#include <utility>
#include <algorithm>
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include "Graphics.hpp"
#include "Menu.hh"
#include "Score.hh"

class Player;

class Podium : public Menu
{
private:
  static Podium			*_Inst;
  Score				*_Score;
  sf::Sprite			*_Podium;
  std::map<int, sf::Color>	colorPod;
  std::vector<sf::Sprite*>	_Character;
public:
  Podium();
  ~Podium();
  void		Run();
  void		Display();
  void		dumpScore();
  void		InitCharacter();
  static Podium	*Instance();
};

#endif
