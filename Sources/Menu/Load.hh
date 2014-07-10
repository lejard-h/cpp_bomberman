//
// Load.hh for  in /home/maigna_j/rendu/cpp_bomberman/Menu
//
// Made by jeremy maignan
// Login   <maigna_j@epitech.net>
//
// Started on  Tue Jun  3 09:48:49 2014 jeremy maignan
// Last update Sun Jun 15 11:52:33 2014 jeremy maignan
//

#ifndef LOAD_HH_
#define LOAD_HH_

#include <vector>
#include <map>

#include "Graphics.hpp"
#include "Menu.hh"
#include "Welcome.hh"

int launchgame();

class Load : public Menu
{
private:
  static Load					*_Inst;
  std::vector<std::string>			_Backup;
  int					_Selected;
  std::map<std::string, sf::Sprite *>		_SpriteList;
public:
  Load();
  ~Load();
  void			Run();
  void			Display();
  std::vector<std::string>			Parse();
  void			GetScreenShot();
  void			SetBackup(std::vector<std::string> &);
  static Load		*Instance();
  void			CheckSelected(const sf::Event &);
};
#endif
