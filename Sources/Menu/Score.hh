//
// Score.hh for  in /home/maigna_j/rendu/cpp_bomberman/menu
//
// Made by jeremy maignan
// Login   <maigna_j@epitech.net>
//
// Started on  Thu May 22 12:55:28 2014 jeremy maignan
// Last update Sun Jun 15 21:50:59 2014 Imad Roughi
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
  std::string			_pathScore;
  static Score			*_Inst;
  std::ofstream			_oScoreTable;
  std::ifstream			_iScoreTable;
  std::vector<std::string>	_names;
  std::vector<int>		_scores;
  std::string			_file;
  int				_type;
  int i;

public:
  Score();
  ~Score();
  static Score		*Instance();
  void			InitScore();
  void			Run(int status);
  void			Display();
  void			ResetFile(int value);
  void			ResetVectors();
  void			InitVectors();
  void			SetScores();
  void			UpdateFile();
  void			SaveScore(const std::string & name, int score);
  int			isRankedIn(int score);
  void			dumpFile();
  void			setFile(const std::string &file);
  std::vector<std::string>	getNames() const;
  std::vector<int>		getScores() const;
};
#endif
