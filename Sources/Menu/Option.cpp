//
// Option.cpp for  in /home/maigna_j/rendu/cpp_bomberman/Menu
//
// Made by jeremy maignan
// Login   <maigna_j@epitech.net>
//
// Started on  Wed Jun  4 16:59:02 2014 jeremy maignan
// Last update Sun Jun 15 21:03:33 2014 Imad Roughi
//

#include "Option.hh"

Option	*Option::_Inst = 0;

Option::Option()
{
  std::cout << "Option Build" << std::endl;
  this->_Window = getWindow();
  this->_Controls = Controls::Instance();
  this->_Camera = Camera::Instance();
  this->_T = new sf::Texture();
  this->LoadSprite2(RESOURCEPATH"optionBg.png", &this->_Sprite);
}
Option::~Option()
{
  std::cout << "delete option" << std::endl;
}

Option	*Option::Instance()
{
  if (Option::_Inst == 0)
    Option::_Inst = new Option();
  return (_Inst);
}

void	Option::Display()
{
  std::stringstream ss;
  ss << static_cast<int>(G_GameSettings->volume * 10.0);

  this->SetSprite(this->_Sprite, 0, 0);
  this->SetText("OPTIONS", "plok", 100, sf::Color(255, 255, 102, 255), 600, 50);
  this->SetText("CONTROLS", "plok", 50, sf::Color(255, 255, 102, 255), 750, 400);
  this->SetText("CAMERA", "plok", 50, sf::Color(255, 255, 102, 255), 750, 500);
  this->SetText("AUDIO", "plok", 50, sf::Color(255, 255, 102, 255), 750, 600);
  this->SetText("-", "arial", 100, sf::Color(255, 255, 102, 255), 1100, 550);
  this->SetText(ss.str(), "plok", 60, sf::Color(255, 255, 102, 255), 1300, 580);
  this->SetText("+", "arial", 100, sf::Color(255, 255, 102, 255), 1500, 550);
  this->SetText("BACK", "plok", 50, sf::Color(255, 255, 102, 255), 50, 950);
}

void	Option::Run()
{
  sf::Event	event;

  this->LoadSprite(RESOURCEPATH"optionBg.png", &this->_Sprite);
  this->PlaySound("yay");
  while (this->_Window->isOpen())
    {
      while (this->_Window->pollEvent(event))
	{
	  this->Quit(event);
	  if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
	    std::cout << event.mouseButton.x << /*std::endl;*/ " " << event.mouseButton.y << std::endl;
	    if (CheckEvent(event, 750, 1150, 390, 460))
	      this->_Controls->Run();
	    else if (CheckEvent(event, 750, 1050, 510, 560))
	      this->_Camera->Run();
	    else if (CheckEvent(event, 1085, 1156, 630, 700) && G_GameSettings->volume >= 0.1)
	      {
		this->PlaySound("update");
		G_GameSettings->volume -= 0.1;
	      }
	    else if (CheckEvent(event,1500, 1545, 610, 645) && G_GameSettings->volume < 1.0)
	      {
		G_GameSettings->volume += 0.1;
		this->PlaySound("update");
	      }
	      else if (CheckEvent(event, 15, 285, 970, 1045))
	      return;
	  }
	}
      //      G_GameSettings->volume = this->volume / 10;
      this->_Window->clear();
      this->Display();
      this->_Window->display();
    }
}
