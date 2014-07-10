/*
** MapComponent.cpp for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Bomberman
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  dim. mai  25 16:00:42 2014 hadrien lejard
// Last update Sun Jun 15 21:08:00 2014 Marc Le Labourier
*/

#include <stdlib.h>
#include "Settings.hpp"
#include "MapComponent.hh"
#include "GraphicComponent.hh"
#include "ColliderEvent.hh"
#include "LifeComponent.hh"
#include "BombComponent.hh"
#include "ScoreComponent.hh"


Bomb::MapComponent::MapComponent() : _x(0), _y(0), _fileMap(""), _map(0)
{
  srand(time(0));
  srand(0);

  this->ctor(Map_c);
}

Bomb::MapComponent::MapComponent(size_t size_x, size_t size_y) : _x(size_x + 2), _y(size_y + 2), _fileMap(""), _map(0)
{
  srand(time(0));
  srand(0);

  this->ctor(Map_c);
}

Bomb::MapComponent::MapComponent(std::string const &map) : _x(2), _y(2), _fileMap(map), _map(0)
{
  srand(time(0));
  srand(0);
  this->ctor(Map_c);
}

void	Bomb::MapComponent::dump() const
{

  std::cout << "MapComponent" << std::endl;
  std::cout << "x " << this->_x << " y " << this->_y << std::endl;
  std::vector<std::vector<IEntity *>*>::const_iterator it = this->_map->begin();

  for (size_t y = 0; y < this->_y; ++y)
    {
      std::cout << "[";
      for (size_t x = 0; x < this->_x; ++x)
	{
	  for (std::vector<IEntity *>::iterator it_list = (*it)->begin();
	       it_list != (*it)->end();
	       ++it_list)
	    {
	      std::cout << (*it_list)->GetTag();
	    }
	  if ((*it)->begin() == (*it)->end())
	    std::cout << " ";
	  if (x + 1 < this->_x)
	    std::cout << ",";
	  it++;
	}
      std::cout << "]" << std::endl;
    }
}

void	Bomb::MapComponent::CreateMap()
{
  this->_map	= new std::vector<std::vector<IEntity *>*>(this->_x * this->_y);

  for (size_t i = 0; i < this->_x * this->_y; ++i)
    (*this->_map)[i] = new std::vector<IEntity *>();
  this->DelimitMap();
}

void	Bomb::MapComponent::ParseMap(std::iostream &file)
{
  std::vector<std::string> 	tmp;
  std::vector<std::string> 	tmp2;
  std::string			line;
  ListObj				*players = G_ObjectsContainer->GetObjByTag(Player_o);
  std::list<IEntity *>::iterator	it_player;

  while (std::getline(file, line))
    tmp.push_back(line);

  this->_y += tmp.size();
  if (tmp.size() > 0)
    {
      std::istringstream iss(tmp[0]);
      std::string	token;
      size_t x = 0;
      while (!iss.eof())
	{
	  std::getline(iss, token, ',');
	  ++x;
	}
      this->_x += x;
    }
  else
    throw ComponentException("MapComponent : No Map in the file.", 0);
  this->CreateMap();

  if (players)
    it_player = players->Begin();

  size_t y = 1;
  for (std::vector<std::string>::iterator it = tmp.begin();
       it != tmp.end() && y < this->_y - 1;
       ++it)
    {
      size_t	x = 1;
      std::istringstream iss(*it);
      std::string	token;
      while(!iss.eof() && x < this->_x - 1)
	{
	  getline(iss, token, ',');
	  int nb;
	  std::istringstream(token) >> nb;

	  GameObjectTag tag = static_cast<GameObjectTag>(nb);
	  if (tag != Player_o)
	    {
	      IEntity	*entity = G_EntityFactory->Create(tag);
	      if (entity && entity->HasComponent(Position_c))
		{
		  PositionComponent *pos
		    = static_cast<PositionComponent *>(entity->GetComponent(Position_c));
		  pos->SetPosition(x + 0.5, y + 0.5);
		  pos->SetSpawn(x + 0.5, y + 0.5);
		  G_ObjectsContainer->AddObj(entity);
		  this->AddEntity(entity, x, y);
		}
	    }
	  else if (tag == Player_o && players && it_player != players->End())
	    {
	      if ((*it_player)->HasComponent(Position_c))
		{
		  PositionComponent *pos
		    = static_cast<PositionComponent *>((*it_player)->GetComponent(Position_c));
		  pos->SetPosition(x + 0.5, y + 0.5);
		  pos->SetSpawn(x + 0.5, y + 0.5);
		  this->AddEntity(*it_player, x, y);
		}
	      ++it_player;
	    }
	  ++x;
	}
      ++y;
    }
  for (it_player = it_player ;it_player != players->End(); ++it_player)
    this->AddEntity(*it_player);
  G_GameSettings->map.x = GetWidth();
  G_GameSettings->map.y = GetHeight();
}

void	Bomb::MapComponent::Start()
{
  if (G_GameSettings->map.mapType == Settings::RANDOM && this->_fileMap.empty())
    {
      this->RandomMap();
      this->InitPlayers();
    }
  else
    {
      std::stringstream	fs(this->Load(this->_fileMap));
      this->ParseMap(fs);

      if (G_GameSettings && G_GameSettings->launchtype == Settings::LOADED)
	this->LoadPlayer(G_GameSettings->SavePlayers);
    }
}

void	Bomb::MapComponent::LoadPlayer(std::vector<Settings::SavePlayer *> &savePlayers)
{
  size_t		idx = 0;
  ListObj		*players = G_ObjectsContainer->GetObjByTag(Player_o);

  if (players)
    {
      std::cout << "LoadPlayer" << std::endl;
      for (std::list<IEntity *>::iterator	it_player = players->Begin();
	   it_player != players->End();
	   ++it_player)
	{
	  PositionComponent	*pos
	    = static_cast<PositionComponent *>((*it_player)->GetComponent(Position_c));
	  LifeComponent	*life
	    = static_cast<LifeComponent *>((*it_player)->GetComponent(Life_c));
	  ScoreComponent	*score
	    = static_cast<ScoreComponent *>((*it_player)->GetComponent(Score_c));
	  BombComponent	*bomb = static_cast<BombComponent *>((*it_player)->GetComponent(Bomb_c));
	  if (pos && life && score && bomb)
	    {
	      pos->SetPosition(savePlayers[idx]->posX, savePlayers[idx]->posY);
	      pos->SetRotation(savePlayers[idx]->rotation);
	      life->SetLife(savePlayers[idx]->life);
	      life->SetMaxLife(savePlayers[idx]->maxLife);
	      score->SetScore(savePlayers[idx]->score);
	      bomb->SetNbBomb(Normal, savePlayers[idx]->nbBombs);
	      bomb->SetSizeBomb(Normal, savePlayers[idx]->sizeBomb);
	      this->AddEntity(*it_player, pos->GetPosition(PositionComponent::X),
			      pos->GetPosition(PositionComponent::Y));
	    }
	  ++idx;
	}
    }
}

void	Bomb::MapComponent::Destroy()
{
  if (this->_map)
    {
      for (size_t i = 0; i < this->_map->size(); ++i)
			delete (*this->_map)[i];
      delete this->_map;
    }
}

void	Bomb::MapComponent::InitPlayers()
{
  ListObj	*players = G_ObjectsContainer->GetObjByTag(Player_o);

  if (players)
    {
      for (std::list<IEntity *>::iterator	it_player = players->Begin();
	   it_player != players->End();
	   ++it_player)
	{
	  this->AddEntity(*it_player);
	}
    }
}

void	Bomb::MapComponent::DelimitMap()
{
  for (size_t y = 0; y < this->_y; ++y)
    {
      for (size_t x = 0; x < this->_x; ++x)
	{
	  if (y == 0 || y == this->_y - 1 ||
	      x == 0 || x == this->_x - 1)
	    {
	      IEntity	*box = G_EntityFactory->Create(UndestructibleBox_o);
	      if (box && box->HasComponent(Position_c))
		{
		  PositionComponent *pos
		    = static_cast<PositionComponent *>(box->GetComponent(Position_c));
		  pos->SetPosition(x + 0.5, y + 0.5);
		  pos->SetSpawn(x + 0.5, y + 0.5);
		  G_ObjectsContainer->AddObj(box);
		  this->AddEntity(box, x, y);
		}
	    }
	}
    }
}

bool	Bomb::MapComponent::IsEnoughSpace(size_t x, size_t y)
{
  int	check[4][2];

  check[0][0] = x + 1;
  check[0][1] = y;
  check[1][0] = x - 1;
  check[1][1] = y;
  check[2][0] = x;
  check[2][1] = y + 1;
  check[3][0] = x;
  check[3][1] = y - 1;

  if (!this->ValidCell(x, y) || !this->EmptyCell(x, y))
    return false;
  for (int i = 0; i < 4; ++i)
    {
      if (!this->ValidCell(check[i][0], check[i][1])
	  || !this->EmptyCell(check[i][0], check[i][1]))
	return false;
    }
  return true;
}

void	Bomb::MapComponent::RandomMap()
{
  int	nbUndestructible = ((this->_x - 2) * (this->_y - 2)) / 6;
  int	check[4][2];

  this->CreateMap();
  while (nbUndestructible >= 0)
    {
      int	x = rand() % (this->_x - 4) + 2;
      int	y = rand() % (this->_y - 4) + 2;
      if (this->EmptyCell(x, y))
	{
	  IEntity	*box = G_EntityFactory->Create(UndestructibleBox_o);
	  if (box && box->HasComponent(Position_c))
	    {
	      PositionComponent *pos = static_cast<PositionComponent *>(box->GetComponent(Position_c));
	      pos->SetPosition(x + 0.5, y + 0.5);
	      pos->SetSpawn(x + 0.5, y + 0.5);
	      G_ObjectsContainer->AddObj(box);
	      this->AddEntity(box, x, y);
	    }

	  check[0][0] = x + 1;
	  check[0][1] = y;
	  check[1][0] = x - 1;
	  check[1][1] = y;
	  check[2][0] = x;
	  check[2][1] = y + 1;
	  check[3][0] = x;
	  check[3][1] = y - 1;

	  for (int i = 0; i < 4; ++i)
	    {
	      if (rand() % 10 > 4 && this->ValidCell(check[i][0], check[i][1])
		  && this->EmptyCell(check[i][0], check[i][1]))
		{
		  box = G_EntityFactory->Create(DestructibleBox_o);
		  if (box && box->HasComponent(Position_c))
		    {
		      PositionComponent *pos
			= static_cast<PositionComponent *>(box->GetComponent(Position_c));
		      pos->SetPosition(check[i][0] + 0.5, check[i][1] + 0.5);
		      pos->SetSpawn(check[i][0] + 0.5, check[i][1] + 0.5);
		      G_ObjectsContainer->AddObj(box);
		      this->AddEntity(box, check[i][0], check[i][1]);
		    }
		}
	    }
	  nbUndestructible--;
	}
    }
}

void	Bomb::MapComponent::AddEntity(IEntity *entity)
{
  size_t	x = rand() % this->_x;
  size_t	y = rand() % this->_y;
  int	nbTry = 100;

  while (!this->IsEnoughSpace(x, y) && nbTry > 0)
    {
      x = rand() % this->_x;
      y = rand() % this->_y;
      --nbTry;
    }
    if (nbTry <= 0)
    {
    	bool	isOk = false;
    	for (y = 0; y < this->_y && !isOk; ++y)
    	{
    		for (x = 0; x < this->_x && !isOk; ++x)
    		{
    			if (this->EmptyCell(x, y))
    			{
    				isOk = true;
    				break;
    			}
    		}
    		if (isOk)
    			break;
    	}
    }
    if (y == this->_y && x == this->_x)
      throw ComponentException("MapComponent : No Places for Players.", 0);
    if (this->EmptyCell(x, y))
      {
    	this->AddEntity(entity, x, y);
    	if (entity->HasComponent(Position_c))
	  {
	    PositionComponent *pos = static_cast<PositionComponent *>(entity->GetComponent(Position_c));
	    pos->SetPosition(x + 0.5, y + 0.5);
	    pos->SetSpawn(x + 0.5, y + 0.5);
	  }
    }
}

void	Bomb::MapComponent::AddEntity(IEntity *entity, size_t x, size_t y)
{
  if (this->ValidCell(x, y))
    {
      (*this->_map)[y * this->_x + x]->push_back(entity);
    }
}

void	Bomb::MapComponent::RemoveEntity(size_t x, size_t y, int id)
{
  std::vector<IEntity *>	*tmp = (*this->_map)[y * this->_x + x];

  if (id == -1)
    return;
  for (std::vector<IEntity *>::iterator it = tmp->begin();
       it != tmp->end();
       ++it)
    {
      if ((*it)->GetId() == id)
	{
	  tmp->erase(it);
	  break;
	  return ;
	}
    }
}

void	Bomb::MapComponent::Update()
{
  for (size_t posX = 0; posX < this->_x; ++posX)
    {
      for (size_t posY = 0; posY < this->_y; ++posY)
	{
	  for (std::vector<IEntity *>::iterator it = (*this->_map)[posY * this->_x + posX]->begin();
	       it != (*this->_map)[posY * this->_x + posX]->end();)
	    {
	      PositionComponent *pos = static_cast<PositionComponent *>((*it)->GetComponent(Position_c));
	      if (pos)
		{
		  size_t	y = pos->GetPosition(PositionComponent::Y);
		  size_t	x = pos->GetPosition(PositionComponent::X);

		  if (x != posX || y != posY)
		    {
		      this->UpdateEntity(*it, posX, posY);
		    }
		  else
		    ++it;
		}
	    }
	}
    }
}

void	Bomb::MapComponent::UpdateEntity(IEntity *entity, size_t realX, size_t realY)
{
  PositionComponent *pos = static_cast<PositionComponent *>(entity->GetComponent(Position_c));

  if (pos)
    {
      size_t	posX = pos->GetPosition(PositionComponent::X);
      size_t	posY = pos->GetPosition(PositionComponent::Y);

      this->RemoveEntity(realX, realY, entity->GetId());

      if (this->ValidCell(posX, posY))
	{
	  (*this->_map)[posY * this->_x + posX]->push_back(entity);
	}
    }
}

bool	Bomb::MapComponent::ValidCell(size_t x, size_t y) const
{
  if ((int) x < 0 || (int) y < 0 || x >= this->_x || y >= this->_y)
    {
      return false;
    }
  return true;
}

bool	Bomb::MapComponent::EmptyCell(size_t x, size_t y) const
{
  if (!ValidCell(x, y))
    return false;
  return (*this->_map)[y * this->_x + x]->empty();
}

bool	Bomb::MapComponent::IsOnCell(size_t x, size_t y, int id) const
{
  if (!this->ValidCell(x, y))
    return false;
  std::vector<IEntity *>	*tmp = (*this->_map)[y * this->_x + x];

  for (std::vector<IEntity *>::iterator it = tmp->begin();
       it != tmp->end();
       ++it)
    {
      if ((*it)->GetId() == id)
	return true;
    }
  return false;
}

bool	Bomb::MapComponent::IsTypeOnCell(size_t x, size_t y, enum GameObjectTag tag) const
{
  if (!this->ValidCell(x, y))
    return false;
  std::vector<IEntity *>	*tmp = (*this->_map)[y * this->_x + x];

  for (std::vector<IEntity *>::iterator it = tmp->begin();
       it != tmp->end();
       ++it)
    {
      if ((*it)->GetTag() == tag)
	return true;
    }
  return false;
}

bool	Bomb::MapComponent::Collider(IEntity *entity, double x, double y) const
{
  PositionComponent	*pos;
  PhysicComponent		*physic;
  PositionComponent	*posObject = static_cast<PositionComponent *>(entity->GetComponent(Position_c));
  PhysicComponent		*physicObject = static_cast<PhysicComponent *>(entity->GetComponent(Physics_c));

  double	posobjX = x - physicObject->GetHitbox();
  double	posobjY = y - physicObject->GetHitbox();
  double	realPosX = posObject->GetPosition(PositionComponent::X) - physicObject->GetHitbox();
  double	realPosY = posObject->GetPosition(PositionComponent::Y) - physicObject->GetHitbox();

  if (G_ObjectsContainer)
  {
  	for (std::list<IEntity *>::iterator	it = G_ObjectsContainer->Begin();
  		it != G_ObjectsContainer->End();
  		++it)
  	{
  		if ((*it)->GetId() != entity->GetId() && (*it)->HasComponent(Physics_c) && (*it)->HasComponent(Position_c))
  		{
  			physic = static_cast<PhysicComponent *>((*it)->GetComponent(Physics_c));
  			pos = static_cast<PositionComponent *>((*it)->GetComponent(Position_c));


  			double	posX = pos->GetPosition(PositionComponent::X) - physic->GetHitbox();
  			double	posY = pos->GetPosition(PositionComponent::Y) - physic->GetHitbox();

  			if (((posX >= realPosX + 2 * physicObject->GetHitbox())
  				|| (posX + 2 * physic->GetHitbox() <= realPosX)
  				|| (posY >= realPosY + 2 *physicObject->GetHitbox())
  				|| (posY + 2 * physic->GetHitbox() <=  realPosY)))
  			{
  				if (!((posX >= posobjX + 2 * physicObject->GetHitbox())
  					|| (posX + 2 * physic->GetHitbox() <= posobjX)
  					|| (posY >= posobjY + 2 *physicObject->GetHitbox())
  					|| (posY + 2 * physic->GetHitbox() <=  posobjY)))
  				{
  					if ((*it)->GetTag() == BonusSizeBomb_o || (*it)->GetTag() == BonusAddBomb_o
  						|| (*it)->GetTag() == BonusSpeed_o)
  						G_EvDispatcher->SendEvent(new Event::CollideEvent((*it)->GetId(), entity->GetId(), posX, posY), Event::COMMON);
  					else
  						return true;
  				}
  			}
  		}
  	}
  }
  return false;
}

std::vector<Bomb::IEntity *>	*Bomb::MapComponent::OnCell(size_t x, size_t y)
{
  if (this->ValidCell(x, y))
    return (*this->_map)[y * this->_x + x];
  return 0;
}

std::string		Bomb::MapComponent::Load(std::string const &fileName)
{
	std::string	stringMap = "";

	try
	{
		std::ifstream ofile(fileName.c_str());
		boost::archive::binary_iarchive iTextArchive(ofile);
		iTextArchive >> stringMap;
	}
	catch (std::exception &e)
	{
		throw ComponentException("MapComponent : " + std::string(e.what()), 0);
	}
	return stringMap;
}

void			Bomb::MapComponent::Save(std::string const &fileName)
{
	try
	{
		std::string	stringMap = "";

		if (this->_map)
		{
			for (size_t y = 1; y < this->_y - 1; ++y)
			{
				for (size_t x = 1; x < this->_x - 1; ++x)
				{
					char	c = '0';
					for (std::vector<IEntity *>::iterator it = (*this->_map)[y * this->_x + x]->begin();
						it != (*this->_map)[y * this->_x + x]->end();
						++it)
					{
						if ((*it)->GetTag() == DestructibleBox_o || (*it)->GetTag() == UndestructibleBox_o)
						{
							c = (*it)->GetTag() + '0';
							break;
						}
					}
					stringMap += c;
					if (x + 1 < this->_x)
						stringMap += ',';
				}
				stringMap += '\n';
			}

		}

		system(("touch " + fileName).c_str());
		std::fstream ofile(fileName.c_str());
		boost::archive::binary_oarchive iTextArchive(ofile);
		iTextArchive << stringMap;
	}
	catch (std::exception &e)
	{
		std::cerr << "MapComponent : Fail To SaveMap, " << e.what() << std::endl;
	}
}

size_t	Bomb::MapComponent::GetWidth() const
{
	return this->_x;
}


size_t	Bomb::MapComponent::GetHeight() const
{
	return this->_y;
}
