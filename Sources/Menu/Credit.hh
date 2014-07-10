//
// Credit.hh for  in /home/maigna_j/rendu/cpp_bomberman/menu
//
// Made by jeremy maignan
// Login   <maigna_j@epitech.net>
//
// Started on  Thu May 22 18:18:17 2014 jeremy maignan
// Last update Thu Jun 12 00:06:52 2014 jeremy maignan
//

#ifndef CREDIT_HH_
#define CREDIT_HH_

#include "Graphics.hpp"
#include "Menu.hh"

class Credit : public Menu
{
private:
  static Credit		*_Inst;
public:
  Credit();
  ~Credit();
  void			Run();
  void			Display();
  static Credit		*Instance();
};

#endif
