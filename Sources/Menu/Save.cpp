//
// Save.cpp for  in /home/maigna_j/rendu/cpp_bomberman/Menu
//
// Made by jeremy maignan
// Login   <maigna_j@epitech.net>
//
// Started on  Tue Jun  3 09:46:57 2014 Imad Roughi
// Last update Sat Jun  7 17:08:20 2014 Imad Roughi
//

#include <iostream>
#include <unistd.h>
#include <fstream>
#include <vector>

#include "Graphics.hpp"
#include "Menu.hh"
#include "Save.hh"

Save	*Save::_Inst= 0;

Save::Save()
{
  this->_Window = getWindow();
  this->LoadSprite("./resource/saveBg.png", &this->_Sprite);
  this->_Selected = -1;
}

Save	*Save::Instance()
{
  if (Save::_Inst == 0)
    Save::_Inst = new Save();
  return (_Inst);
}

void	Save::GetScreenShot()
{
  std::vector<std::string>::iterator	filename = this->_Backup.begin();
  unsigned int				i = 1;

  while (i < this->_Backup.size())
    {
      if ((*filename).find("Empty") > 200)
	this->LoadSprite("../Saves/" + (*filename) + ".jpg", &this->_SpriteList[(*filename)]);
      i++;
      filename++;
    }
}

void Save::Parse()
{
  std::string		line;
  std::ifstream		myfile("../Saves/Saves.txt");

  this->_Backup.clear();
  if (myfile.is_open())
    {
      while (getline(myfile,line))
	this->_Backup.push_back(line);
      myfile.close();
    }
  else
    std::cerr << "Can not open back-up file" << std::endl;
}

void	Save::Display()
{
  std::vector<std::string>::iterator game = this->_Backup.begin();
  unsigned int i = 1;

  this->SetSprite(this->_Sprite, -300, 0);
  while (i <= this->_Backup.size())
    {
      if (i == this->_Selected)
	{
	  this->SetSprite(this->_SpriteList[*game], 900, 240);
	  this->SetText(*game, "./resource/plok.ttf", 40, sf::Color(255, 140, 0, 255), 150, 200 + (70 * (i - 1)));
	}
      else
	this->SetText(*game, "./resource/plok.ttf", 40, sf::Color::Green, 150, 200 + (70 * (i - 1)));
      game++;
      i++;
    }
  this->SetText("SAVE", "./resource/plok.ttf", 100, sf::Color::Green, 700, 50);
  this->SetText("BACK", "./resource/plok.ttf", 50, sf::Color::Green, 50, 950);
  this->SetText("SAVE", "./resource/plok.ttf", 50, sf::Color::Green, 1550, 950);
}

void	Save::Run()
{
  sf::Event	event;

  this->Parse();
  this->GetScreenShot();
  while (this->_Window->isOpen())
    {
      while (this->_Window->pollEvent(event))
	{
	  this->Quit(event);
	  if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	    {
	      if (CheckEvent(event, 15, 285, 970, 1045))
		return;
	      else if (CheckEvent(event, 1520, 1770, 970, 1045))
		std::cout << "next\n";
	      else if (CheckEvent(event, 680, 1025, 970, 1045))
		std::cout << "delete\n";// supprimer dans le fichier txt et remplacer par empty et supprimer l'image
	      else if (CheckEvent(event ,35, 690, 196, 270) && this->_Backup[0].find("Empty") > 200)
		this->_Selected = 1;
	      else if (CheckEvent(event, 35, 690, 270, 342) && this->_Backup[1].find("Empty") > 200)
		this->_Selected = 2;
	      else if (CheckEvent(event, 35, 690, 342, 414) && this->_Backup[2].find("Empty") > 200)
		this->_Selected = 3;
	      else if (CheckEvent(event, 35, 690, 414, 488) && this->_Backup[3].find("Empty") > 200)
		this->_Selected = 4;
	      else if (CheckEvent(event, 35, 690, 488, 557) && this->_Backup[4].find("Empty") > 200)
		this->_Selected = 5;
	      else if (CheckEvent(event, 35, 690, 557, 627) && this->_Backup[5].find("Empty") > 200)
		this->_Selected = 6;
	      else if (CheckEvent(event, 35, 690, 627, 701) && this->_Backup[6].find("Empty") > 200)
		this->_Selected = 7;
	      else if (CheckEvent(event, 35, 690, 701, 777) && this->_Backup[7].find("Empty") > 200)
		this->_Selected = 8;
	      else if (CheckEvent(event, 35, 690, 777, 849) && this->_Backup[8].find("Empty") > 200)
		this->_Selected = 9;
	      else if (CheckEvent(event, 35, 690, 849, 926) && this->_Backup[9].find("Empty") > 200)
		this->_Selected = 10;
	    }
	}
      this->_Window->clear();
      this->Display();
      this->_Window->display();
    }
}
