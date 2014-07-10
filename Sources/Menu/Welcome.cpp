//
// Welcome.cpp for  in /home/maigna_j/rendu/cpp_bomberman/Bomberman
//
// Made by jeremy maignan
// Login   <maigna_j@epitech.net>
//
// Started on  Tue Jun 10 15:56:10 2014 jeremy maignan
// Last update Sat Jun 14 18:55:59 2014 Imad Roughi
//

#include <iostream>
#include <unistd.h>
#include <map>
#include <unistd.h>

#include "Graphics.hpp"
#include "Score.hh"
#include "Mode.hh"
#include "Welcome.hh"
#include "Credit.hh"
#include "Load.hh"
#include "Save.hh"
#include "Option.hh"
#include "Controls.hh"
#include "Camera.hh"

Welcome *Welcome::_Inst = 0;

Welcome::Welcome()
{
  this->_Window = getWindow();
  this->_Score = Score::Instance();
  this->_Mode = Mode::Instance();
  this->_Credit = Credit::Instance();
  this->_Load = Load::Instance();
  this->_Option = Option::Instance();
  this->_T = new sf::Texture();
}

Welcome::~Welcome()
{
  delete this->_Sprite;
  this->_Sprite = 0;
  delete this->_T;
  this->_T = 0;
}

Welcome *Welcome::Instance()
{
  if (_Inst == 0)
    _Inst = new Welcome();
  return (_Inst);
}

void Welcome::Display()
{
  this->SetSprite(this->_Sprite, 0, 0);
  this->SetText("PLAY", "plok", 80, sf::Color::Black, 750, 300);
  this->SetText("LOAD", "plok", 80, sf::Color::Black, 750, 410);
  this->SetText("OPTIONS", "plok", 80, sf::Color::Black, 640, 520);
  this->SetText("SCORES", "plok", 80, sf::Color::Black, 680, 630);
  this->SetText("CREDITS", "plok", 80, sf::Color::Black, 640, 740);
  this->SetText("EXIT", "plok", 80, sf::Color::Black, 750, 850);
  this->SetText("Beta V2.3.6", "plok", 20, sf::Color::Black, 1700, 1000);
}

void Welcome::Run()
{
  sf::Event event;

  this->PlaySound("menu");
  this->LoadSprite2(RESOURCEPATH"Menu.png", &this->_Sprite);
  while (this->_Window->isOpen())
    {
      this->_Window->clear();
      this->Display();
      this->_Window->display();
      while (this->_Window->pollEvent(event))
	{
	  this->Quit(event);
	  if (event.type == sf::Event::MouseButtonPressed &&
	      event.mouseButton.button == sf::Mouse::Left)
	    {
	      if (CheckEvent(event, 755, 1175, 885, 970))
		this->_Window->close();
	      else if (CheckEvent(event, 640, 1215, 775, 855))
		this->_Credit->Run();
	      else if (CheckEvent(event, 690, 1170, 658, 742))
		this->_Score->Run(0);
	      else if (CheckEvent(event, 640, 1215, 545, 630))
		this->_Option->Run();
	      else if (CheckEvent(event, 745, 1080, 435, 515))
		this->_Load->Run();
	      else if (CheckEvent(event, 745, 1080, 320, 400))
		this->_Mode->Run();
	    }
	}
    }
}
