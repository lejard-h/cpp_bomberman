//
// Mode.cpp for  in /home/maigna_j/rendu/cpp_bomberman/Menu
//
// Made by jeremy maignan
// Login   <maigna_j@epitech.net>
//
// Started on  Thu May 29 17:19:02 2014 jeremy maignan
// Last update Sun Jun 15 19:01:30 2014 jeremy maignan
//

#include <iostream>
#include <unistd.h>

#include "Graphics.hpp"
#include "Menu.hh"
#include "Mode.hh"
#include "Player.hh"

Mode	*Mode::_Inst = 0;

Mode::Mode()
{
  this->_Window = getWindow();
  this->_Player = Player::Instance();
  this->_Description.push_back("Get the highest score.\nKill your opponent with bombs.\nExplode the box to obtain bonus.\n2 minutes per game.");
  this->_Description.push_back("Kill all your opponents.\nThe last player wins the game.\nNo time limit.");
  this->_Description.push_back("Explode the most of box.\n2 minutes per game.");
}

Mode::~Mode()
{
  delete this->_Sprite;
  this->_Description.clear();
}

Mode	*Mode::Instance()
{
  if (Mode::_Inst == 0)
    Mode::_Inst = new Mode();
  return (_Inst);
}

void	Mode::Display()
{
  this->SetSprite(this->_Sprite, 0, 0);
  this->SetText("MODE", "plok", 100, sf::Color::White, 700, 50);
  this->SetText("Classic", "plok", 60, sf::Color::Red, 50, 300);
  this->SetText("Survival", "plok", 60, sf::Color::Green, 50, 450);
  this->SetText("Territory", "plok", 60, sf::Color::Blue, 50, 600);
  this->SetText(this->_Description[G_GameSettings->gamemode], "plok", 40, sf::Color::White, 650, 300);
  this->SetText("BACK", "plok", 50, sf::Color::White, 50, 950);
  this->SetText("NEXT", "plok", 50, sf::Color::White, 1550, 950);
}

void	Mode::Run()
{
  sf::Event	event;

  this->LoadSprite(RESOURCEPATH"mode.png", &this->_Sprite);
  this->PlaySound("yay");
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
		this->_Player->Run();
	      else if (CheckEvent(event, 40, 600, 310, 380))
		G_GameSettings->gamemode = static_cast<Settings::GameMode>(0);
	      else if (CheckEvent(event, 40, 540, 465, 535))
		G_GameSettings->gamemode = static_cast<Settings::GameMode>(1);
	      else if (CheckEvent(event, 40, 425, 625, 690))
	      	G_GameSettings->gamemode = static_cast<Settings::GameMode>(2);
	    }
	}
      this->_Window->clear();
      this->Display();
      this->_Window->display();
    }
}
