//
// Opponent.hh for  in /home/maigna_j/rendu/cpp_bomberman/Menu
//
// Made by jeremy maignan
// Login   <maigna_j@epitech.net>
//
// Started on  Thu May 29 14:55:51 2014 jeremy maignan
// Last update Sat Jun 14 23:43:41 2014 Imad Roughi
//

#ifndef OPPONENT_HH_
#define OPPONENT_HH_

#include <vector>

#include "Graphics.hpp"
#include "Playlist.hh"
#include "Menu.hh"
#include "Score.hh"
#include "Controls.hh"
#include "Podium.hh"

int launchgame();

class Opponent : public Menu
{
 private:
  static Opponent			*_Inst;
  Score					*_Score;
  Controls				*_Cont;
  Podium				*_Podium;
  std::vector<sf::Sprite *>		_Pic;
  int					_Number;
  int					_Level;
public:
  Opponent();
  ~Opponent();
  void			Run();
  void			Display();
  void			loadLevel();
  static Opponent      	*Instance();
};
#endif
