/*
** ScoreComponent.cpp for Bomberman in /home/lejard_h/cpp_bomberman/Bomberman
**
** Made by hadrien lejard         
** Login   <lejard_h@epitech.net>
**
** Started on  mer. juin  11 00:42:45 2014 hadrien lejard         
** Last update mer. juin  11 00:42:45 2014 hadrien lejard         
*/

#include "ScoreComponent.hh"
#include "ScoreEvent.hh"

Bomb::ScoreComponent::ScoreComponent() : _score(0)
{
	this->ctor(Score_c);

	this->_mapPoints[Event::DamageScoring][Settings::CLASSIC] = 1;
	this->_mapPoints[Event::DeathScoring][Settings::CLASSIC] = -10;
	this->_mapPoints[Event::TakeDamageScoring][Settings::CLASSIC] = -1;
	this->_mapPoints[Event::WinGame][Settings::CLASSIC] = 0;

	this->_mapPoints[Event::DamageScoring][Settings::SURVIVAL] = 1;
	this->_mapPoints[Event::DeathScoring][Settings::SURVIVAL] = -10;
	this->_mapPoints[Event::TakeDamageScoring][Settings::SURVIVAL] = -1;
	this->_mapPoints[Event::WinGame][Settings::SURVIVAL] = 100;

	this->_mapPoints[Event::DamageScoring][Settings::TERRITORY] = 1;
	this->_mapPoints[Event::DeathScoring][Settings::TERRITORY] = -5;
	this->_mapPoints[Event::TakeDamageScoring][Settings::TERRITORY] = -1;
	this->_mapPoints[Event::WinGame][Settings::TERRITORY] = 100;

	_pointsByTarget[Player_o][Settings::CLASSIC] = 10;
	_pointsByTarget[Player_o][Settings::SURVIVAL] = 10;
	_pointsByTarget[Player_o][Settings::TERRITORY] = 1;

	_pointsByTarget[DestructibleBox_o][Settings::CLASSIC] = 1;
	_pointsByTarget[DestructibleBox_o][Settings::SURVIVAL] = 0;
	_pointsByTarget[DestructibleBox_o][Settings::TERRITORY] = 10;
}

void	Bomb::ScoreComponent::SetScore(int s)
{
	this->_score = s;
}

Bomb::ScoreComponent::~ScoreComponent()
{
}

void 	Bomb::ScoreComponent::OnEvent(Event::Event *e)
{
	if (e && e->Scope() == Event::GAME && e->Subject() == Event::SCORE)
		this->_events.push_back(e);
	else
		delete e;
}

void	Bomb::ScoreComponent::UpdateScore(enum Event::ScoreAction action, int OnId, int targetId)
{
	int	newScore;

	if (OnId == this->GetParent()->GetId())
	{
		newScore = this->_mapPoints[action][G_GameSettings->gamemode];
		if (action == Event::KillTargetScoring && G_ObjectsContainer && targetId >= 0 && targetId != OnId)
		{
			IEntity *target = G_ObjectsContainer->GetObjById(targetId);
			if (target)
				newScore = this->_pointsByTarget[target->GetTag()][G_GameSettings->gamemode];
		}
		this->_score += newScore;

		if (action == Event::TakeDamageScoring && targetId >= 0 && G_ObjectsContainer)
		{
			IEntity *target = G_ObjectsContainer->GetObjById(OnId);
			if (target)
			{
				LifeComponent	*life = static_cast<LifeComponent *>(target->GetComponent(Life_c));
				if (life && life->GetLife() <= 1)
				{
					G_EvDispatcher->SendEvent(new Event::ScoreEvent(Event::KillTargetScoring, targetId, OnId), 
						Event::COMMON);
					this->_score += this->_mapPoints[Event::DeathScoring][G_GameSettings->gamemode];
				}
			}
		}
	}
}

void	Bomb::ScoreComponent::Update()
{
	if (this->_events.size())
	{
		Event::ScoreEvent	*ev = static_cast<Event::ScoreEvent *>(this->_events.front());
		this->_events.pop_front();

		this->UpdateScore(ev->action, ev->id, ev->targetId);
	}
}

int		Bomb::ScoreComponent::GetScore() const
{
	return this->_score;
}