//
// Podium.cpp for  in /home/maigna_j/rendu/cpp_bomberman/Sources/Menu
//
// Made by jeremy maignan
// Login   <maigna_j@epitech.net>
//
// Started on  Sat Jun 14 17:55:07 2014 jeremy maignan
// Last update Sun Jun 15 20:40:08 2014 Imad Roughi
//

#include "Podium.hh"

Podium	*Podium::_Inst = 0;

Podium::Podium()
{
  this->_Window = getWindow();
  this->_T = new sf::Texture();
  this->_Score = Score::Instance();
  this->LoadSprite2(RESOURCEPATH"stadium.jpg", &this->_Sprite);
  this->InitCharacter();
  this->colorPod[0] = sf::Color(239,216,7);
  this->colorPod[1] = sf::Color(206,206,206);
  this->colorPod[2] = sf::Color(174,100,45);
}

Podium::~Podium()
{
  delete this->_Sprite;
  this->_Sprite = 0;
  delete this->_T;
  this->_T = 0;
 }

Podium	*Podium::Instance()
{
  if (Podium::_Inst == 0)
    Podium::_Inst = new Podium();
  return (_Inst);
}

void	Podium::InitCharacter()
{
  this->_Character.clear();
  sf::Sprite *charac3 = new sf::Sprite();
  this->LoadSprite(RESOURCEPATH"black.png", &charac3);
  this->_Character.push_back(charac3);

  sf::Sprite *charac4 = new sf::Sprite();
  this->LoadSprite(RESOURCEPATH"white.png", &charac4);
  this->_Character.push_back(charac4);

  sf::Sprite *charac1 = new sf::Sprite();
  this->LoadSprite(RESOURCEPATH"red.png", &charac1);
  this->_Character.push_back(charac1);

  sf::Sprite *charac2 = new sf::Sprite();
  this->LoadSprite(RESOURCEPATH"blue.png", &charac2);
  this->_Character.push_back(charac2);
}

void	Podium::dumpScore(){
  std::vector<std::string>			names;
  std::vector<int>				scores;
  std::vector<std::string>::iterator		itName;
  std::vector<int>::iterator			itScore;
  std::map<int, std::string>			my_map;
  std::map<int, std::string>::reverse_iterator		it_map;
  int x = 150;
  int y = 400;
  int i = 0;


  names = this->_Score->getNames();
  scores = this->_Score->getScores();
  itScore = scores.begin();

  for (itName = names.begin(); itName != names.end(); itName++){
    my_map[*itScore] += *itName;
    itScore++;
  }
  unsigned int c;
  this->InitCharacter();
  int pos = 0;
  for (it_map = my_map.rbegin();it_map != my_map.rend();it_map++){
    c = 0;
    pos++;
    this->SetText(it_map->second, "plok", 50, colorPod[i], x, y);
    std::stringstream ss;
    ss << it_map->first;
    this->SetText(ss.str(), "plok", 50, colorPod[i++], x + 600, y);
    y += 70;
    while(G_GameSettings->players.size() > c && G_GameSettings->players[c]->name != it_map->second)
      c++;
    if (G_GameSettings->players.size() > c){
    if(pos == 1)
      this->SetSprite(this->_Character[G_GameSettings->players[c]->character - 1], 1325, 400);
    if(pos == 2)
      this->SetSprite(this->_Character[G_GameSettings->players[c]->character - 1], 1025, 450);
    if(pos == 3)
      this->SetSprite(this->_Character[G_GameSettings->players[c]->character - 1], 1550, 475);
    }
  }
}


void	Podium::Display()
{

  this->SetSprite(this->_Sprite, 0, 0);
  this->SetSprite(this->_Podium, 1000, 650);
  this->SetText("PODIUM", "plok", 100, sf::Color::White, 600, 60);
  this->SetText("MENU", "plok", 50, sf::Color::Blue, 50, 950);
  this->SetText("QUIT", "plok", 50, sf::Color::Blue, 1550, 950);

  this->_Score->setFile("scoreInGame.txt");
  this->_Score->ResetVectors();
  this->_Score->InitVectors();
  this->dumpScore();
}

void		Podium::Run()
{
  sf::Event	event;

  this->PlaySound("yay");
  this->LoadSprite2(RESOURCEPATH"stadium.jpg", &this->_Sprite);
  this->LoadSprite(RESOURCEPATH"podium.png", &this->_Podium);
  while (this->_Window->isOpen())
    {
      while (this->_Window->pollEvent(event))
	{
	  this->Quit(event);
	  if (event.type == sf::Event::MouseButtonPressed &&
	      event.mouseButton.button == sf::Mouse::Left)
	    {
	      if (CheckEvent(event, 15, 285, 970, 1045))
		return;
	      else if (CheckEvent(event, 1520, 1770, 970, 1045))
		this->_Window->close();
	    }
	}
      this->_Window->clear();
      this->Display();
      this->_Window->display();
    }
}
