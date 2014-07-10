//
// Controls.hh for controls in /home/roughi_i/epitech/c++/bomberman/cpp_bomberman/Menu
//
// Made by Imad Roughi
// Login   <roughi_i@epitech.net>
//
// Started on  Sat Jun  7 18:38:38 2014 Imad Roughi
// Last update Sun Jun 15 21:46:19 2014 Imad Roughi
//


#ifndef CONTROLS_HH_
#define CONTROLS_HH_

#include <list>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <map>

#include "KeyboardManager.hh"
#include "Graphics.hpp"
#include "Menu.hh"

class Controls : public Menu
{
 private:
  static Controls				*_Inst;
  std::map<std::string, std::string>		ctrlK1;
  std::map<std::string, std::string>		ctrlK2;
  std::map<int, std::string>			*ctrlK1Bind;
  std::map<int, std::string>			*ctrlK2Bind;
  std::map<std::string, std::string>		ctrlCu;
  int						num_play;
public:
  Controls();
  ~Controls();
  const std::map<int, std::string>			&getCtrlK1() const;
  const std::map<int, std::string>			&getCtrlK2() const;
  int			keySFtoSD(const std::string &key) const;
  void			Run();
  void			Binding();
  void			Display();
  void			InitKBoards();
  void			LoadAlphaSFtoSD() const;
  void			KeyInput(const std::string &index);
  void			CatchController(const sf::Event &);
  bool			isNum(const std::string &) const;
  bool			KeyAvailable(const std::string &, const std::string &index);

  static Controls	*Instance();
};
#endif
