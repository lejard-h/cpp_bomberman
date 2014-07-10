//
// Score.cpp for  in /home/maigna_j/rendu/cpp_bomberman/menu
//
// Made by jeremy maignan
// Login   <maigna_j@epitech.net>
//
// Started on  Thu May 22 12:59:12 2014 jeremy maignan
// Last update Tue Jun 10 22:45:56 2014 jeremy maignan
//

#include "Graphics.hpp"
#include <iostream>
#include <unistd.h>

#include "Menu.hh"
#include "Score.hh"

Score	*Score::_Inst= 0;

Score::Score()
{
  this->_Window = getWindow();
  this->LoadSprite(RESOURCEPATH"jail.jpg", &this->_Sprite);
}

Score::~Score()
{
  delete this->_Sprite;
  this->_names.clear();
  this->_scores.clear();
}

Score	*Score::Instance()
{
  if (Score::_Inst == 0)
    {
      Score::_Inst = new Score();
      _Inst->InitVectors();
    }
  return (_Inst);
}

void Score::ResetTable()
{
  int i = 1;

  while (i <= 10)
    {
      _Inst->_names.pop_back();
      _Inst->_scores.pop_back();
      i++;
    }
  i = 1;
  while (i <= 10)
    {
      _Inst->_names.push_back("...");
      _Inst->_scores.push_back(0);
      i++;
    }
}

//load vecteur name et score pour comparatif
void	Score::InitVectors()
{
  std::string	line;
  std::string	delimiter = ";";
  std::string	del = ".";
  size_t	pos = 0;
  std::string	token;
  std::string	tok;
  size_t	ps = 0;
  int		score;

  //modele string "name.score; parsing 2 etapes ";" & "."
  this->_iScoreTable.open("./resource/scoreTable.txt");
  if (this->_iScoreTable.is_open())
  {
  getline(this->_iScoreTable, line);
  while ((pos = line.find(delimiter)) != std::string::npos) {
    token = line.substr(0, pos);
    while ((ps = token.find(del)) != std::string::npos) {
      tok = token.substr(0, ps);
      this->_names.push_back(tok); //insertion name in vec
      token.erase(0, ps + del.length());
      std::stringstream ss(token);
      ss >> score;
      this->_scores.push_back(score); //insertion score in vec
    }
    line.erase(0, pos + delimiter.length());

  }
  this->_iScoreTable.close();
  }
}

//dump file to vector charger a l'init
void	Score::Display()
{
  int rank  = 1;
  int y = 210;
  int test = 0;
  this->SetSprite(this->_Sprite, 0, 0);
  this->SetText("SCORES", "plok", 100, sf::Color::Yellow, 600, 50);

  std::vector<int>::iterator score = _scores.begin();
  for (std::vector<std::string>::iterator it = _names.begin() ; it != _names.end() && test < 10; ++it ){
    test++;
    std::stringstream ss;
    ss << rank << ". " << *it << "\t" << *score <<"\t\tpoints";
    this->SetText(ss.str(), "plok", 30, sf::Color::Yellow, 30, y);
    y += 70;
    rank++;
    score++;
  }
  this->SetText("BACK", "plok", 50, sf::Color::Yellow, 50, 950);
  this->SetText("RESET", "plok", 50, sf::Color::Yellow, 1550, 950);
}

//save vector to file
void	Score::SetScores(){
  this->_oScoreTable.open ("./resource/scoreTable.txt");
    if (this->_iScoreTable.is_open())
  {
  std::vector<int>::iterator score = _scores.begin();
  for (std::vector<std::string>::iterator it = _names.begin() ; it != _names.end(); ++it){
    std::stringstream ss;
    ss << *score;
    this->_oScoreTable << *it << "." << ss.str() << ";";
    ++score;
  }
}
  this->_oScoreTable.close();
}

int			Score::isRankedIn(int score){
  int rank = 0;
  for (std::vector<int>::iterator it = _scores.begin() ; it != _scores.end(); ++it){
    if (score > *it){
      return(rank);
    }
    rank++;
  }
  return -1;
}

//modif vectors
void	Score::SaveScore(std::string name, int score){
  int rank ;
  if ((rank = isRankedIn(score)) > -1){
    _scores.insert(_scores.begin()+rank, score);
    _names.insert(_names.begin()+rank, name);
    _scores.pop_back();
    _names.pop_back();
  }
  this->SetScores();
}

void	Score::Run()
{
  sf::Event	event;

  //  this->SaveScore("DUD", 900);
  while (this->_Window->isOpen())
    {
      while (this->_Window->pollEvent(event))
	{
	  this->Quit(event);
	  if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	    {
	      if (CheckEvent(event, 40, 255, 980, 1045))
		return;
	      else if (CheckEvent(event, 1520, 1770, 970, 1045))
		this->ResetTable();
	    }
	}
      this->_Window->clear();
      this->Display();
      this->_Window->display();
    }
}
