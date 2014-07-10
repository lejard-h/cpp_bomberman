/*
** Player.hh for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Bomberman/Header
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  ven. mai  30 11:21:51 2014 hadrien lejard
// Last update Sun Jun 15 14:49:36 2014 Marc Le Labourier
*/

#ifndef __PLAYER_HH__
#define __PLAYER_HH__

#include <list>
#include "Event.hpp"
#include "GameObject.hh"
#include "PositionComponent.hh"
#include "PhysicComponent.hh"
#include "LifeComponent.hh"
#include "PlayerInputComponent.hh"
#include "IaComponent.hh"
#include "AudioComponent.hh"
#include "BombComponent.hh"
#include "GraphicComponent.hh"

namespace Bomb
{

#define PLAYER_VELOCITY	(0.15)
#define PLAYER_LIFE	(1)
#define PLAYER_HITBOX	(0.2)

  enum PlayerType	{ Ia, Player1, Player2, Player3, Player4, PlayerUndefined};
  typedef std::map<Settings::Character, std::string*> PlayerData;
  typedef std::map<Settings::Character, double> PlayerSize;

  class Player : public GameObject
  {
  public:
    Player();
    ~Player();
    PlayerType GetPlayerType();
    void	Start();
    virtual void OnEvent(Event::Event *);
    virtual GameObject	*Clone() const;
    static void		Reset();
    static size_t	_nb;
    void  Respawn();
    void  EventTreatment();
    void  Update();
    PlayerData*	GetNames();
    PlayerData*	GetPaths();
    PlayerData*	GetSounds();
    PlayerSize*	GetSizes();
    std::string*	GetMyName();
    const std::string*	GetMyPath() const;
    const std::string*	GetMySound() const;
    double		GetMySize() const;
  private:
    std::list<Event::Event *> _events;
    void	InitInput();
    size_t	GetNbPlayer();
    // TMP
    int			_slot;
    std::string*	_errorsound;
    std::string*	_myname;
    std::string*	_mypath;
    std::string*	_mysound;
    double		_mysize;
    PlayerData		_name;
    PlayerData		_path;
    PlayerData		_sound;
    PlayerData		_soundpath;
    PlayerSize		_size;
  };
}

#endif
