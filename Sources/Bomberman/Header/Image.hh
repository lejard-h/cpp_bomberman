/*
** Image.cpp for BOmber in /home/thomas_1/Desktop/Projets/Bomberman/cpp_bomberman/Bomberman
**
** Made by Pierre-Yves THOMAS
** Login   <thomas_1@epitech.net>
**
** Started on  Sat Jun  07 17:35:31 2014 Pierre-Yves THOMAS
// Last update Thu Jun 12 16:11:03 2014 Marc Le Labourier
*/


#ifndef __IMAGES_HH
#define __IMAGES_HH

#include <string>
#include "GameObject.hh"
#include "PositionComponent.hh"
#include "PhysicComponent.hh"
#include "GraphicComponent.hh"

namespace Bomb
{
  class Image : public GameObject
  {
  public:
    Image(int, int, int, int, std::string, std::string);
    Image();
    virtual GameObject *Clone() const;

  protected:
    int 	posX;
    int 	posY;
    int 	width;
    int 	height;
    std::string	path;
    std::string	name;

  public:
    int 	getWidth() const;
    int 	getHeight() const;
    int 	getPosX() const;
    int 	getPosY() const;
    void 	setWidth(int);
    void	setHeight(int);
    void	setPosX(int);
    void	setPosY(int);
    void 	setInformations(int, int, int, int);
    const std::string &getPath() const;
    const std::string &getName() const;
    void	setName(const std::string &);
    void 	setPath(const std::string &);
  };
}

#endif
