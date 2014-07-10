//
// Load.hh for  in /home/maigna_j/rendu/cpp_bomberman/Menu
//
// Made by jeremy maignan
// Login   <maigna_j@epitech.net>
//
// Started on  Tue Jun  3 09:48:49 2014 Imad Roughi
// Last update Sat Jun  7 16:49:12 2014 Imad Roughi
//

#ifndef SAVE_HH_
#define SAVE_HH_

#include "Graphics.hpp"
#include <vector>
#include <map>

#include "Menu.hh"

class Save : public Menu
{
private:
  static Save					*_Inst;
  std::vector<std::string>			_Backup;
  unsigned int					_Selected;
  std::map<std::string, sf::Sprite *>		_SpriteList;
public:
  Save();
  void			Run();
  void			Display();
  void			Parse();
  void			GetScreenShot();
  static Save		*Instance();
};
#endif
