//
// Controls.cpp for controls in /home/roughi_i/epitech/c++/bomberman/cpp_bomberman/Menu
//
// Made by Imad Roughi
// Login   <roughi_i@epitech.net>
//
// Started on  Sat Jun  7 18:38:41 2014 Imad Roughi
// Last update Sun Jun 15 21:46:14 2014 Imad Roughi
//

#include "Controls.hh"

Controls	*Controls::_Inst = 0;
std::map<std::string, int >			*G_AlphaSFtoSD = 0;

Controls::Controls()
{
  G_AlphaSFtoSD = new  std::map<std::string, int >();
  this->ctrlK1Bind = new  std::map<int, std::string >();
  this->ctrlK2Bind = new  std::map<int, std::string >();
  this->_Window = getWindow();
  this->LoadAlphaNum();
  this->LoadAlphaSFtoSD();
  this->num_play = 1;
  this->InitKBoards();
  this->Binding();
}

Controls::~Controls()
{
  delete this->ctrlK1Bind;
  delete this->ctrlK2Bind;
  delete G_AlphaSFtoSD;
}

Controls	*Controls::Instance()
{
  if (Controls::_Inst == 0)
    Controls::_Inst = new Controls();
  return (_Inst);
}

void	Controls::InitKBoards()
{
  this->ctrlK2["up"] = "Z";
  this->ctrlK2["down"] = "S";
  this->ctrlK2["left"] = "Q";
  this->ctrlK2["right"] = "D";
  this->ctrlK2["bomb"] = "E";

  this->ctrlK1["up"] = "Up";
  this->ctrlK1["down"] = "Down";
  this->ctrlK1["left"] = "Left";
  this->ctrlK1["right"] = "Right";
  this->ctrlK1["bomb"] = "Space";
  this->ctrlCu = this->ctrlK1;
}

const std::map<int, std::string>			&Controls::getCtrlK1() const
{
  return *ctrlK1Bind;
}
const std::map<int, std::string>			&Controls::getCtrlK2() const
{
return *ctrlK2Bind;
}

void	Controls::LoadAlphaSFtoSD() const
{
  (*G_AlphaSFtoSD)["1"] = SDLK_1;
  (*G_AlphaSFtoSD)["2"] = SDLK_2;
  (*G_AlphaSFtoSD)["3"] = SDLK_3;
  (*G_AlphaSFtoSD)["4"] = SDLK_4;
  (*G_AlphaSFtoSD)["5"] = SDLK_5;
  (*G_AlphaSFtoSD)["6"] = SDLK_6;
  (*G_AlphaSFtoSD)["7"] = SDLK_7;
  (*G_AlphaSFtoSD)["8"] = SDLK_8;
  (*G_AlphaSFtoSD)["9"] = SDLK_9;
  (*G_AlphaSFtoSD)["A"] = SDLK_a;
  (*G_AlphaSFtoSD)["B"] = SDLK_b;
  (*G_AlphaSFtoSD)["C"] = SDLK_c;
  (*G_AlphaSFtoSD)["D"] = SDLK_d;
  (*G_AlphaSFtoSD)["E"] = SDLK_e;
  (*G_AlphaSFtoSD)["F"] = SDLK_f;
  (*G_AlphaSFtoSD)["G"] = SDLK_g;
  (*G_AlphaSFtoSD)["H"] = SDLK_h;
  (*G_AlphaSFtoSD)["I"] = SDLK_i;
  (*G_AlphaSFtoSD)["J"] = SDLK_j;
  (*G_AlphaSFtoSD)["K"] = SDLK_k;
  (*G_AlphaSFtoSD)["L"] = SDLK_l;
  (*G_AlphaSFtoSD)["M"] = SDLK_m;
  (*G_AlphaSFtoSD)["N"] = SDLK_n;
  (*G_AlphaSFtoSD)["O"] = SDLK_o;
  (*G_AlphaSFtoSD)["P"] = SDLK_p;
  (*G_AlphaSFtoSD)["Q"] = SDLK_q;
  (*G_AlphaSFtoSD)["R"] = SDLK_r;
  (*G_AlphaSFtoSD)["S"] = SDLK_s;
  (*G_AlphaSFtoSD)["T"] = SDLK_t;
  (*G_AlphaSFtoSD)["U"] = SDLK_u;
  (*G_AlphaSFtoSD)["V"] = SDLK_v;
  (*G_AlphaSFtoSD)["W"] = SDLK_w;
  (*G_AlphaSFtoSD)["X"] = SDLK_x;
  (*G_AlphaSFtoSD)["Y"] = SDLK_y;
  (*G_AlphaSFtoSD)["Z"] = SDLK_z;
  (*G_AlphaSFtoSD)["Up"] = SDLK_UP;
  (*G_AlphaSFtoSD)["Down"] = SDLK_DOWN;
  (*G_AlphaSFtoSD)["Left"] = SDLK_LEFT;
  (*G_AlphaSFtoSD)["Right"] = SDLK_RIGHT;
  (*G_AlphaSFtoSD)["Space"] = SDLK_SPACE;
}

int	Controls::keySFtoSD(const std::string &key) const
{
  for (std::map<std::string, int>::const_iterator it = (*G_AlphaSFtoSD).begin();
       it != (*G_AlphaSFtoSD).end(); ++it)
    if (key == it->first)
      return(it->second);
  return -1;
}

void	Controls::Binding()
{
  int value;

  this->ctrlK1Bind->clear();
  this->ctrlK2Bind->clear();
  for (std::map<std::string, std::string>::iterator it = this->ctrlK1.begin();
       it != this->ctrlK1.end(); ++it)
    {
      if((value = keySFtoSD(it->second)) != -1)
	(*this->ctrlK1Bind)[value] = it->first;
    }
  for (std::map<std::string, std::string>::iterator it = this->ctrlK2.begin();
       it != this->ctrlK2.end(); ++it)
    {
      if((value = keySFtoSD(it->second)) != -1)
	(*this->ctrlK2Bind)[value] = it->first;
    }
}

void	Controls::Display()
{
  std::stringstream ss;
  std::string str;
  ss << this->num_play;
  str = ss.str();

  this->SetSprite(this->_Sprite, 0, 0);
  this->SetText("CONTROLS", "plok", 100, sf::Color::White, 500, 50);
  this->SetText("KEYBOARD", "plok", 50, sf::Color(255, 140, 0, 255), 600, 200);
  this->SetText("-", "arial", 70, sf::Color(255, 140, 0, 255), 1050, 180);
  this->SetText(str, "plok", 60, sf::Color(255, 140, 0, 255), 1100, 200);
  this->SetText("+", "arial", 70, sf::Color(255, 140, 0, 255), 1170, 190);

  this->DrawSquare(850, 415, 1050,465, sf::Color::White);
  this->DrawSquare(850, 535, 1050,585, sf::Color::White);
  this->DrawSquare(550, 535, 750, 585, sf::Color::White);
  this->DrawSquare(1225, 535, 1425,585, sf::Color::White);
  this->DrawSquare(850, 655, 1050,710, sf::Color::White);

  this->SetText("UP", "plok", 50, sf::Color(255, 140, 0, 255), 900, 350);
  this->SetText("DOWN", "plok", 50, sf::Color(255, 140, 0, 255), 850, 470);
  this->SetText("LEFT", "plok", 50, sf::Color(255, 140, 0, 255), 550, 470);
  this->SetText("RIGHT", "plok", 50, sf::Color(255, 140, 0, 255), 1200, 470);
  this->SetText("BOMB", "plok", 50, sf::Color::Green, 850, 590);

  this->SetText(this->ctrlCu["up"], "plok", 25, sf::Color::Red, 890, 420);
  this->SetText(this->ctrlCu["left"], "plok", 25, sf::Color::Red, 585, 550);
  this->SetText(this->ctrlCu["down"], "plok", 25, sf::Color::Red, 885, 550);
  this->SetText(this->ctrlCu["right"], "plok", 25, sf::Color::Red, 1260, 550);
  this->SetText(this->ctrlCu["bomb"], "plok", 25, sf::Color::Red, 885, 670);

  this->SetText("BACK", "plok", 50, sf::Color(255, 140, 0, 255), 50, 950);
  this->SetText("DEFAULT", "plok", 50, sf::Color(255, 140, 0, 255), 1550, 950);
}

bool	Controls::isNum(const std::string &key) const{
  if (key == "0" || key == "1" ||
      key == "2" || key == "3" ||
      key == "4" || key == "5" ||
      key == "6" || key == "7" ||
      key == "8" || key == "9")
    return true;
  return false;
}

bool	Controls::KeyAvailable(const std::string &key, const std::string &index)
{
  if (isNum(key))
    return false;
  if (this->num_play == 1 && ctrlK1[index] == key)
    return(true);
  if (this->num_play == 2 && ctrlK2[index] == key)
    return(true);

  if (key == ctrlK1["up"] || key == ctrlK2["up"] ||
      key == ctrlK1["down"] || key == ctrlK2["down"] ||
      key == ctrlK1["left"] || key == ctrlK2["left"] ||
      key == ctrlK1["bomb"] || key == ctrlK2["bomb"] ||
      key == ctrlK1["right"] || key == ctrlK2["right"])
    return false;
  return true;
}

void	Controls::KeyInput(const std::string &index)
{
 sf::Event	event;
 std::string	key;

 while (this->_Window->waitEvent(event))
   {
     if (event.type == sf::Event::KeyPressed)
       {
	 key  = this->_Alpha[event.key.code];
	 if(KeyAvailable(key, index) && key != ""){
	   while (this->ctrlCu.find(index) != this->ctrlCu.end())
	     this->ctrlCu.erase(this->ctrlCu.find(index));
	   this->ctrlCu[index] = key;
	   if (this->num_play ==  1)
	     this->ctrlK1 = this->ctrlCu;
	   else
	     this->ctrlK2 = this->ctrlCu;
	   return;
	 }
       }
   }
}

void	Controls::CatchController(const sf::Event &event)
{
  std::string index = "";

  if (this->num_play ==  1)
    this->ctrlCu = this->ctrlK1;
  else
    this->ctrlCu = this->ctrlK2;
  if (CheckEvent(event, 850, 1055, 415, 470))
    index = "up";
  else if (CheckEvent(event, 550, 755, 535, 590))
    index = "left";
  else if (CheckEvent(event, 850, 1050, 540, 590))
    index = "down";
  else if (CheckEvent(event, 1225, 1425, 540, 590))
    index = "right";
  else if (CheckEvent(event, 850, 1050, 660, 710))
    index = "bomb";
  if (index.size() > 1){
    this->ctrlCu[index] = "Key";
    this->Display();
    this->_Window->display();
    KeyInput(index);
  }
}



void	Controls::Run()
{
  sf::Event	event;
  std::string	str;

  this->PlaySound("yay");
  this->LoadSprite(RESOURCEPATH"controlBg.png", &this->_Sprite);
  while (this->_Window->isOpen())
    {
      while (this->_Window->pollEvent(event))
	{
	  this->Quit(event);
	  if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
	    if (CheckEvent(event, 1050, 1075, 230, 240) && this->num_play > 1)
	      this->num_play-= 1;
	    if (CheckEvent(event,1175, 1210, 220, 255) && this->num_play < 2)
	      this->num_play+= 1;
	    if (CheckEvent(event,1550, 1900, 960, 1010))
	      InitKBoards();
	    if (CheckEvent(event, 15, 285, 970, 1045))
	      return;
	    this->CatchController(event);
	  }
	}
      this->Binding();
      this->_Window->clear();
      this->Display();
      this->_Window->display();
    }
}
