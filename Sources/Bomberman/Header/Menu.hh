/*
** Image.cpp for BOmber in /home/thomas_1/Desktop/Projets/Bomberman/cpp_bomberman/Bomberman
**
** Made by Pierre-Yves THOMAS
** Login   <thomas_1@epitech.net>
**
** Started on  Sat Jun  07 17:35:31 2014 Pierre-Yves THOMAS
// Last update Sat Jun 14 18:44:35 2014 Marc Le Labourier
*/


#ifndef __MENU_HH
#define __MENU_HH

#include <string>
#include "Image.hh"
#include "Mutex.hh"

namespace Bomb
{
  typedef std::map<std::string, Image*> Sprite;
  typedef std::map<std::string, bool> SpriteState;

  class Menu : public Image
  {
  public:
    Menu(int, int, int, int, std::string, std::string);
    virtual GameObject *Clone() const;
    void		OnEvent(Event::Event*);
    Sprite*		GetSprite();
    SpriteState*	GetSpriteState();
    void		Reset();
    void		Std();
    void		Inc();
    void		Dec();
    void		Valid();
    void		Start();
    void		TreatEvent();
  private:
    int					_state;
    std::map<std::string, Image*>	_sprite;
    std::map<std::string, std::string>	_ressources;
    std::map<std::string, int>		_posX;
    std::map<std::string, int>		_posY;
    std::map<std::string, int>		_dec;
    std::map<std::string, bool>		_spritestate;
  };
}

#endif
