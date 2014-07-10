//
// Welcome.hh for  in /home/maigna_j/rendu/cpp_bomberman/menu
//
// Made by jeremy maignan
// Login   <maigna_j@epitech.net>
//
// Started on  Thu May 22 13:03:40 2014 jeremy maignan
// Last update Sun Jun 15 02:07:55 2014 Imad Roughi
//

#ifndef WELCOME_HH_
#define WELCOME_HH_

#include "Menu.hh"

class Score;
class Mode;
class Credit;
class Load;
class Option;

class Welcome : public Menu
{
private:
  Score				*_Score;
  Load				*_Load;
  Credit			*_Credit;
  Mode	         		*_Mode;
  Option	         	*_Option;
  static Welcome		*_Inst;
public:
  Welcome();
  ~Welcome();
  static Welcome		*Instance();
  void				Run();
  void				Display();
};

#endif
