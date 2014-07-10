//
// Settings.cpp for  in /home/lelabo_m/rendu/cpp_bomberman/GameEngine
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Mon May 26 14:52:16 2014 Marc Le Labourier
// Last update Sun Jun 15 20:50:01 2014 Imad Roughi
//

#include "Settings.hpp"
#include "Controls.hh"
#include "Player.hh"
#include "ScoreComponent.hh"

Settings::GameContext	*G_GameSettings = new Settings::GameContext();

Settings::Player::Player(std::string newname, Character newcharacter, InputType IT)
{
  Controls      *Co = Controls::Instance();

  this->name = newname;
  this->character = newcharacter;
  this->input = new InputConf();
  this->input->type2 = IT;
  this->input->id = IT % 2;
  if (IT == KEYBOARD1)
    {
      this->input->type = Event::KEYBOARD;
      this->input->keyconf = Co->getCtrlK1();
    }
  else if (IT == KEYBOARD2)
    {
      this->input->type = Event::KEYBOARD;
      this->input->keyconf = Co->getCtrlK2();
    }
  else
    this->input->type = Event::XBOX;
}

void  Settings::SavePlayer::SetPlayer(Bomb::IEntity *player)
{
  if (player)
  {
    Bomb::BombComponent *bomb = static_cast<Bomb::BombComponent *>(player->GetComponent(Bomb::Bomb_c));
    Bomb::LifeComponent *l = static_cast<Bomb::LifeComponent *>(player->GetComponent(Bomb::Life_c));
    Bomb::ScoreComponent *s = static_cast<Bomb::ScoreComponent *>(player->GetComponent(Bomb::Score_c));
    Bomb::PositionComponent *pos = static_cast<Bomb::PositionComponent *>(player->GetComponent(Bomb::Position_c));

    if (pos && s && l && bomb)
    {
      this->posX = pos->GetPosition(Bomb::PositionComponent::X);
      this->posY = pos->GetPosition(Bomb::PositionComponent::Y);
      this->rotation = pos->GetRotation();
      this->life = l->GetLife();
      this->maxLife = l->GetMaxLife();
      this->score = s->GetScore();
      this->sizeBomb = bomb->GetSizeBomb(Bomb::Normal);
      this->nbBombs = bomb->GetMapNbBomb()[Bomb::Normal];
    }
  }
}
