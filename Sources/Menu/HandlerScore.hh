//
// Score.hh for  in /home/maigna_j/rendu/cpp_bomberman/menu
//
// Made by jeremy maignan
// Login   <maigna_j@epitech.net>
//
// Started on  Thu May 22 12:55:28 2014 jeremy maignan
// Last update Tue Jun 10 22:45:37 2014 jeremy maignan
//

#ifndef SCORE_HH_
#define SCORE_HH_

#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>
#include <string>

#include "Graphics.hpp"
#include "Menu.hh"


class Score : public Menu
{
 private:
  static Score			*_Inst;
  std::ofstream			_oScoreTable;
  std::ifstream			_iScoreTable;
  std::vector<std::string>	_names;
  std::vector<int>		_scores;

public:
  Score();
  ~Score();
  static Score		*Instance();
  void			Run();
  void			Display();
  void			ResetTable();
  void			InitVectors();
  void			SetScores();
  void			SaveScore(std::string name, int score);
  int			isRankedIn(int score);
};
#endif
