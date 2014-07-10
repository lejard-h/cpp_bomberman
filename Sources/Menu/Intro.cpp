//
// Intro.cpp for  in /home/maigna_j/rendu/cpp_bomberman/Menu
//
// Made by jeremy maignan
// Login   <maigna_j@epitech.net>
//
// Started on  Wed May 28 16:50:11 2014 jeremy maignan
// Last update Sat Jun 14 17:59:44 2014 jeremy maignan

#include "Intro.hh"
#include "Playlist.hh"

Intro::Intro()
{
  this->LoadSprite(RESOURCEPATH"intro.png", &this->_Sprite);
  this->_Window = getWindow();
  this->_Window->clear();
  this->SetSprite(this->_Sprite, 0, 0);
  this->SetText("LOADING", "plok", 100, sf::Color::Yellow, 600, 50);
  this->_Window->display();
  // LOAD every resource here //
  Playlist *SoundContent = Playlist::getPlaylist();
  SoundContent->loadSound("./Asset/Sounds/menu.mp3", "menu");
  SoundContent->loadSound("./Asset/Sounds/error.mp3", "error");
  SoundContent->loadSound("./Asset/Sounds/YAY.mp3", "yay");
  SoundContent->loadSound("./Asset/Sounds/what.mp3", "what");
  this->_Welcome = Welcome::Instance();
  this->_Player = Player::Instance();
  this->_Map = Map::Instance();
  this->_Opponent = Opponent::Instance();
  this->_Score = Score::Instance();
  this->_Credit = Credit::Instance();
  this->_Load = Load::Instance();
  this->_Save = Save::Instance();
  this->_Option = Option::Instance();
  this->_Controls = Controls::Instance();
  this->_Camera = Camera::Instance();
  this->_Podium = Podium::Instance();
  //  sleep(1);
}

Intro::~Intro()
{
  delete this->_Welcome;
  delete this->_Player;
  delete this->_Map;
  delete this->_Opponent;
  delete this->_Score;
  delete this->_Credit;
  delete this->_Load;
  delete this->_Save;
  delete this->_Option;
  delete this->_Controls;
  delete this->_Camera;
  delete this->_Podium;
  Playlist::delPlaylist();
}
