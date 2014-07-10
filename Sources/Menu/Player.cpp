//
// Player.cpp for  in /home/maigna_j/rendu/cpp_bomberman
//
// Made by jeremy maignan
// Login   <maigna_j@epitech.net>
//
// Started on  Wed Jun 11 23:38:34 2014 jeremy maignan
// Last update Sun Jun 15 20:39:14 2014 Imad Roughi
//

#include "Graphics.hpp"
#include <iostream>
#include <unistd.h>

#include "Menu.hh"
#include "Player.hh"
#include "Map.hh"

Player	*Player::_Inst = 0;

Player::Player()
{
  this->_Window = getWindow();
  this->_Map = Map::Instance();
  this->_Control.push_back("Keyboard 1");
  this->_Control.push_back("Keyboard 2");
  this->_Control.push_back("Gamepad  1");
  this->_Control.push_back("Gamepad  2");
  this->_T = new sf::Texture();
  this->InitCharacter();
  this->LoadSprite2(RESOURCEPATH"eye.jpg", &this->_Sprite);
  this->InitIndex();
  this->LoadAlphaNum();
  this->_Name1 = "J1";
  this->_Name2 = "J2";
  this->_Name3 = "J3";
  this->_Name4 = "J4";
  this->_Error = "";
}

Player	*Player::Instance()
{
  if (Player::_Inst == 0)
    Player::_Inst = new Player();
  return (_Inst);
}

Player::~Player()
{
  this->_Control.clear();
  this->_Character.clear();
  this->_Alpha.clear();
}

int		Player::CheckError()
{
  unsigned int i = 0;
  unsigned int j = 0;

  if (G_GameSettings->nb_players == 0)
    {
      this->_Error = "No player selected.";
      return (1);
    }
  while (i < G_GameSettings->nb_players)
    {
      if (G_GameSettings->players[i]->name == "")
	{
	  this->_Error = "A player has no name.";
	  return (1);
	}
      j = 0;
      while (j < G_GameSettings->nb_players)
	{
	  if (i != j && G_GameSettings->players[i]->name
	      == G_GameSettings->players[j]->name)
	    {
	      this->_Error = "Two players have the same name.";
	      return (1);
	    }
	  if (i != j && G_GameSettings->players[i]->input->type2
	      == G_GameSettings->players[j]->input->type2)
	    {
	      this->_Error = "Two players have the same controler.";
	      return (1);
	    }
	  if (i != j && G_GameSettings->players[i]->character
	      == G_GameSettings->players[j]->character)
	    {
	      this->_Error = "Two players have the same character.";
	      return (1);
	    }
	  j++;
	}
      i++;
    }
  return (0);
}

int		Player::LoadCharacter()
{
  G_GameSettings->players.clear();
  if (this->_Index[0] != 0)
    G_GameSettings->players.push_back(new Settings::Player(this->_Name1, static_cast<Settings::Character>(this->_Index[0]), static_cast<Settings::InputType>(this->_Index[1])));
  if (this->_Index[2] != 0)
    G_GameSettings->players.push_back(new Settings::Player(this->_Name2, static_cast<Settings::Character>(this->_Index[2]), static_cast<Settings::InputType>(this->_Index[3])));
  if (this->_Index[4] != 0)
    G_GameSettings->players.push_back(new Settings::Player(this->_Name3, static_cast<Settings::Character>(this->_Index[4]), static_cast<Settings::InputType>(this->_Index[5])));
  if (this->_Index[6] != 0)
    G_GameSettings->players.push_back(new Settings::Player(this->_Name4, static_cast<Settings::Character>(this->_Index[6]), static_cast<Settings::InputType>(this->_Index[7])));
  G_GameSettings->nb_players = G_GameSettings->players.size();
  return (this->CheckError());
}

void	Player::InitCharacter()
{
  this->_Character.clear();
  sf::Sprite *none = new sf::Sprite();
  this->LoadSprite(RESOURCEPATH"none.png", &none);
  this->_Character.push_back(none);


  sf::Sprite *charac3 = new sf::Sprite();
  this->LoadSprite(RESOURCEPATH"black.png", &charac3);
  this->_Character.push_back(charac3);

  sf::Sprite *charac4 = new sf::Sprite();
  this->LoadSprite(RESOURCEPATH"white.png", &charac4);
  this->_Character.push_back(charac4);

  sf::Sprite *charac1 = new sf::Sprite();
  this->LoadSprite(RESOURCEPATH"red.png", &charac1);
  this->_Character.push_back(charac1);

  sf::Sprite *charac2 = new sf::Sprite();
  this->LoadSprite(RESOURCEPATH"blue.png", &charac2);
  this->_Character.push_back(charac2);

}

void	Player::InitIndex()
{
  this->_Index[0] = 1;
  this->_Index[2] = 0;
  this->_Index[4] = 0;
  this->_Index[6] = 0;
  this->_Index[1] = 0;
  this->_Index[3] = 1;
  this->_Index[5] = 2;
  this->_Index[7] = 3;
}

void	Player::DisplayCharacter()
{ //1
  this->SetSprite(this->_Character[this->_Index[0]], 100, 300);
  this->SetText("<", "arial", 70, sf::Color::Black, 30, 400);
  this->SetText(">", "arial", 70, sf::Color::Black, 330, 400);
  //2
  this->SetSprite(this->_Character[this->_Index[2]], 600, 300);
  this->SetText("<", "arial", 70, sf::Color::Black, 530, 400);
  this->SetText(">", "arial", 70, sf::Color::Black, 830, 400);
  //3
  this->SetSprite(this->_Character[this->_Index[4]], 1100, 300);
  this->SetText("<", "arial", 70, sf::Color::Black, 1030, 400);
  this->SetText(">", "arial", 70, sf::Color::Black, 1330, 400);
  //4
  this->SetSprite(this->_Character[this->_Index[6]], 1620, 300);
  this->SetText("<", "arial", 70, sf::Color::Black, 1550, 400);
  this->SetText(">", "arial", 70, sf::Color::Black, 1850, 400);
}

void	Player::DisplayController()
{ //1
  this->SetText(this->_Control[this->_Index[1]], "plok", 25, sf::Color::Black, 80, 650);
  this->SetText("<", "arial", 50, sf::Color::Black, 25, 635);
  this->SetText(">", "arial", 50, sf::Color::Black, 335, 635);
  //2
  this->SetText(this->_Control[this->_Index[3]], "plok", 25, sf::Color::Black, 580, 650);
  this->SetText("<", "arial", 50, sf::Color::Black, 525, 635);
  this->SetText(">", "arial", 50, sf::Color::Black, 835, 635);
  //3
  this->SetText(this->_Control[this->_Index[5]], "plok", 25, sf::Color::Black, 1080, 650);
  this->SetText("<", "arial", 50, sf::Color::Black, 1025, 635);
  this->SetText(">", "arial", 50, sf::Color::Black, 1335, 635);
  //4
  this->SetText(this->_Control[this->_Index[7]], "plok", 25, sf::Color::Black, 1600, 650);
  this->SetText("<", "arial", 50, sf::Color::Black, 1545, 635);
  this->SetText(">", "arial", 50, sf::Color::Black, 1855, 635);
}

void	Player::DisplayName(int flag)
{ //1
  if (flag == 1)
    this->DrawSquare(15, 750, 370, 850, sf::Color::Red);
  this->DrawSquare(25, 760, 360, 840, sf::Color::Black);
  this->SetText(this->_Name1, "plok", 50, sf::Color::White, 100, 770);
  //2
  if (flag == 2)
    this->DrawSquare(515, 750, 870, 850, sf::Color::Red);
  this->DrawSquare(525, 760, 860, 840, sf::Color::Black);
  this->SetText(this->_Name2, "plok", 50, sf::Color::White, 600, 770);
  //3
  if (flag == 3)
    this->DrawSquare(1015, 750, 1370, 850, sf::Color::Red);
  this->DrawSquare(1025, 760, 1360, 840, sf::Color::Black);
  this->SetText(this->_Name3, "plok", 50, sf::Color::White, 1100, 770);
  //4
  if (flag == 4)
    this->DrawSquare(1535, 750, 1890, 850, sf::Color::Red);
  this->DrawSquare(1545, 760, 1880, 840, sf::Color::Black);
  this->SetText(this->_Name4, "plok", 50, sf::Color::White, 1620, 770);
}

void	Player::Display(int flag)
{
  this->_Window->clear();
  this->SetSprite(this->_Sprite, 0, 0);
  this->DisplayName(flag);
  this->DisplayController();
  this->DisplayCharacter();
  this->SetText("PLAYER", "plok", 100, sf::Color::Black, 650, 50);
  this->SetText("BACK", "plok", 50, sf::Color::White, 50, 950);
  if (flag == 5)
    this->SetText("NEXT", "plok", 50, sf::Color::Red, 1550, 950);
  else
    this->SetText("NEXT", "plok", 50, sf::Color::White, 1550, 950);

  this->SetText("Player 1", "plok", 40, sf::Color::Black, 60, 230);
  this->SetText("Player 2", "plok", 40, sf::Color::Black, 560, 230);
  this->SetText("Player 3", "plok", 40, sf::Color::Black, 1060, 230);
  this->SetText("Player 4", "plok", 40, sf::Color::Black, 1580, 230);
  if (this->_Error != "")
    this->SetText(this->_Error, "plok", 30, sf::Color::Red, 450, 900);
  this->_Window->display();
}

void	Player::CatchCharacter(const sf::Event &event)
{
  if (CheckEvent(event, 20, 80, 430, 490) && this->_Index[0] != 0)
    this->_Index[0]--;
  else if (CheckEvent(event, 320, 380, 430, 490) && this->_Index[0] != 4)
    this->_Index[0]++;
  else if (CheckEvent(event, 520, 580, 430, 490) && this->_Index[2] != 0)
    this->_Index[2]--;
  else if (CheckEvent(event, 820, 880, 430, 490) && this->_Index[2] != 4)
    this->_Index[2]++;
  else if (CheckEvent(event, 1020, 1085, 430, 490) && this->_Index[4] != 0)
    this->_Index[4]--;
  else if (CheckEvent(event, 1320, 1380, 430, 490) && this->_Index[4] != 4)
    this->_Index[4]++;
  else if (CheckEvent(event, 1540, 1605, 430, 490) && this->_Index[6] != 0)
    this->_Index[6]--;
  else if (CheckEvent(event, 1840, 1906, 430, 490) && this->_Index[6] != 4)
    this->_Index[6]++;
}

void	Player::NameInput(std::string *NewName, int num)
{
 sf::Event	event;

 (*NewName) = "";
 this->Display(num);
 while (42)
   while (this->_Window->waitEvent(event))
     {
       if (event.type == sf::Event::KeyPressed && event.key.code >= 0 && event.key.code <= 26)
	 {
	   (*NewName) += this->_Alpha[event.key.code];
	   this->Display(num);
	 }
       else if (event.key.code == 58 || (*NewName).size() == 3)
	 return;
     }
}

void	Player::CatchController(const sf::Event &event)
{
  if (CheckEvent(event, 25, 75, 665, 710) && this->_Index[1] != 0)
    this->_Index[1]--;
  else if (CheckEvent(event, 315, 370, 665, 710) && this->_Index[1] != 3)
    this->_Index[1]++;
  else if (CheckEvent(event, 525, 580, 665, 710) && this->_Index[3] != 0)
    this->_Index[3]--;
  else if (CheckEvent(event, 820, 875, 665, 710) && this->_Index[3] != 3)
    this->_Index[3]++;
  else if (CheckEvent(event, 1020, 1085, 665, 710) && this->_Index[5] != 0)
    this->_Index[5]--;
  else if (CheckEvent(event, 1320, 1375, 665, 710) && this->_Index[5] != 3)
    this->_Index[5]++;
  else if (CheckEvent(event, 1540, 1600, 665, 710) && this->_Index[7] != 0)
    this->_Index[7]--;
  else if (CheckEvent(event, 1840, 1900, 665, 710) && this->_Index[7] != 3)
    this->_Index[7]++;
}

void	Player::Run()
{
  sf::Event	event;

  this->PlaySound("yay");
  this->InitCharacter();
  this->LoadSprite2(RESOURCEPATH"eye.jpg", &this->_Sprite);
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
		{
		  this->_Error = "";
		  if (this->LoadCharacter() == 0)
		    this->_Map->Run();
		  else
		    {
		      this->PlaySound("error");
		      this->Display(5);
		    }
		}
	      this->CatchName(event);
	      this->CatchCharacter(event);
	      this->CatchController(event);
       	    }
	}
      this->Display();
    }
}

void	Player::CatchName(const sf::Event &event)
{
  if (CheckEvent(event, 25, 360, 760, 840))
    this->NameInput(&this->_Name1, 1);
  else if (CheckEvent(event,525, 860, 760, 840))
    this->NameInput(&this->_Name2, 2);
  else if (CheckEvent(event, 1025, 1360, 760, 840))
    this->NameInput(&this->_Name3, 3);
  else if (CheckEvent(event, 1545, 1880, 760, 840))
    this->NameInput(&this->_Name4, 4);
}
