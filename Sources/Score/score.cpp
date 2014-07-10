//
// score.cpp for  in /home/maigna_j/rendu/cpp_bomberman/score
// 
// Made by jeremy maignan
// Login   <maigna_j@epitech.net>
// 
// Started on  Tue May 20 14:56:31 2014 jeremy maignan
// Last update Tue May 20 18:14:58 2014 jeremy maignan
//

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <time.h>

#include "score.hh"

const std::string CurrentDate()
{
  time_t     now = time(0);
  struct tm  tstruct;
  char       buf[80];

  tstruct = *localtime(&now);
  strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
  return buf;
}
/////////////SCORE/////////////////////
Score::Score(const std::string &name, int score)
{
  this->_name = name;
  this->_score = score;
  this->_date = CurrentDate();
  
  std::ofstream	     file;
  file.open("score.txt");

  std::stringstream ss;
  ss << this->_score;
  std::string line = this->_name + " " + ss.str() + " " + this->_date;
  std::cout << line ;  
//  long sizet = line.size();
  file.write(line.c_str(), 100);
}
/////////////////RANK/////////////////
Rank::Rank()
{
  this->_file.open("score.txt");
  if (this->_file == NULL)
    std::cerr << "can't open rank file" << std::endl;

  /*  std::string tmp2;
  std::getline(this->_file, tmp2, '\n');
  std::cout << tmp2;*/
}

void Rank::ParseFile()
{

}

void Rank::AddScore(const std::string &name, int score)
{
  this->_rank.push_back(new Score(name, score));
}


int main()
{
  Rank *classement = new Rank();
  classement->AddScore("michel", 10);
  classement->AddScore("steve", 11);
  classement->AddScore("alain", 12);
  classement->AddScore("christoph", 13);
  classement->AddScore("laurent", 14);
  classement->AddScore("jean", 10);
  classement->AddScore("luc", 10);
  classement->AddScore("bernard", 10);
}
