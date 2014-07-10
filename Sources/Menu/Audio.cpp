//
// Option.cpp for  in /home/maigna_j/rendu/cpp_bomberman/Menu
//
// Made by jeremy maignan
// Login   <maigna_j@epitech.net>
//
// Started on  Wed Jun  4 16:59:02 2014 jeremy maignan
// Last update Sun Jun 15 15:45:36 2014 Marc Le Labourier
//

#include "Graphics.hpp"
#include <sstream>
#include <iostream>
#include <unistd.h>

#include "Menu.hh"
#include "Option.hh"
#include "Map.hh"

Option	*Option::_Inst = 0;

Option::Option()
{
  this->_Window = getWindow();
  this->LoadSprite("./resource/optionBg.png", &this->_Sprite);
}

Option	*Option::Instance()
{
  if (Option::_Inst == 0)
    Option::_Inst = new Option();
  return (_Inst);
}

void	Option::Display(std::string &number)
{
  this->SetText("OPTIONS", "./resource/plok.ttf", 100, sf::Color::White, 500, 50);
  this->SetText("BACK", "./resource/plok.ttf", 50, sf::Color(255, 140, 0, 255), 50, 950);
  this->SetText("DEFAULT", "./resource/plok.ttf", 50, sf::Color(255, 140, 0, 255), 700, 950);
  this->SetText("SAVE", "./resource/plok.ttf", 50, sf::Color(255, 140, 0, 255), 1550, 950);

  this->SetText("Audio", "./resource/plok.ttf", 60, sf::Color(255, 140, 0, 255), 150, 300);
  this->SetText("-", "./resource/arial.ttf", 70, sf::Color(255, 140, 0, 255), 170, 400);
  this->SetText(number, "./resource/plok.ttf", 60, sf::Color(255, 140, 0, 255), 280, 400);
  this->SetText("+", "./resource/arial.ttf", 70, sf::Color(255, 140, 0, 255), 470, 400);

  this->SetText("Option2", "./resource/plok.ttf", 60, sf::Color(255, 140, 0, 255), 700, 300);
  this->SetText("Option2", "./resource/plok.ttf", 60, sf::Color(255, 140, 0, 255), 1300, 300);
}

void	Option::Run()
{
  sf::Event	event;
  std::string	str;
  int		volume;

  volume = 5;
  while (this->_Window->isOpen())
    {
      while (this->_Window->pollEvent(event))
	{
	  this->Quit(event);
	  if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
	    if (CheckEvent(event,160, 200, 427, 475) && volume >= 1)
	      volume-= 1;
	    if (CheckEvent(event,465, 515, 427, 475) && volume < 10)
	      volume+= 1;
	    if (CheckEvent(event, 15, 285, 970, 1045))
	      return;
	  }
	}
      std::stringstream ss;
      ss << volume;
      str = ss.str();
      G_GameSettings->volume = (float)volume/10;
      this->_Window->clear();
      this->Display(str);
      this->_Window->display();
    }
}
