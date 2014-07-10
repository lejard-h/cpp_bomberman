//
// Menu.hh for  in /home/maigna_j/rendu/cpp_bomberman/menu
//
// Made by jeremy maignan
// Login   <maigna_j@epitech.net>
//
// Started on  Thu May 22 13:00:13 2014 jeremy maignan
// Last update Fri Jun 13 15:55:18 2014 jeremy maignan
//

#ifndef MENU_HH_
#define MENU_HH_

#include <map>
#include "KeyboardManager.hh"
#include "Graphics.hpp"
#include "Settings.hpp"
#include "Playlist.hh"

#define RESOURCEPATH ASSETPATH"Menu/"

extern std::map<std::string, int >			*G_AlphaSFtoSD;
sf::RenderWindow *getWindow();

class Menu
{
protected:
  sf::Sprite		*_Sprite;
  sf::Texture		*_T;
  sf::RenderWindow	*_Window;
  std::map<sf::Keyboard::Key, std::string> _Alpha;

  void			PlaySound(const std::string &);
  void			SetSprite(sf::Sprite *, int, int);
  void			SetText(const std::string &, const std::string &, int, sf::Color, int, int);
  void			Quit(const sf::Event &);
  void			LoadSprite(const std::string &, sf::Sprite **);
  void			LoadSprite2(const std::string &, sf::Sprite **);
  bool			CheckEvent(const sf::Event &, int, int, int, int);
  void			DrawSquare(int, int, int, int, const sf::Color &);
  void			LoadAlphaNum();
  void			LoadNum();
};

#endif
