/*
** IaComponent.cpp for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Bomberman
**
** Made by hadrien lejard         
** Login   <lejard_h@epitech.net>
**
** Started on  ven. mai  30 12:29:27 2014 hadrien lejard         
** Last update ven. mai  30 12:29:27 2014 hadrien lejard         
*/

#include <iostream>
#include "IaComponent.hh"
#include "IAactions.hh"
#include "BombComponent.hh"
#include "Astar.hh"


Bomb::IaComponent::IaComponent(Settings::IAMode mode) : _IAmode(mode)
{
	this->ctor(Ia_c);
	this->goToCenter = true;
	this->prevSquare = std::pair<int, int>(0, 0);
}

Bomb::IaComponent::IaComponent(IaComponent &ia) : InputComponent(ia)
{
	this->_IAmode = ia.GetMode();
}

Bomb::IaComponent	&Bomb::IaComponent::operator=(IaComponent &ia)
{
	this->_IAmode = ia.GetMode();
	return *this;
}

Settings::IAMode	Bomb::IaComponent::GetMode()
{
	return this->_IAmode;
}

void 	Bomb::IaComponent::moveIA(const IAactions &actions)
{
	PositionComponent	*positionIA = dynamic_cast<PositionComponent *>(this->GetParent()->GetComponent(Position_c));
	PhysicComponent 	*physic 	= static_cast<PhysicComponent *>(this->GetParent()->GetComponent(Physics_c));

   	physic->SetVelocity(PLAYER_VELOCITY);
	if (positionIA && physic)
	{
		std::list<std::pair<double, double> > safePath = actions.getShortestPath();
		std::list<std::pair<double, double> >::iterator	it = safePath.begin();
		if (safePath.size() >= 2)
		{
			double sX 		= positionIA->GetPosition(PositionComponent::X);
			double sY 		= positionIA->GetPosition(PositionComponent::Y);
			double velocity = physic->GetVelocity();
			std::pair<double, double> 	posB = std::pair<double, double>(sX, sY);
			std::pair<double, double> 	posE = std::pair<double, double>(safePath.front());
			if (static_cast<std::pair<int, int> >(posB) != prevSquare)
				goToCenter = true;

			if (goToCenter == true
				&& posB.first >= posE.first - velocity && posB.first <= posE.first + velocity
				&& posB.second >= posE.second - velocity && posB.second <= posE.second + velocity)
				goToCenter = false;
			if (!goToCenter)
				++it;

			posE 	= std::pair<double, double>(*it);



			if (posB.first != posE.first && (posB.first <= posE.first - 0.1 || posB.first >= posE.first + 0.1))
				(posB.first > posE.first) ? (this->Move("left")) : (this->Move("right"));
			else
				(posB.second > posE.second) ? (this->Move("up")) : (this->Move("down"));

			prevSquare = static_cast<std::pair<int, int> >(safePath.front());
		}
	}
}

void	Bomb::IaComponent::Update()
{
	int count;
	IAactions actions(this);
 
	if (actions.isSafe() == true)
	{

		for (count = 1 ; count <= 5 && actions.getBonusAtRange(count) != true ; count++);
		if (count <= 5 && actions.findShortestPath(actions.getBonusPath()) == true)
		{
			this->moveIA(actions);
		}
		else
		{
			if (actions.isDestructibleObjectOnRange())
			{
				this->PutBomb();
			}
			else
			{
				for (count = 1 ; count <= 5 && actions.getDestructibleObjectAtRange(count) != true ; count++);
				if (count <= 5 && actions.findShortestPath(actions.getDestruciblePath()) == true)
				{
			
					this->moveIA(actions);
				}
				else
				{
					if (actions.findOtherAI() == true && actions.findShortestPath(actions.getOtherAIPath()) == true)
					{
						this->moveIA(actions);
					}
				}
			}
		}
	}	
	else
	{

		for (count = 1 ; count < 5  && actions.getPathAtRange(count) == false ; count++);
		if (count != 5 && actions.findShortestPath(actions.getSafePath()) == true)
		{
			this->moveIA(actions);
		}
	}
	
	++count;
}

void	Bomb::IaComponent::EasyMode() const
{

}

void	Bomb::IaComponent::MediumMode() const
{

}

void	Bomb::IaComponent::HardMode() const
{

}