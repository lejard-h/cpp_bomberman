//
// ClassicMode.cpp for  in /home/lelabo_m/rendu/cpp_bomberman
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Sun Jun 15 19:56:31 2014 Marc Le Labourier
// Last update Sun Jun 15 19:56:32 2014 Marc Le Labourier
//

#include <sys/stat.h>
#include <fstream>
#include "ClassicMode.hh"
#include "Settings.hpp"
#include "EventDispatcher.hh"
#include "PositionComponent.hh"

Bomb::ClassicMode::ClassicMode()
{
  this->ctor(ClassicMode_o);
  this->_isDestroy = false;

  TimerComponent	*timer = new TimerComponent(180);
  timer->AssignEntity(this);
  this->AddComponent(timer);
}

Bomb::ClassicMode::~ClassicMode()
{
	if (!this->_isDestroy)
		this->Destroy();
}

bool  IsOnlyOnePlayer()
{
  Bomb::ListObj *list_players = 0;
  size_t  count = 0;

  if (G_ObjectsContainer && (list_players = G_ObjectsContainer->GetObjByTag(Bomb::Player_o)))
  {
    if (list_players)
    {
      for (std::list<Bomb::IEntity *>::iterator it = list_players->Begin();
        it != list_players->End();
        ++it)
      {
        Bomb::LifeComponent *life = static_cast<Bomb::LifeComponent *>((*it)->GetComponent(Bomb::Life_c));
        if (life && life->GetLife() > 0)
          count++;
      }
    }
  }
  if (count <= 1)
    return true;
  return false;
}

void	Bomb::ClassicMode::Update()
{
  if (G_GameSettings->gamemode == Settings::SURVIVAL && IsOnlyOnePlayer())
    this->Destroy();
  else if (this->HasComponent(Timer_c) && !this->_isDestroy)
    {
      TimerComponent	*timer = static_cast<TimerComponent *>(this->GetComponent(Timer_c));

      timer->Update();
      if (timer->IsDone() && !this->_isDestroy && G_GameSettings->gamemode != Settings::SURVIVAL)
       this->Destroy();
    }
    this->SaveScore();
}

void  Bomb::ClassicMode::SaveScore()
{
  if (G_ObjectsContainer && G_GameSettings)
  {
    ListObj *listPlayer = G_ObjectsContainer->GetObjByTag(Player_o);

    if (listPlayer)
    {
      size_t idx = 0;

      std::fstream fs;

      mkdir("./Score", 0774);
      fs.open("./Score/scoreInGame.txt", std::ios::out | std::ios::trunc);

      for (std::list<IEntity *>::iterator it = listPlayer->Begin();
        it != listPlayer->End();
        ++it)
      {
        Player  *current = static_cast<Player *>(*it);
        ScoreComponent *score = static_cast<ScoreComponent *>(current->GetComponent(Score_c));

        if (score && G_GameSettings && idx < G_GameSettings->players.size())
          fs << G_GameSettings->players[idx]->name << "." << score->GetScore() << ";";
        ++idx;
      }
      fs.close();
    }
  }
}

void	Bomb::ClassicMode::Destroy()
{
  this->_isDestroy = true;
  if (G_GameSettings)
    G_GameSettings->gameState = Settings::END;
  if (G_EvDispatcher)
    G_EvDispatcher->SendEvent(new Event::EngineEvent(Event::ENGINEQUIT), Event::COMMON);
}

Bomb::GameObject	*Bomb::ClassicMode::Clone() const
{
  return new ClassicMode();
}
