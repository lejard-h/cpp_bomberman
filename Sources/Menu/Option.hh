//
// Option__.hh for  in /home/maigna_j/rendu/cpp_bomberman/Menu
//
// Made by jeremy maignan
// Login   <maigna_j@epitech.net>
//
// Started on  Wed Jun  4 17:00:58 2014 jeremy maignan
// Last update Fri Jun 13 18:06:43 2014 jeremy maignan
//

#ifndef OPTION_HH_
#define OPTION_HH_

#include <list>
#include <sstream>
#include <iostream>
#include <unistd.h>

#include "Graphics.hpp"
#include "Menu.hh"
#include "Controls.hh"
#include "Camera.hh"

class Option : public Menu
{
 private:
  static Option			*_Inst;
  Controls			*_Controls;
  Camera			*_Camera;
 public:
  Option();
  ~Option();
  void			Run();
  void			Display();
  static Option		*Instance();
};
#endif
