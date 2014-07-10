//
// Load.cpp for  in /home/maigna_j/rendu/cpp_bomberman/Menu
//
// Made by jeremy maignan
// Login   <maigna_j@epitech.net>
//
// Started on  Tue Jun  3 09:46:57 2014 jeremy maignan
// Last update Sun Jun 15 22:00:31 2014 Marc Le Labourier
//

#include <iostream>
#include <unistd.h>
#include <fstream>
#include <vector>

#include "Graphics.hpp"
#include "Menu.hh"
#include "Load.hh"

Load	*Load::_Inst= 0;

Load::Load()
{
  this->_T = new sf::Texture();
  this->LoadSprite(RESOURCEPATH"load.png", &this->_Sprite);
  this->_Window = getWindow();
  this->_Selected = -1;
}

Load::~Load()
{
  delete this->_Sprite;
  this->_SpriteList.clear();
  this->_Backup.clear();
}

Load	*Load::Instance()
{
  if (Load::_Inst == 0)
    Load::_Inst = new Load();
  return (_Inst);
}

void	Load::GetScreenShot()
{
  std::vector<std::string>::iterator	filename = this->_Backup.begin();
  unsigned int				i = 1;

  while (i <= this->_Backup.size())
    {
      if ((*filename).find("Empty") > 200)
       this->LoadSprite("./Saves/" + (*filename) + ".tga", &this->_SpriteList[(*filename)]);
      i++;
      filename++;
    }
}

std::vector<std::string>	Load::Parse()
{
  std::string		line;
  std::ifstream		myfile("./Saves/Saves.txt");

  this->_Backup.clear();
  if (myfile.is_open())
    {
      while (getline(myfile,line))
       this->_Backup.push_back(line);
      myfile.close();
    }
  else
    std::cerr << "Can not open back-up file" << std::endl;
  if (this->_Backup.size() == 0)
    {
      for (int i = 0; i < 10; ++i)
	this->_Backup.push_back("Empty");
    }
  return this->_Backup;
}

void  Load::SetBackup(std::vector<std::string> &b)
{
  this->_Backup = b;
}

void	Load::Display()
{
  std::vector<std::string>::iterator game = this->_Backup.begin();
  unsigned int i = 1;

  this->SetSprite(this->_Sprite, -300, 0);
  while (i <= this->_Backup.size())
    {
      if (static_cast<int>(i) == this->_Selected)
	{
	  this->_SpriteList[*game]->setScale(0.5, 0.5);
	  this->SetSprite(this->_SpriteList[*game], 900, 240);
	  this->SetText(*game, "plok", 40, sf::Color(255, 140, 0, 255), 150, 200 + (70 * (i - 1)));
	}
      else
	this->SetText(*game, "plok", 40, sf::Color::Red, 150, 200 + (70 * (i - 1)));
      game++;
      i++;
    }
  this->SetText("LOAD", "plok", 100, sf::Color::Red, 700, 50);
  this->SetText("BACK", "plok", 50, sf::Color::Red, 50, 950);
  this->SetText("PLAY", "plok", 50, sf::Color::Red, 1550, 950);
}

void	Load::CheckSelected(const sf::Event &event)
{
  if (CheckEvent(event ,35, 900, 196, 270) && this->_Backup[0].find("Empty") > 200)
    this->_Selected = 1;
  else if (CheckEvent(event, 35, 900, 270, 342) && this->_Backup[1].find("Empty") > 200)
    this->_Selected = 2;
  else if (CheckEvent(event, 35, 900, 342, 414) && this->_Backup[2].find("Empty") > 200)
    this->_Selected = 3;
  else if (CheckEvent(event, 35, 900, 414, 488) && this->_Backup[3].find("Empty") > 200)
    this->_Selected = 4;
  else if (CheckEvent(event, 35, 900, 488, 557) && this->_Backup[4].find("Empty") > 200)
    this->_Selected = 5;
  else if (CheckEvent(event, 35, 900, 557, 627) && this->_Backup[5].find("Empty") > 200)
    this->_Selected = 6;
  else if (CheckEvent(event, 35, 900, 627, 701) && this->_Backup[6].find("Empty") > 200)
    this->_Selected = 7;
  else if (CheckEvent(event, 35, 900, 701, 777) && this->_Backup[7].find("Empty") > 200)
    this->_Selected = 8;
  else if (CheckEvent(event, 35, 900, 777, 849) && this->_Backup[8].find("Empty") > 200)
    this->_Selected = 9;
  else if (CheckEvent(event, 35, 900, 849, 926) && this->_Backup[9].find("Empty") > 200)
    this->_Selected = 10;
}


void	Load::Run()
{
  sf::Event	event;

  this->PlaySound("yay");
  this->Parse();
  this->GetScreenShot();
  Sound *sound;
  Playlist *SoundContent = Playlist::getPlaylist();
  sound = SoundContent->getMusic("menu");
  this->LoadSprite(RESOURCEPATH"load.png", &this->_Sprite);
  while (this->_Window->isOpen())
    {
      while (this->_Window->pollEvent(event))
	{
	  this->Quit(event);
	  if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	    {
	      if (CheckEvent(event, 15, 285, 970, 1045))
		return;
	      else if (CheckEvent(event, 1520, 1770, 970, 1045) && this->_Selected != -1)
		{
		  if (this->_Selected >= 1)
		    {
		      G_GameSettings->launchtype = Settings::LOADED;
		      G_GameSettings->Save = "./Saves/" + this->_Backup[this->_Selected - 1] + ".save";
		    }
		  this->_Window->setVisible(false);
		  sound->pauseSound();
		  launchgame();
		  this->_Window->setVisible(true);

		  Welcome *Welcome = Welcome::Instance();
		  Welcome->Run();
		}
	      this->CheckSelected(event);
	    }
	}
      this->_Window->clear();
      this->Display();
      this->_Window->display();
    }
}
