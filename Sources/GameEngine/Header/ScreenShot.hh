//
// ScreenShot.hh for  in /home/lelabo_m/rendu/cpp_bomberman
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Sun Jun 15 13:48:59 2014 Marc Le Labourier
// Last update Sun Jun 15 14:05:37 2014 Marc Le Labourier
//

#ifndef SCREENSHOT_HH_
# define SCREENSHOT_HH_

#include <string>

namespace Graphic
{
  class MyScreenShot
  {
  public:
    MyScreenShot(const std::string&, int, int);
    ~MyScreenShot() {};
    void	SetName(const std::string&);
    void	SetWindow(int, int);
    void	TakeScreenShot();
  private:
    const std::string&	_name;
    int		_x;
    int		_y;
  };
}

#endif /* !SCREENSHOT_HH_ */
