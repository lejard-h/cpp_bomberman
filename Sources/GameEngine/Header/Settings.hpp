//
// Settings.hpp for  in /home/lelabo_m/rendu/cpp_bomberman/GameEngine
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Sun May 25 15:30:14 2014 Marc Le Labourier
// Last update Sun Jun 15 15:55:18 2014 Marc Le Labourier
//

#ifndef SETTINGS_HPP_
# define SETTINGS_HPP_

#include <map>
#include <string>
#include <cstdlib>
#include <vector>
#include "boost/serialization/string.hpp"
#include "boost/serialization/map.hpp"
#include "boost/serialization/list.hpp"
#include "boost/serialization/vector.hpp"
#include "boost/archive/binary_iarchive.hpp"
#include "boost/archive/binary_oarchive.hpp"
#include "Event.hpp"
#include "GraphicContext.hh"

#define ASSETPATH "Asset/"
#define MODELPATH ASSETPATH"Model/"
#define SOUNDPATH ASSETPATH"Sounds/"
#define NB_KEYBOARD 3
#define WIN_X 1000
#define WIN_Y 800
#define WINSIZE_X 1920
#define WINSIZE_Y 1080

namespace Settings
{
  enum InputType {KEYBOARD1 = 0, KEYBOARD2, GAMEPAD1, GAMEPAD2};
  enum MapType {MAP, RANDOM};
  enum GameMode	{CLASSIC = 0, SURVIVAL, TERRITORY};
  enum IAMode {EASY = 0, MEDIUM, HARD};
  enum Character{RABBIT1 = 1, RABBIT2, MINION1, MINION2, IA};
  enum GameState {START, RUNNING, PAUSED, END};
  enum LaunchType {NEWGAME, LOADED, REPLAY};

  class InputConf
  {
  public:
    InputConf() {};
    ~InputConf() {};
    Event::InputType			type;
    Settings::InputType			type2;
    int					id;
    std::map<int, std::string>		keyconf;

    template<class Archive>
    void save(Archive &ar, const unsigned int) const
    {
      ar & this->type;
      ar & this->type2;
      ar & this->id;
      ar & this->keyconf;
    };

    template<class Archive>
    void load(Archive &ar, const unsigned int)
    {
      ar & this->type;
      ar & this->type2;
      ar & this->id;
      ar & this->keyconf;
    };

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
      boost::serialization::split_member(ar, *this, version);
    }
  };

  class Player
  {
  public:
    Player() {};
    Player(std::string, Character, InputType);
    ~Player() {};
    std::string	name;
    InputConf	*input;
    Character   character;
    // Skin
    // Skill (special power, ...)
    // Score

    template<class Archive>
    void save(Archive &ar, const unsigned int) const
    {
      ar & this->name;
      ar & this->input;
      ar & this->character;
    };

    template<class Archive>
    void load(Archive &ar, const unsigned int)
    {
      ar & this->name;
      ar & this->input;
      ar & this->character;
    };

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
      boost::serialization::split_member(ar, *this, version);
    }
  };

  class Map
  {
  public:
    Map() {}
    MapType     mapType;
    std::string mapPath;
    size_t      x;
    size_t      y;

    template<class Archive>
    void save(Archive &ar, const unsigned int) const
    {
      ar & this->mapType;
      ar & this->mapPath;
      ar & this->x;
      ar & this->y;
    };

    template<class Archive>
    void load(Archive &ar, const unsigned int)
    {
      ar & this->mapType;
      ar & this->mapPath;
      ar & this->x;
      ar & this->y;
    };

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
      boost::serialization::split_member(ar, *this, version);
    }
  };

  class SavePlayer
  {
  public:
    SavePlayer()
    {
      posX = 0.1;
      posY = 0.1;
      rotation = 0.1;
      life = 0;
      maxLife = 0;
      score = 0;
      sizeBomb = 1;
    };

    void  SetPlayer(Bomb::IEntity *);

    double  posX;
    double  posY;
    double  rotation;
    int     life;
    int     maxLife;
    int     score;
    int     sizeBomb;
    int     nbBombs;


template<class Archive>
    void save(Archive &ar, const unsigned int) const
    {
      ar & this->posX;
      ar & this->posY;
      ar & this->rotation;
      ar & this->life;
      ar & this->maxLife;
      ar & this->score;
      ar & this->sizeBomb;
      ar & this->nbBombs;
    };

template<class Archive>
    void load(Archive &ar, const unsigned int)
    {
      ar & this->posX;
      ar & this->posY;
      ar & this->rotation;
      ar & this->life;
      ar & this->maxLife;
      ar & this->score;
      ar & this->sizeBomb;
      ar & this->nbBombs;
    };

template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
      boost::serialization::split_member(ar, *this, version);
    }
  };

  class GameContext
  {
  public:
    GameContext()
    {
      gameState = START;
      nb_players = 1;
      nb_ia = 0;
      ialevel = EASY;
      map.mapType = RANDOM;
      map.mapPath = "";
      map.x = 10;
      map.y = 10;
      gamemode = CLASSIC;
      launchtype = NEWGAME;
      InputConf*      caminput = new InputConf();
      caminput->type = Event::KEYBOARD;
      caminput->type2 = KEYBOARD1;
      caminput->id = 0;
      caminput->keyconf[SDLK_KP_8] = "up";
      caminput->keyconf[SDLK_KP_5] = "down";
      caminput->keyconf[SDLK_KP_4] = "left";
      caminput->keyconf[SDLK_KP_6] = "right";
      caminput->keyconf[SDLK_KP_7] = "back";
      caminput->keyconf[SDLK_KP_9] = "front";
      cam = caminput;
      InputConf*      defaultinput = new InputConf();
      defaultinput->type = Event::KEYBOARD;
      defaultinput->type2 = KEYBOARD1;
      defaultinput->id = 0;
      defaultinput->keyconf[SDLK_UP] = "up";
      defaultinput->keyconf[SDLK_DOWN] = "down";
      defaultinput->keyconf[SDLK_LEFT] = "left";
      defaultinput->keyconf[SDLK_RIGHT] = "right";
      defaultinput->keyconf[SDLK_SPACE] = "bomb";
      Player	*p1 = new Player();
      p1->name = "Noob";
      p1->input = defaultinput;
      p1->character = RABBIT1;
      players.push_back(p1);
      SavePlayers.push_back(new SavePlayer());
      volume = 0.5;
      Save = "save";
      SaveState = false;
    };

    ~GameContext() {};
    GameState			gameState;
    //Player
    std::vector<Player*>	players;
    size_t			nb_players;
    // IA:
    size_t			nb_ia;
    IAMode			ialevel;
    //Map
    Map				map;
    // mode de jeu :
    GameMode			gamemode;
    LaunchType			launchtype;
    // Other:
    InputConf			*cam;
    float			volume; // 0.0 -> 1.0

    std::string               Save;
    std::vector<SavePlayer *> SavePlayers;
    bool		SaveState;

    template<class Archive>
    void save(Archive &ar, const unsigned int) const
    {
      ar & this->gameState;
      ar & this->nb_players;
      ar & this->players;
      ar & this->nb_ia;
      ar & this->ialevel;
      ar & this->map;
      ar & this->gamemode;
      ar & this->launchtype;
      ar & this->cam;
      ar & this->SavePlayers;
      ar & this->Save;
      ar & this->SaveState;
      ar & this->volume;
    };

    template<class Archive>
    void load(Archive &ar, const unsigned int)
    {
      ar & this->gameState;
      ar & this->nb_players;
      ar & this->players;
      ar & this->nb_ia;
      ar & this->ialevel;
      ar & this->map;
      ar & this->gamemode;
      ar & this->launchtype;
      ar & this->cam;
      ar & this->SavePlayers;
      ar & this->Save;
      ar & this->SaveState;
      ar & this->volume;
    };

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
      boost::serialization::split_member(ar, *this, version);
    }
  };
}

extern Settings::GameContext	*G_GameSettings;

#endif /* !SETTINGS_HH_ */
