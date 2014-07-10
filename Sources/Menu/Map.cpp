//
// Map.cpp for  in /home/maigna_j/rendu/cpp_bomberman/Menu
//
// Made by jeremy maignan
// Login   <maigna_j@epitech.net>
//
// Started on  Thu May 29 14:32:45 2014 jeremy maignan
// Last update Sun Jun 15 22:01:23 2014 Marc Le Labourier
//

#include <iostream>
#include <unistd.h>
#include <sstream>
#include <string>

#include "Graphics.hpp"
#include "Menu.hh"
#include "Map.hh"

Map	*Map::_Inst = 0;

Map::Map()
{
  this->_Window = getWindow();
  this->_Opponent = Opponent::Instance();
  this->_Number = 0;
  this->LoadMaps();
}

Map::~Map()
{
  this->_Map.clear();
  this->_Name.clear();
  delete this->_Sprite;
  this->_Sprite = 0;
  delete this->_T;
  this->_T = 0;
}

Map	*Map::Instance()
{
  if (Map::_Inst == 0)
    Map::_Inst = new Map();
  return (_Inst);
}

void	Map::LoadMaps()
{
  this->_T = new sf::Texture();
  this->LoadSprite2(RESOURCEPATH"map.png", &this->_Sprite);

  this->_Map.clear();
  this->_Name.clear();
  sf::Sprite *random = new sf::Sprite();
  this->LoadSprite("./Map/random.png", &random);
  this->_Map.push_back(random);

  sf::Sprite *map1 = new sf::Sprite();
  this->LoadSprite("./Map/map1.png", &map1);
  this->_Map.push_back(map1);

  sf::Sprite *map2 = new sf::Sprite();
  this->LoadSprite("./Map/map2.png", &map2);
  this->_Map.push_back(map2);

  sf::Sprite *map3 = new sf::Sprite();
  this->LoadSprite("./Map/map3.png", &map3);
  this->_Map.push_back(map3);

  this->_Name.push_back("Random");
  this->_Name.push_back("Map1");
  this->_Name.push_back("Map2");
  this->_Name.push_back("Map3");
}

void	Map::Display()
{
  std::string			str;
  std::stringstream		ss;
  std::string			str2;
  std::stringstream		ss2;

  ss << G_GameSettings->map.x;
  str = ss.str();
  ss2 << G_GameSettings->map.y;
  str2 = ss2.str();

  this->SetSprite(this->_Sprite, 0, 0);
  this->SetText("MAP", "plok", 100, sf::Color::Green, 700, 50);
  this->SetSprite(this->_Map[this->_Number], 500, 250);
  this->SetText(this->_Name[this->_Number], "plok", 60, sf::Color::Green, 730, 800);
  this->SetText("BACK", "plok", 50, sf::Color::Green, 50, 950);
  this->SetText("NEXT", "plok", 50, sf::Color::Green, 1550, 950);
  this->SetText("<", "arial", 150, sf::Color::Green, 400, 750);
  this->SetText(">", "arial", 150, sf::Color::Green, 1300, 750);
  if (this->_Number == 0)
    {
      this->SetText("X : ", "plok", 50, sf::Color::Green, 400, 930);
      this->SetText("-", "arial", 100, sf::Color::Green, 530, 890);
      this->SetText(str, "plok", 50, sf::Color::Green, 600, 930);
      this->SetText("+", "arial", 100, sf::Color::Green, 730, 900);
      this->SetText("Y : ", "plok", 50, sf::Color::Green, 1000, 930);
      this->SetText("-", "arial", 100, sf::Color::Green, 1130, 890);
      this->SetText(str2, "plok", 50, sf::Color::Green, 1200, 930);
      this->SetText("+", "arial", 100, sf::Color::Green, 1330, 900);
    }
}

void	Map::Run()
{
  sf::Event	event;

  this->PlaySound("yay");
  this->LoadMaps();
  while (this->_Window->isOpen())
    {
      while (this->_Window->pollEvent(event))
	{
	  this->Quit(event);
	  if (event.type == sf::Event::MouseButtonPressed &&
	      event.mouseButton.button == sf::Mouse::Left)
	    {
	      if (CheckEvent(event, 15, 285, 970, 1045))
		return;
	      else if (CheckEvent(event, 1520, 1770, 970, 1045))
		{
		  G_GameSettings->launchtype = Settings::NEWGAME;
		  (this->_Number != 0) ?
		    (G_GameSettings->map.mapType = Settings::MapType(0)) :
		    (G_GameSettings->map.mapType = Settings::MapType(1));
		  G_GameSettings->map.mapPath = "./Map/" + this->_Name[this->_Number] + ".map";
		  this->_Opponent->Run();
		}
	      else if (CheckEvent(event, 390, 510, 820, 925) && this->_Number != 0)
		this->_Number--;
	      else if (CheckEvent(event, 1290, 1400, 820, 925) && this->_Number != 3)
		this->_Number++;
	      if (this->_Number == 0)
		{
		  if (CheckEvent(event, 1128, 1190, 960, 1025) && G_GameSettings->map.y != 10)
		    G_GameSettings->map.y--;
		  else if (CheckEvent(event, 1315, 1390, 960, 1025) && G_GameSettings->map.y != 50)
		    G_GameSettings->map.y++;
		  else if (CheckEvent(event, 515, 585, 960, 1025) && G_GameSettings->map.x != 10)
		    G_GameSettings->map.x--;
		  else if (CheckEvent(event, 725, 788, 960, 1025) && G_GameSettings->map.x != 50)
		    G_GameSettings->map.x++;
		}
	    }
	}
      this->_Window->clear();
      this->Display();
      this->_Window->display();
    }
}
