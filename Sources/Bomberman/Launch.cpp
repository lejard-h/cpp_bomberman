//
// Launch.cpp for  in /home/lelabo_m/rendu/cpp_bomberman
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Fri Jun 13 15:52:28 2014 Marc Le Labourier
// Last update Sun Jun 15 13:40:56 2014 Marc Le Labourier
//

#include <exception>
#include <stdio.h>
#include "Engine.hh"
#include "Settings.hpp"
#include "MapComponent.hh"
#include "DestructibleBox.hh"
#include "UndestructibleBox.hh"
#include "Image.hh"
#include "Player.hh"
#include "Cam.hh"
#include "FireAnim.hh"
#include "BonusAddBomb.hh"
#include "BonusSpeedPlayer.hh"
#include "BonusSizeBomb.hh"
#include "ClassicMode.hh"
#include "Menu.hh"

std::string*	path1 = new std::string(ASSETPATH"Sounds/bo.mp3");
std::string*	test1 = new std::string("test1");

bool	freefunc()
{
  // delete path1;
  // delete test1;
  //G_GameSettings->conf.clear();
  return true;
}

void  InitGameMode()
{
  G_ObjectsContainer->AddObj(G_EntityFactory->Create(Bomb::ClassicMode_o));
}

void  InitGameObject()
{
  Bomb::DestructibleBox*    box = new Bomb::DestructibleBox();

  G_EntityFactory->Register(Bomb::DestructibleBox_o, box);
  G_EvDispatcher->SendEvent(new Event::GraphicEvent(box, Graphic::MESHINIT), Event::COMMON);

  Bomb::NormalBomb*   bomb = new Bomb::NormalBomb();
  G_EntityFactory->Register(Bomb::NormalBomb_o, bomb);
  G_EvDispatcher->SendEvent(new Event::GraphicEvent(bomb, Graphic::MESHINIT), Event::COMMON);

  Bomb::ClassicMode*   classicMode = new Bomb::ClassicMode();
  G_EntityFactory->Register(Bomb::ClassicMode_o, classicMode);

  Bomb::BonusAddBomb*   addBomb = new Bomb::BonusAddBomb();
  G_EntityFactory->Register(Bomb::BonusAddBomb_o, addBomb);
  G_EvDispatcher->SendEvent(new Event::GraphicEvent(addBomb, Graphic::MESHINIT), Event::COMMON);

  Bomb::UndestructibleBox*  box2 = new Bomb::UndestructibleBox();
  G_EntityFactory->Register(Bomb::UndestructibleBox_o, box2);
  G_EvDispatcher->SendEvent(new Event::GraphicEvent(box2, Graphic::MESHINIT), Event::COMMON);

  Bomb::BonusSizeBomb*  sizeBomb = new Bomb::BonusSizeBomb();
  G_EntityFactory->Register(Bomb::BonusSizeBomb_o, sizeBomb);
  G_EvDispatcher->SendEvent(new Event::GraphicEvent(sizeBomb, Graphic::MESHINIT), Event::COMMON);


  Bomb::BonusSpeedPlayer*  speedPlayer = new Bomb::BonusSpeedPlayer();
  G_EntityFactory->Register(Bomb::BonusSpeed_o, speedPlayer);
  G_EvDispatcher->SendEvent(new Event::GraphicEvent(speedPlayer, Graphic::MESHINIT), Event::COMMON);

  Bomb::World   *map = new Bomb::World();
  G_ObjectsContainer->AddObj(map);
  G_EvDispatcher->SendEvent(new Event::GraphicEvent(map, Graphic::MESHINIT), Event::COMMON);
  G_EvDispatcher->SendEvent(new Event::GraphicEvent(map, Graphic::MESHADD), Event::COMMON);

  Bomb::GameCam*      cam = new Bomb::GameCam();
  G_ObjectsContainer->AddObj(cam);
  Bomb::FireAnim*     fire = new Bomb::FireAnim();
  G_EntityFactory->Register(Bomb::FireAnim_o, fire);
  G_EvDispatcher->SendEvent(new Event::AnimeEvent(fire, 0.0, 0.0, 0, Graphic::ANIMINIT), Event::COMMON);
}

void  InitPlayer()
{
  Bomb::Player  *original = new Bomb::Player();
  G_EntityFactory->Register(Bomb::Player_o, original);
  G_EvDispatcher->SendEvent(new Event::GraphicEvent(original, Graphic::MESHINIT), Event::COMMON);

  for (size_t i = 0; i < G_GameSettings->nb_players; ++i)
    {
      Bomb::IEntity*  player = G_EntityFactory->Create(Bomb::Player_o);
      G_ObjectsContainer->AddObj(player);
    }
  for (size_t i = 0; i < G_GameSettings->nb_ia; ++i)
    {
      Bomb::IEntity*  player = G_EntityFactory->Create(Bomb::Player_o);
      G_ObjectsContainer->AddObj(player);
    }
}

void  LoadGame()
{
  if (G_GameSettings && G_GameSettings->launchtype == Settings::LOADED)
  {
    std::ifstream ofile(G_GameSettings->Save.c_str());
    boost::archive::binary_iarchive iTextArchive(ofile);

    iTextArchive.register_type(static_cast<Settings::GameContext *>(0));
    iTextArchive.register_type(static_cast<Settings::Map *>(0));
    iTextArchive.register_type(static_cast<Settings::Player *>(0));
    iTextArchive.register_type(static_cast<Settings::InputConf *>(0));
    iTextArchive.register_type(static_cast<Settings::SavePlayer *>(0));

    iTextArchive >> G_GameSettings;
    G_GameSettings->launchtype = Settings::LOADED;
  }
}

void  InitBackground()
{
  Bomb::Image   *img;
  img = new Bomb::Image(0, 0, WIN_X, WIN_Y, "background", MODELPATH"background.tga");
  G_EvDispatcher->SendEvent(new Event::GraphicEvent(img, Graphic::MESHINIT), Event::COMMON);
  G_EvDispatcher->SendEvent(new Event::GraphicEvent(img, Graphic::MESHADD), Event::COMMON);
}

void  InitMenu()
{
  Bomb::Menu    *m = new Bomb::Menu(0, 0, 250, 500, "menu", ASSETPATH"Menu/");
  G_ObjectsContainer->AddObj(m);
}

bool	initializer()
{
  try
  {
    G_EntityFactory = new Pattern::Factory<Bomb::IEntity, Bomb::GameObjectTag>();
    G_ObjectsContainer = new Bomb::ObjContainer();
    G_GameSettings->gameState = Settings::START;

    LoadGame();
    InitBackground();
    InitMenu();
    InitGameObject();
    InitPlayer();
    InitGameMode();
  }
  catch (Bomb::EngineException &e)
  {
    std::cerr << e.what() << std::endl;
    G_EvDispatcher->SendEvent(new Event::EngineEvent(Event::ENGINEERROR), Event::COMMON);
    G_GameSettings->gameState = Settings::END;
    return false;
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
    G_EvDispatcher->SendEvent(new Event::EngineEvent(Event::ENGINEERROR), Event::COMMON);
    G_GameSettings->gameState = Settings::END;
    return false;
  }

  return true;
}

int	launchgame()
{
  Bomb::Player::Reset();
  glm::mat4 projection;
  glm::mat4 transformation;
  projection = glm::perspective(60.0f, 1920.0f / 1080.0f, 0.1f, 200.0f);
  transformation
    = glm::lookAt(glm::vec3(0, (G_GameSettings->map.x > G_GameSettings->map.y) ?
			    (G_GameSettings->map.x + 5) : (G_GameSettings->map.y + 5),
			    10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
  Graphic::OGLContext*	ogl = new Graphic::OGLContext(projection, transformation);
  ogl->Init(WINSIZE_X, WINSIZE_Y);
  Bomb::Engine	eng(ogl, initializer, freefunc);
  try
    {
      eng.Init();
      G_EvDispatcher->SendEvent(new Event::AudioEvent(path1, test1,
						      G_GameSettings->volume,
						    Audio::LOAD), Event::COMMON);
       G_EvDispatcher->SendEvent(new Event::AudioEvent(path1, test1,
       						      G_GameSettings->volume,
       						      Audio::PLAY), Event::COMMON);
      eng.Start();
      //  G_ObjectsContainer->dump();
      eng.Stop();
      delete ogl;
    }
  catch (std::exception& e)
    {
      std::cerr << "Catch exeception in main" << std::endl;
      std::cerr << e.what() << std::endl;
      //delete ogl;
      return 1;
    }
  return 0;
}
