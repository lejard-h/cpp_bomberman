//
// Opponent.cpp for  in /home/maigna_j/rendu/cpp_bomberman
//
// Made by jeremy maignan
// Login   <maigna_j@epitech.net>
//
// Started on  Tue Jun 10 15:59:24 2014 jeremy maignan
// Last update Sun Jun 15 14:46:20 2014 jeremy maignan
//

#include "Graphics.hpp"
#include <sstream>
#include <iostream>
#include <unistd.h>

#include "Opponent.hh"
#include "Welcome.hh"

Opponent *Opponent::_Inst = 0;

class Score;
Opponent::Opponent()
{
  this->_Podium = Podium::Instance();
  this->_Score = Score::Instance();
  this->_Window = getWindow();
  this->_Number = 0;
  this->_Level = 0;
  this->_T = new sf::Texture();
}

Opponent::~Opponent()
{
  this->_Pic.clear();
}

Opponent	*Opponent::Instance()
{
  if (Opponent::_Inst == 0)
    Opponent::_Inst = new Opponent();
  return (_Inst);
}

void	Opponent::loadLevel()
{
  this->LoadSprite2(RESOURCEPATH"cloud.jpg", &this->_Sprite);
  this->_Pic.clear();
  sf::Sprite *Noob = new sf::Sprite();
  this->LoadSprite(RESOURCEPATH"noob.png", &Noob);
  this->_Pic.push_back(Noob);

  sf::Sprite *Bof = new sf::Sprite();
  this->LoadSprite(RESOURCEPATH"bof.png", &Bof);
  this->_Pic.push_back(Bof);

  sf::Sprite *Boss = new sf::Sprite();
  this->LoadSprite(RESOURCEPATH"boss.png", &Boss);
  this->_Pic.push_back(Boss);
}

void Opponent::Display()
{
  std::string			str;
  std::stringstream		ss;
  std::vector<std::string>	name;

  name.push_back("Noob");
  name.push_back("Bof");
  name.push_back("Boss");

  ss << this->_Number;
  str = ss.str();
  this->SetSprite(this->_Sprite, 0, 0);
  this->SetSprite(this->_Pic[this->_Level], 800, 200);
  this->SetText("NUMBER", "plok", 60, sf::Color(255, 140, 0, 255), 150, 300);
  this->SetText("-", "arial", 70, sf::Color(255, 140, 0, 255), 170, 400);
  this->SetText(str, "plok", 60, sf::Color(255, 140, 0, 255), 280, 400);
  this->SetText("+", "arial", 70, sf::Color(255, 140, 0, 255), 470, 400);
  this->SetText("LEVEL", "plok", 60, sf::Color(255, 140, 0, 255), 180, 600);
  this->SetText("<", "arial", 70, sf::Color(255, 140, 0, 255), 140, 700);
  this->SetText(name[this->_Level], "plok", 60, sf::Color(255, 140, 0, 255), 210, 700);
  this->SetText(">", "arial", 70, sf::Color(255, 140, 0, 255), 490, 700);
  this->SetText("BACK", "plok", 50, sf::Color(255, 140, 0, 255), 50, 950);
  this->SetText("OPPONENT", "plok", 100, sf::Color(255, 140, 0, 255), 500, 50);
  this->SetText("PLAY", "plok", 50, sf::Color(255, 140, 0, 255), 1550, 950);
}

void Opponent::Run()
{
  sf::Event	event;

  this->loadLevel();
  this->PlaySound("yay");
  Sound *sound;
  Playlist *SoundContent = Playlist::getPlaylist();
  sound = SoundContent->getMusic("menu");
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
	      else if (CheckEvent(event,1520, 1770, 970, 1045))
		{
		  G_GameSettings->nb_ia = this->_Number;
		  G_GameSettings->ialevel = Settings::IAMode(this->_Level);
		  Welcome *Welcome = Welcome::Instance();
		  this->_Window->setVisible(false);
		  sound->pauseSound();
		  launchgame();
		  this->_Window->setVisible(true);
		  this->_Podium->Run();
		  //		  this->_Score->Run(1);
		  Welcome->Run();
		}
	      else if (CheckEvent(event,160, 200, 427, 475) && this->_Number != 0)
		this->_Number--;
	      else if (CheckEvent(event,465, 515, 427, 475) && this->_Number != 20)
		this->_Number++;
	      else if (CheckEvent(event,135, 195, 730, 795) && this->_Level != 0)
		this->_Level--;
	      else if (CheckEvent(event,480, 540, 730, 795) && this->_Level != 2)
		this->_Level++;
	    }
	}
      this->_Window->clear(sf::Color(255, 255, 255, 255));
      this->Display();
      this->_Window->display();
    }
}
