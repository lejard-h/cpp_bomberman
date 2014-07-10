//
// Credit.cpp for  in /home/maigna_j/rendu/cpp_bomberman/menu
//
// Made by jeremy maignan
// Login   <maigna_j@epitech.net>
//
// Started on  Thu May 22 18:40:03 2014 jeremy maignan
// Last update Sun Jun 15 17:01:16 2014 jeremy maignan
//

#include "Graphics.hpp"
#include <iostream>
#include <unistd.h>

#include "Menu.hh"
#include "Credit.hh"

Credit	*Credit::_Inst = 0;

Credit::Credit()
{
  this->_Window = getWindow();
  this->_T = new sf::Texture();
  this->LoadSprite2(RESOURCEPATH"Background.png", &this->_Sprite);
}

Credit::~Credit()
{
  delete this->_Sprite;
  this->_Sprite = 0;
  delete this->_T;
  this->_T = 0;
 }

Credit	*Credit::Instance()
{
  if (Credit::_Inst == 0)
    Credit::_Inst = new Credit();
  return (_Inst);
}

void	Credit::Display()
{
  this->SetSprite(this->_Sprite, 0, 0);
  this->SetText("CREDITS", "plok", 100, sf::Color::White, 600, 60);
  this->SetText("Imad Roughi", "plok", 50, sf::Color::White, 600, 300);
  this->SetText("Marc Le Labourier", "plok", 50, sf::Color::White, 600, 400);
  this->SetText("Hadrien Lejard", "plok", 50, sf::Color::White, 600, 500);
  this->SetText("Guillaume Paris", "plok", 50, sf::Color::White, 600, 600);
  this->SetText("Jeremy Maignan", "plok", 50, sf::Color::White, 600, 700);
  this->SetText("Pierre Yves Thomas", "plok", 50, sf::Color::White, 600, 800);
  this->SetText("BACK", "plok", 50, sf::Color::White, 50, 950);
}

void		Credit::Run()
{
  sf::Event	event;

  this->PlaySound("yay");
  this->LoadSprite2(RESOURCEPATH"Background.png", &this->_Sprite);
  while (this->_Window->isOpen())
    {
      while (this->_Window->pollEvent(event))
	{
	  this->Quit(event);
	  if (event.type == sf::Event::MouseButtonPressed &&
	      event.mouseButton.button == sf::Mouse::Left)
	    {
	      if (this->CheckEvent(event, 15, 285, 970, 1045))
		return;
	      if (this->CheckEvent(event, 590, 1215, 820, 891))
		this->PlaySound("what");
	    }
	}
      this->_Window->clear();
      this->Display();
      this->_Window->display();
    }
}
