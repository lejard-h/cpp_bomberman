/*
** InputComponent.cpp for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Bomberman
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  jeu. mai  29 14:32:00 2014 hadrien lejard
// Last update Sun Jun 15 18:48:26 2014 Marc Le Labourier
*/

#include "InputComponent.hh"
#include "PlayerInputComponent.hh"
#include "GraphicComponent.hh"
#include "Player.hh"

Bomb::PlayerInputComponent::PlayerInputComponent(int slot) : _slot(slot)// Joueur 1 ou 2 ou 3 ou 4 ...
{
  this->ctor(PlayerInput_c);
  _lastevent = 0;
}

void	Bomb::PlayerInputComponent::Start()
{
  G_EvDispatcher->AddSubscriber(Event::INPUT, this);
  _lastevent = 0;
}

void	Bomb::PlayerInputComponent::Update()
{
  Event::InputType type = G_GameSettings->players[this->_slot]->input->type;
  while (!this->_events.empty() && G_GameSettings->players[this->_slot]->input)
    {
      Event::InputEvent	*ev = static_cast<Event::InputEvent *>(this->_events.front());
      this->_events.pop_front();
      if (!ev || ev->Subject() != type)
	{
	  if (ev)
	    delete ev;
	  continue;
	}
      if (_lastevent)
	delete _lastevent;
      _lastevent = ev;
      this->_events.clear();
      break;
    }
  if (!_lastevent)
    return ;
  if (_lastevent->Subject() == Event::KEYBOARD)
    {
      Event::KeyboardEvent*	keyev
	= dynamic_cast<Event::KeyboardEvent*>(_lastevent);
      if (keyev)
	EventKeyboard(keyev);
    }
  else if (_lastevent && _lastevent->Subject() == Event::XBOX)
    {
      Event::XboxEvent*	xboxev
	= dynamic_cast<Event::XboxEvent*>(_lastevent);
      if (xboxev)
	EventXbox(xboxev);
    }
}

void		Bomb::PlayerInputComponent::EventXbox(Event::XboxEvent* ev)
{
  std::map<int, std::string>	selectaction;

  selectaction[-1] = "";
  selectaction[90] = "up";
  selectaction[0] = "right";
  selectaction[270] = "down";
  selectaction[180] = "left";

  IComponent*	compo = this->GetParent()->GetComponent(Bomb::Render_c);
  int slot = G_GameSettings->players[this->_slot]->input->id;
  if (slot >= ev->slot)
    return ;
  std::vector< std::vector<int>* >*	buttons = ev->data;
  std::string	action;

  if ((*(*buttons)[slot])[0])
    {
      this->PutBomb();
      delete this->_lastevent;
      this->_lastevent = 0;
    }
  else if ((*(*buttons)[slot])[Event::XboxManager::STICK1])
    {
      if (compo)
	{
	  MeshComponent*  mesh = dynamic_cast<MeshComponent*>(compo);
	  Player*		p = dynamic_cast<Player*>(this->GetParent());
	  if (mesh && p)
	    {
	      mesh->SetName(p->GetMyName());
	      mesh->SetAnime("run", 0, true);
	    }
	}
      int angle = (*(*buttons)[slot])[Event::XboxManager::STICK1];
    this->Move(angle);
  }
  else
  {
    if (compo)
    {
      MeshComponent*  mesh = dynamic_cast<MeshComponent*>(compo);
      Player*		p = dynamic_cast<Player*>(this->GetParent());
      if (mesh && p)
	{
	  mesh->SetName(p->GetMyName());
	  mesh->SetAnime("run", 0, true);
	}
    }
    action = selectaction[(*(*buttons)[slot])[13]];
    if ((*(*buttons)[slot])[13] == -1)
    {
      delete _lastevent;
      _lastevent = 0;
    }
    this->Move(action);
  }
}

void		Bomb::PlayerInputComponent::EventKeyboard(Event::KeyboardEvent* ev)
{
  for (std::map<int, std::string>::iterator it
	 = G_GameSettings->players[this->_slot]->input->keyconf.begin();
       it != G_GameSettings->players[this->_slot]->input->keyconf.end();
       ++it)
    {
      int	key = it->first;
      std::string action = it->second;
      keyMap_itConst	it_key = ev->data.find(key);
      if (it_key != ev->data.end() && it_key->second == true)
	{
	  IComponent*	compo = this->GetParent()->GetComponent(Bomb::Render_c);
	  if (this->_rMap.find(action) != this->_rMap.end())
	    {
	      if (compo)
		{
		  MeshComponent*  mesh = dynamic_cast<MeshComponent*>(compo);
		  Player*		p = dynamic_cast<Player*>(this->GetParent());
		  if (mesh && p)
		    {
		      mesh->SetName(p->GetMyName());
		      mesh->SetAnime("run", 0, true);
		    }
		}
	      this->Move(action);
	    }
	  else if (action == "bomb")
	    {
	      this->PutBomb();
	      delete this->_lastevent;
	      this->_lastevent = 0;
	      break;
	    }
	}
    }
}

int		Bomb::PlayerInputComponent::GetSlot()  const
{
  return this->_slot;
}
