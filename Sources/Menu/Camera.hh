//
// Camera.hh for controls in /home/roughi_i/epitech/c++/bomberman/cpp_bomberman/Menu
//
// Made by Imad Roughi
// Login   <roughi_i@epitech.net>
//
// Started on  Sat Jun  7 18:38:38 2014 Imad Roughi
// Last update Sun Jun 15 21:49:28 2014 Imad Roughi
//


#ifndef CAMERA_HH_
#define CAMERA_HH_

#include <list>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <map>

#include "Graphics.hpp"
#include "Menu.hh"

class Camera : public Menu
{
 private:
  static Camera			*_Inst;
  std::map<std::string, std::string>	ctrlCam;
  std::map<int, std::string>		*ctrlCamBind;
public:
  Camera();
  ~Camera();
  static Camera		*Instance();
  void			Run();
  void			Display();
  void			Binding();
  void			InitKBoard();
  void			KeyInput(const std::string &index);
  void			CatchController(const sf::Event &);
  int			keySFtoSD(const std::string &key) const;
  bool			KeyAvailable(const std::string &, const std::string &index);
  std::map<int, std::string>		*getCtrlCam() const;
};
#endif
