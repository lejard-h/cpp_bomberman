//
// score.hh for  in /home/maigna_j/rendu/cpp_bomberman/score
// 
// Made by jeremy maignan
// Login   <maigna_j@epitech.net>
// 
// Started on  Tue May 20 14:58:30 2014 jeremy maignan
// Last update Tue May 20 17:56:03 2014 jeremy maignan
//

#ifndef SCORE_HH_
#define SCORE_HH_

#include <string>
#include <iostream>
#include <list>
#include <fstream>

class Score
{
private:
  std::string	_name;
  std::string   _date;
  int		_score;
public:
  Score(const std::string &name, int score);
};

class Rank
{
private:
  std::ifstream	     _file;
  std::list<Score *> _rank;
public:
  Rank();
  void	AddScore(const std::string &name, int score);
  void	ParseFile();
};

#endif
