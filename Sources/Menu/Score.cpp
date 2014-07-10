//
// Score.cpp for  in /home/maigna_j/rendu/cpp_bomberman/menu
//
// Made by jeremy maignan
// Login   <maigna_j@epitech.net>
//
// Started on  Thu May 22 12:59:12 2014 jeremy maignan
// Last update Sun Jun 15 21:50:54 2014 Imad Roughi
//

#include "Graphics.hpp"
#include <iostream>
#include <unistd.h>

#include "Menu.hh"
#include "Score.hh"

#define RESOURCESCORE "./Score/"

Score	*Score::_Inst= 0;

Score::Score()
{
  i = 0;
  this->_Window = getWindow();
  this->_T = new sf::Texture;
  this->LoadSprite2(RESOURCEPATH"jail.jpg", &this->_Sprite);
  this->_file = "score.txt";
  this->_iScoreTable.open((RESOURCESCORE+this->_file).c_str()); // open your file
  this->_type = 0;
  if (this->_iScoreTable.peek() == std::ifstream::traits_type::eof()){
    this->ResetFile(10);
  }
  this->_iScoreTable.close();
}

Score::~Score()
{
  delete this->_Sprite;
  this->_Sprite = 0;
  delete this->_T;
  this->_T = 0;
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

void	Score::ResetFile(int value){
  int i  = -1;
  this->_oScoreTable.open((RESOURCESCORE+this->_file).c_str(), std::ios::trunc);
  while (++i < value)
    this->_oScoreTable<<"???.0;";
  this->_oScoreTable.close();
}

void Score::ResetVectors()
{
  int i = 0;
  std::vector<std::string>::iterator	it = _names.begin();
  while (it != _names.end()){
    this->_names.pop_back();
    this->_scores.pop_back();
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
  this->_iScoreTable.open((RESOURCESCORE+this->_file).c_str());
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

//dump file to vector charger a l'init
void	Score::Display()
{
  int rank  = 1;
  int y = 210;
  int test = 0;
  if (this->_type == 0){
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
}

//save vector to file
void	Score::SetScores(){
  this->_oScoreTable.open ((RESOURCESCORE+this->_file).c_str());
  std::vector<int>::iterator score = _scores.begin();
  for (std::vector<std::string>::iterator it = _names.begin() ; it != _names.end(); ++it){
    std::stringstream ss;
    ss << *score;
    this->_oScoreTable << *it << "." << ss.str() << ";";
    ++score;
  }
  this->_oScoreTable.close();
}

int			Score::isRankedIn(int score){
  int rank = 0;
  for (std::vector<int>::iterator it = _scores.begin() ; it != _scores.end(); ++it){
    if (score > *it)
      return(rank);
    rank++;
  }
  return -1;
}

//modif vectors
void	Score::SaveScore(const std::string &name, int score){
  int rank ;
  if ((rank = isRankedIn(score)) > -1){
    _scores.insert(_scores.begin()+rank, score);
    _names.insert(_names.begin()+rank, name);
    _scores.pop_back();
    _names.pop_back();
  }
  this->SetScores();
}
void	Score::UpdateFile(){
  std::vector<std::string>	namesI;
  std::vector<int>		scoresI;
  std::vector<int>::iterator		it;
  this->_file = "scoreInGame.txt";
  this->ResetVectors();
  this->InitVectors();
  namesI = this->_names;
  scoresI = this->_scores;
  this->_file = "score.txt";
  this->ResetVectors();
  this->InitVectors();
  int i = 0;
  for (std::vector<int>::iterator it = scoresI.begin(); it != scoresI.end(); it++){
    if (isRankedIn(*it) > -1)
      this->SaveScore(namesI[i], scoresI[i]);
    i++;
  }
}

void	Score::setFile(const std::string &file){this->_file = file;}
std::vector<std::string>	Score::getNames() const{return this->_names;}
std::vector<int>		Score::getScores() const{return this->_scores;}


void	Score::Run(int type) //0 score from menu 1 in game
{
  sf::Event	event;

  this->PlaySound("yay");
  this->LoadSprite2(RESOURCEPATH"jail.jpg", &this->_Sprite);
  if (type == 0){
    this->UpdateFile();
    this->_file = "scoreInGame.txt";
    this->_oScoreTable.open((RESOURCESCORE+this->_file).c_str(), std::ios::trunc);
    this->_oScoreTable.close();
    this->_file = "score.txt";
  }
  if (type == 1)
    this->_file = "scoreInGame.txt";
  this->_type = type;
  this->ResetVectors();
  this->InitVectors();
  while (this->_Window->isOpen())
    {
      if (type == 0)
	this->_file = "score.txt";
      if (type == 1)
	this->_file = "scoreInGame.txt";
      while (this->_Window->pollEvent(event))
	{
	  this->Quit(event);
	  if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	    {
	      if (CheckEvent(event, 40, 255, 980, 1045))
		return;
	     if (CheckEvent(event, 1520, 1770, 970, 1045) && this->_type == 0)
	        this->ResetFile(10);
	        this->ResetVectors();
	        this->InitVectors();
	    }
	}
      this->_Window->clear();
      this->Display();
      this->_Window->display();
    }
}
