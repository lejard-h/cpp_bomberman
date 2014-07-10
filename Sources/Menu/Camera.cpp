//
// Camera.cpp for controls in /home/roughi_i/epitech/c++/bomberman/cpp_bomberman/Menu
//
// Made by Imad Roughi
// Login   <roughi_i@epitech.net>
//
// Started on  Sat Jun  7 18:38:41 2014 Imad Roughi
// Last update Sun Jun 15 21:48:07 2014 Imad Roughi
//

#include "Camera.hh"

Camera	*Camera::_Inst = 0;

Camera::Camera()
{
  ctrlCamBind = new std::map<int, std::string>();
  this->_Window = getWindow();
  this->LoadNum();
  InitKBoard();
  Binding();
}

Camera::~Camera(){
  delete this->ctrlCamBind;
}

Camera	*Camera::Instance()
{
  if (Camera::_Inst == 0)
    Camera::_Inst = new Camera();
  return (_Inst);
}

std::map<int, std::string>	*Camera::getCtrlCam() const{return this->ctrlCamBind;}

void	Camera::InitKBoard(){
  this->ctrlCam["UP"] = "8";
  this->ctrlCam["DOWN"] = "5";
  this->ctrlCam["LEFT"] = "4";
  this->ctrlCam["RIGHT"] = "6";
  this->ctrlCam["BACK"] = "7";
  this->ctrlCam["FRONT"] = "9";
}

void	Camera::Display()
{
  std::stringstream ss;

  this->SetSprite(this->_Sprite, 0, 0);
  this->SetText("CAMERA", "plok", 100, sf::Color::White, 500, 50);

  //up squareline
  this->DrawSquare(550, 415, 750,465, sf::Color::White);
  this->DrawSquare(850, 415, 1050,465, sf::Color::White);
  this->DrawSquare(1225, 415, 1425,465, sf::Color::White);

  //down square line
  this->DrawSquare(1225, 535, 1425,585, sf::Color::White);
  this->DrawSquare(850, 535, 1050,585, sf::Color::White);
  this->DrawSquare(550, 535, 750, 585, sf::Color::White);

  this->SetText("UP", "plok", 50, sf::Color(255, 140, 0, 255), 900, 350);
  this->SetText("DOWN", "plok", 50, sf::Color(255, 140, 0, 255), 850, 470);
  this->SetText("LEFT", "plok", 50, sf::Color(255, 140, 0, 255), 550, 470);
  this->SetText("RIGHT", "plok", 50, sf::Color(255, 140, 0, 255), 1200, 470);
  this->SetText("BACK", "plok", 50, sf::Color(255, 140, 0, 255), 550, 350);
  this->SetText("FRONT", "plok", 50, sf::Color(255, 140, 0, 255), 1200, 350);

  this->SetText(this->ctrlCam["UP"], "plok", 25, sf::Color::Red, 890, 420);
  this->SetText(this->ctrlCam["LEFT"], "plok", 25, sf::Color::Red, 585, 550);
  this->SetText(this->ctrlCam["DOWN"], "plok", 25, sf::Color::Red, 885, 550);
  this->SetText(this->ctrlCam["RIGHT"], "plok", 25, sf::Color::Red, 1260, 550);
  this->SetText(this->ctrlCam["BACK"], "plok", 25, sf::Color::Red, 585, 420);
  this->SetText(this->ctrlCam["FRONT"], "plok", 25, sf::Color::Red, 1260, 420);

  this->SetText("BACK", "plok", 50, sf::Color(255, 140, 0, 255), 50, 950);
  this->SetText("DEFAULT", "plok", 50, sf::Color(255, 140, 0, 255), 1550, 950);
}

void	Camera::Binding(){
  int value;
  this->ctrlCamBind->clear();
  if((value = keySFtoSD(this->ctrlCam["UP"])) != -1)
    (*this->ctrlCamBind)[value] = "up";
  if((value = keySFtoSD(this->ctrlCam["DOWN"])) != -1)
    (*this->ctrlCamBind)[value] = "down";
  if((value = keySFtoSD(this->ctrlCam["LEFT"])) != -1)
    (*this->ctrlCamBind)[value] = "left";
  if((value = keySFtoSD(this->ctrlCam["RIGHT"])) != -1)
    (*this->ctrlCamBind)[value] = "right";
  if((value = keySFtoSD(this->ctrlCam["BACK"])) != -1)
    (*this->ctrlCamBind)[keySFtoSD(this->ctrlCam["BACK"])] = "back";
  if((value = keySFtoSD(this->ctrlCam["FRONT"])) != -1)
    (*this->ctrlCamBind)[value] = "front";
}

int	Camera::keySFtoSD(const std::string &key) const{
  for (std::map<std::string, int>::const_iterator it = (*G_AlphaSFtoSD).begin(); it != (*G_AlphaSFtoSD).end(); ++it)
    if (key == it->first)
      return(it->second);
  return -1;
}


bool	Camera::KeyAvailable(const std::string &key, const std::string &index){
  if (ctrlCam[index] == key)
    return true;
  if (key == ctrlCam["UP"] ||key == ctrlCam["DOWN"] ||
      key == ctrlCam["BACK"] || key == ctrlCam["LEFT"] ||
      key == ctrlCam["FRONT"] || key == ctrlCam["RIGHT"])
    return false;
  return true;
}

void	Camera::KeyInput(const std::string &index)
{
 sf::Event	event;
 std::string	key;

 while (this->_Window->waitEvent(event))
   {
     if (event.type == sf::Event::KeyPressed)
       {
	 key  = this->_Alpha[event.key.code];
	 if(KeyAvailable(key, index) && key != ""){
	   this->ctrlCam[index] = key;
	   this->Display();
	   return;
	 }
       }
   }
}

void	Camera::CatchController(const sf::Event &event)
{
  std::string index = "";

  if (CheckEvent(event, 850, 1055, 415, 470))
    index = "UP";
  else if (CheckEvent(event, 550, 755, 535, 590))
    index = "LEFT";
  else if (CheckEvent(event, 850, 1050, 540, 590))
    index = "DOWN";
  else if (CheckEvent(event, 1225, 1425, 540, 590))
    index = "RIGHT";
  else if (CheckEvent(event, 550, 755, 415, 470))
    index = "BACK";
  else if (CheckEvent(event, 1225, 1425, 415, 470))
    index = "FRONT";
  if (index.size() > 1){
    this->ctrlCam[index] = "Key";
    this->Display();
    this->_Window->display();
    KeyInput(index);
  }
}

void	Camera::Run()
{
  sf::Event	event;
  std::string	str;

  this->PlaySound("yay");
  this->LoadSprite(RESOURCEPATH"Cam.png", &this->_Sprite);
  while (this->_Window->isOpen())
    {
      while (this->_Window->pollEvent(event))
	{
	  this->Quit(event);
	  if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
	    if (CheckEvent(event,1550, 1900, 960, 1010))
	      InitKBoard();
	    if (CheckEvent(event, 15, 285, 970, 1045))
	      return;
	    this->CatchController(event);
	  }
	}
      this->_Window->clear();
      this->Display();
      this->_Window->display();
    }
}
