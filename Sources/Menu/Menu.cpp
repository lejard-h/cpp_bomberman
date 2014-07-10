//
// Menu.cpp for  in /home/lelabo_m/rendu/cpp_bomberman
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Sun Jun 15 17:52:10 2014 Marc Le Labourier
// Last update Sun Jun 15 17:52:28 2014 Marc Le Labourier
//

#include <iostream>
#include <unistd.h>
#include <map>
#include <stdlib.h>

#include "Env.hpp"
#include "LoaderSettings.hh"
#include "Graphics.hpp"
#include "Score.hh"
#include "Welcome.hh"
#include "Intro.hh"
#include "Podium.hh"

void		Menu::PlaySound(const std::string &soundname)
{
  Playlist *SoundContent = Playlist::getPlaylist();
  if (soundname != "update")
    {
      SoundContent->playSound(soundname);
      Sound *sound = SoundContent->getMusic(soundname);
      sound->setVolume(G_GameSettings->volume);
    }
  static Sound *menu = SoundContent->getMusic("menu");
  if (soundname == "update")
    menu->setVolume(G_GameSettings->volume);
 }

void Menu::SetText(const std::string &sentence,
		   const std::string &Typo,
		   int size,  sf::Color color,
		   int x,  int y)
{
  sf::Font	t;

  if (Typo == "plok")
    {
      if (!t.loadFromFile(RESOURCEPATH"plok.ttf"))
	std::cerr << "Can not load ttf file" << std::endl;
    }
  else
    {
      if (!t.loadFromFile(RESOURCEPATH"arial.ttf"))
	std::cerr << "Can not load ttf file" << std::endl;
    }
  sf::Text *text = new sf::Text(sentence, t, size);
  text->setColor(color);
  text->setPosition(sf::Vector2f(x, y));
  this->_Window->draw(*text);
  delete text;
}

void	Menu::SetSprite(sf::Sprite *s, int x, int y)
{
  s->setPosition(sf::Vector2f(x, y));
  this->_Window->draw(*s);
}

void	Menu::DrawSquare(int a, int b, int c, int d, const sf::Color &color)
{
  sf::VertexArray *quad = new sf::VertexArray(sf::Quads, 4);

  (*quad)[0].position = sf::Vector2f(a, b);
  (*quad)[0].color = color;
  (*quad)[1].position = sf::Vector2f(c, b);
  (*quad)[1].color = color;
  (*quad)[2].position = sf::Vector2f(c, d);
  (*quad)[2].color = color;
  (*quad)[3].position = sf::Vector2f(a, d);
  (*quad)[3].color = color;
  this->_Window->draw(*quad);
  delete quad;
  quad = 0;
}

sf::RenderWindow *getWindow()
{
  std::vector<sf::VideoMode> size = sf::VideoMode::getFullscreenModes();
  static sf::RenderWindow tmp(size[0], "Bomberman");
  size.clear();
  return (&tmp);
}

void		Menu::Quit(const sf::Event &event)
{
  if (event.type == sf::Event::Closed)
    this->_Window->close();
  else if (event.type == sf::Event::KeyPressed)
    {
      if (event.key.code == sf::Keyboard::Escape)
	this->_Window->close();
    }
}

void	Menu::LoadSprite(const std::string &Path, sf::Sprite **sprite)
{
  sf::Texture *texture = new sf::Texture();
  texture->loadFromFile(Path);
  (*sprite) = new sf::Sprite(*texture);
}

void	Menu::LoadSprite2(const std::string &Path, sf::Sprite **sprite)
{
  _T->loadFromFile(Path);
  (*sprite) = new sf::Sprite(*_T);
}

bool	Menu::CheckEvent(const sf::Event &event, int x_min, int x_max, int y_min, int y_max)
{
  sf::RenderWindow	*w = getWindow();
  sf::Vector2u		tmp = w->getSize();
  int x1, x2, y1, y2;

  x1 = x_min * tmp.x / 1920;
  x2 = x_max * tmp.x / 1920;
  y1 = y_min * tmp.y / 1056;
  y2 = y_max * tmp.y / 1056;
  if (event.mouseButton.x > x1 &&
      event.mouseButton.x < x2 &&
      event.mouseButton.y > y1 &&
      event.mouseButton.y < y2)
    return (true);
  else
    return (false);
}

void	Menu::LoadAlphaNum()
{
  this->_Alpha[sf::Keyboard::A] = "A";
  this->_Alpha[sf::Keyboard::B] = "B";
  this->_Alpha[sf::Keyboard::C] = "C";
  this->_Alpha[sf::Keyboard::D] = "D";
  this->_Alpha[sf::Keyboard::E] = "E";
  this->_Alpha[sf::Keyboard::F] = "F";
  this->_Alpha[sf::Keyboard::G] = "G";
  this->_Alpha[sf::Keyboard::H] = "H";
  this->_Alpha[sf::Keyboard::I] = "I";
  this->_Alpha[sf::Keyboard::J] = "J";
  this->_Alpha[sf::Keyboard::K] = "K";
  this->_Alpha[sf::Keyboard::L] = "L";
  this->_Alpha[sf::Keyboard::M] = "M";
  this->_Alpha[sf::Keyboard::N] = "N";
  this->_Alpha[sf::Keyboard::O] = "O";
  this->_Alpha[sf::Keyboard::P] = "P";
  this->_Alpha[sf::Keyboard::Q] = "Q";
  this->_Alpha[sf::Keyboard::R] = "R";
  this->_Alpha[sf::Keyboard::S] = "S";
  this->_Alpha[sf::Keyboard::T] = "T";
  this->_Alpha[sf::Keyboard::U] = "U";
  this->_Alpha[sf::Keyboard::V] = "V";
  this->_Alpha[sf::Keyboard::W] = "W";
  this->_Alpha[sf::Keyboard::X] = "X";
  this->_Alpha[sf::Keyboard::Y] = "Y";
  this->_Alpha[sf::Keyboard::Z] = "Z";
  this->_Alpha[sf::Keyboard::Numpad0] = "0";
  this->_Alpha[sf::Keyboard::Numpad1] = "1";
  this->_Alpha[sf::Keyboard::Numpad2] = "2";
  this->_Alpha[sf::Keyboard::Numpad3] = "3";
  this->_Alpha[sf::Keyboard::Numpad4] = "4";
  this->_Alpha[sf::Keyboard::Numpad5] = "5";
  this->_Alpha[sf::Keyboard::Numpad6] = "6";
  this->_Alpha[sf::Keyboard::Numpad7] = "7";
  this->_Alpha[sf::Keyboard::Numpad8] = "8";
  this->_Alpha[sf::Keyboard::Numpad9] = "9";
  this->_Alpha[sf::Keyboard::Up] = "Up";
  this->_Alpha[sf::Keyboard::Down] = "Down";
  this->_Alpha[sf::Keyboard::Left] = "Left";
  this->_Alpha[sf::Keyboard::Right] = "Right";
  this->_Alpha[sf::Keyboard::Space] = "Space";
}

void	Menu::LoadNum()
{
  this->_Alpha[sf::Keyboard::Numpad0] = "0";
  this->_Alpha[sf::Keyboard::Numpad1] = "1";
  this->_Alpha[sf::Keyboard::Numpad2] = "2";
  this->_Alpha[sf::Keyboard::Numpad3] = "3";
  this->_Alpha[sf::Keyboard::Numpad4] = "4";
  this->_Alpha[sf::Keyboard::Numpad5] = "5";
  this->_Alpha[sf::Keyboard::Numpad6] = "6";
  this->_Alpha[sf::Keyboard::Numpad7] = "7";
  this->_Alpha[sf::Keyboard::Numpad8] = "8";
  this->_Alpha[sf::Keyboard::Numpad9] = "9";
}

static void	launch()
{
  Settings::LoaderSettings	settings("settings");

  G_GameSettings = settings.GetSettings();
  if (!G_GameSettings)
    G_GameSettings = new Settings::GameContext();
  Intro *tmp = new Intro();
  Welcome *tmp2 = Welcome::Instance();
  tmp2->Run();
  delete tmp;
  settings.SetSettings(G_GameSettings);
}

int main(int ac, char **av)
{
  EnvChecker			isenv;
  if (!isenv.IsSafe())
    {
      std::cerr << "Env is not safe for " << (ac ? av[0] : "bomberman") << std::endl;
      return isenv.Return();
    }
  if (ac == 2)
    system("vlc --play-and-exit --fullscreen --no-loop --no-video-title-show --quiet\
 --mouse-hide-timeout 0 "ASSETPATH"bomberman_intro.mp4 2> /dev/null");
  launch();
  return (isenv.Return());
}
