//
// Intro.hh for  in /home/maigna_j/rendu/cpp_bomberman/Menu
//
// Made by jeremy maignan
// Login   <maigna_j@epitech.net>
//
// Started on  Wed May 28 16:53:39 2014 jeremy maignan
// Last update Sat Jun 14 18:00:10 2014 jeremy maignan
//

#ifndef INTRO_HH_
#define INTRO_HH_

#include <iostream>
#include <unistd.h>

#include "Graphics.hpp"
#include "Menu.hh"
#include "Score.hh"
#include "Player.hh"
#include "Welcome.hh"
#include "Credit.hh"
#include "Map.hh"
#include "Opponent.hh"
#include "Load.hh"
#include "Save.hh"
#include "Option.hh"
#include "Controls.hh"
#include "Camera.hh"
#include "Podium.hh"

class Intro : public Menu
{
private:
  Score				*_Score;
  Credit			*_Credit;
  Load				*_Load;
  Save				*_Save;
  Option	         	*_Option;
  Controls			*_Controls;
  Camera			*_Camera;
  Mode	         		*_Mode;
  Player			*_Player;
  Map				*_Map;
  Opponent			*_Opponent;
  Welcome			*_Welcome;
  Podium			*_Podium;
public:
  Intro();
  ~Intro();
};

#endif
