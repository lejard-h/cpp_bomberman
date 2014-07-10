/*
** SysGame.cpp for Bomberman in /home/lejard_h/rendu/cpp_bomberman/GameEngine
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  mar. mai  20 22:57:24 2014 hadrien lejard
// Last update Sun Jun 15 14:35:52 2014 Marc Le Labourier
*/

#include <sys/stat.h>
#include <ctime>
#include <iostream>
#include <unistd.h>
#include "Engine.hh"
#include "SysGame.hh"
#include "BombComponent.hh"
#include "ExplodeComponent.hh"
#include "LoaderSettings.hh"
#include "Load.hh"

/*
* class ListObj
*/

Bomb::ListObj::ListObj()
{
  _mutex = new Mutex();
}

Bomb::ListObj::~ListObj()
{
  delete _mutex;
  _list.clear();
}

Bomb::ListObj::ListObj(ListObj &l)
{
  this->_list = l.GetList();
}

Bomb::ListObj  &Bomb::ListObj::operator=(ListObj &l)
{
  this->_list = l.GetList();
  return *this;
}

Bomb::IEntity *Bomb::ListObj::front()
{
  ScopedLock  lock(this->_mutex);

  if (this->_list.empty())
    return 0;
  return this->_list.front();
}

std::list<Bomb::IEntity *>::iterator  Bomb::ListObj::Begin()
{
  ScopedLock  lock(this->_mutex);

  return this->_list.begin();
}

std::list<Bomb::IEntity *>::iterator  Bomb::ListObj::End()
{
  ScopedLock  lock(this->_mutex);

  return this->_list.end();
}

void	Bomb::ListObj::AddObj(IEntity *obj)
{
  ScopedLock	lock(this->_mutex);

  this->_list.push_back(obj);
}

Bomb::IEntity	*Bomb::ListObj::GetObjById(int id)
{
  ScopedLock	lock(this->_mutex);

  std::list<IEntity *>::iterator	it;
  for (it = this->_list.begin(); it != this->_list.end(); ++it)
    {
      if ((*it)->GetId() == id)
	return *it;
    }
  return 0;
}

bool		Bomb::ListObj::RemoveObjById(int id)
{
  ScopedLock	lock(this->_mutex);

  std::list<IEntity *>::iterator	it;
  for (it = this->_list.begin(); it != this->_list.end(); ++it)
    {
      if ((*it)->GetId() == id)
	{
	  this->_list.erase(it);
	  return true;
	}
    }
  return false;
}

void Bomb::ListObj::dump(void)
{
  ScopedLock	lock(this->_mutex);

  std::list<IEntity *>::iterator	it;
  for (it = this->_list.begin(); it != this->_list.end(); ++it)
    {
      (*it)->dump();
      std::cout << std::endl;
    }
}

std::list<Bomb::IEntity *>  &Bomb::ListObj::GetList()
{
  return this->_list;
}

/*
* class ObjContainer
*/

Bomb::ObjContainer::ObjContainer()
{
  _mutex = new Mutex();
}

Bomb::ObjContainer::~ObjContainer()
{
  for (std::map<enum GameObjectTag, ListObj *>::iterator it = this->_objs.begin();
    it != this->_objs.end();
    ++it)
  {
    delete it->second;
  }
  delete _mutex;
}

Bomb::ObjContainer::ObjContainer(ObjContainer &o)
{
  this->_objs = o.GetMapObject();
  this->_list = o.GetListObject();
}

Bomb::ObjContainer  &Bomb::ObjContainer::operator=(ObjContainer &o)
{
  this->_objs = o.GetMapObject();
  this->_list = o.GetListObject();
  return *this;
}

std::map<enum Bomb::GameObjectTag, Bomb::ListObj *> &Bomb::ObjContainer::GetMapObject()
{
  return this->_objs;
}

Bomb::ListObj &Bomb::ObjContainer::GetListObject()
{
  return this->_list;
}

std::list<Bomb::IEntity *>::iterator  Bomb::ObjContainer::Begin()
{
  return this->_list.Begin();
}

std::list<Bomb::IEntity *>::iterator  Bomb::ObjContainer::End()
{
  return this->_list.End();
}

void	Bomb::ObjContainer::AddObj(IEntity *obj)
{
  if (obj)
    {
      ScopedLock	lock(this->_mutex);
      std::map<enum GameObjectTag, ListObj *>::iterator	it;

      if ((it = this->_objs.find(obj->GetTag())) != this->_objs.end())
       it->second->AddObj(obj);
     else
     {
       ListObj	*list = new ListObj();
       list->AddObj(obj);
       this->_objs[obj->GetTag()] = list;
     }
      this->_list.AddObj(obj);
    }
}

Bomb::ListObj	*Bomb::ObjContainer::GetObjByTag(enum GameObjectTag tag)
{
  ScopedLock	lock(this->_mutex);
  std::map<enum GameObjectTag, ListObj *>::iterator	it;

  if ((it = this->_objs.find(tag)) != this->_objs.end())
    return it->second;
  return 0;
}

Bomb::IEntity	*Bomb::ObjContainer::GetObjById(int id)
{
  ScopedLock	lock(this->_mutex);
  std::map<enum GameObjectTag, ListObj *>::iterator	it_map;

  for (it_map = this->_objs.begin(); it_map != this->_objs.end(); ++it_map)
  {
    Bomb::IEntity *obj = it_map->second->GetObjById(id);
    if (obj)
     return obj;
 }
 return 0;
}

Bomb::IEntity	*Bomb::ObjContainer::GetObjById(int id, enum GameObjectTag tag)
{
  ScopedLock	lock(this->_mutex);
  std::map<enum GameObjectTag, ListObj *>::iterator	it;

  if ((it = this->_objs.find(tag)) != this->_objs.end())
    return it->second->GetObjById(id);
  return 0;
}

void			Bomb::ObjContainer::RemoveObjsByTag(enum GameObjectTag tag)
{
  ScopedLock	lock(this->_mutex);

  std::map<enum GameObjectTag, ListObj *>::iterator	it;
  std::list<IEntity *>::iterator it_list;
  if ((it = this->_objs.find(tag)) != this->_objs.end())
  {
     for (it_list = it->second->Begin(); it_list != it->second->End(); ++it_list)
      this->_list.RemoveObjById((*it_list)->GetId());
    this->_objs.erase(it);
  }
}

void		Bomb::ObjContainer::RemoveObjById(int id)
{
  ScopedLock	lock(this->_mutex);
  std::map<enum GameObjectTag, ListObj *>::iterator it_map;

  for (it_map = this->_objs.begin(); it_map != this->_objs.end(); ++it_map)
    {
      if (it_map->second->RemoveObjById(id) && this->_list.RemoveObjById(id))
       return ;
    }
}

void		Bomb::ObjContainer::RemoveObjById(int id, enum GameObjectTag tag)
{
  ScopedLock	lock(this->_mutex);

  std::map<enum GameObjectTag, ListObj *>::iterator	it;
  if ((it = this->_objs.find(tag)) != this->_objs.end())
    it->second->RemoveObjById(id);
  this->_list.RemoveObjById(id);
}

void	Bomb::ObjContainer::dump(void)
{
  ScopedLock	lock(this->_mutex);
  std::map<enum GameObjectTag, ListObj *>::iterator	it;

  for (it = this->_objs.begin(); it != this->_objs.end(); ++it)
    {
      std::cout << "Tag : ";
      std::cout << it->first << std::endl;
      it->second->dump();
      std::cout << std::endl;
    }
}

/*
* class SysGame
*/

Pattern::Factory<Bomb::IEntity, Bomb::GameObjectTag>  *G_EntityFactory = 0;
Bomb::ObjContainer  *G_ObjectsContainer = 0;

Bomb::SysGame::SysGame(Graphic::OGLContext* ogl, Initializer init, Initializer destroy)
  : _ogl(ogl), _init(init), _free(destroy)
{
  _isdestroy = true;
  _isInside = false;
  _gamethread = 0;
}

Bomb::SysGame::~SysGame()
{
  if (!_isdestroy)
    Destroy();
}

bool	Bomb::SysGame::Init()
{
  _isdestroy = false;
  if (_init)
    (_init)();
  if (!G_EntityFactory)
    G_EntityFactory = new Pattern::Factory<IEntity, GameObjectTag>();
  if (!G_ObjectsContainer)
    G_ObjectsContainer = new ObjContainer();
  G_EvDispatcher->AddSubscriber(Event::GAME, this);
  _gamethread = new TaskThread(&SysGame::InitContext, &SysGame::MainLoop, this);
  _gamethread->run();
  return true;
}

void    *Bomb::SysGame::InitContext(void *param)
{
  SysGame*     obj = reinterpret_cast<SysGame*>(param);

  obj->InitObj();
  return 0;
}

void	Bomb::SysGame::InitObj()
{
  _mutex.lock();
  _ogl->Lock();
  try
  {
    for (std::list<IEntity *>::iterator it = G_ObjectsContainer->Begin();
     it != G_ObjectsContainer->End(); ++it)
      (*it)->Start();
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
    G_EvDispatcher->SendEvent(new Event::EngineEvent(Event::ENGINEERROR), Event::COMMON);
    G_GameSettings->gameState = Settings::END;
  }
  _ogl->Unlock();
  _mutex.unlock();
}

void	Bomb::SysGame::OnEvent(Event::Event *ev)
{
  bool	islock = false;
  if (!_isInside)
  {

    _mutex.lock();
    islock = true;
  }
  this->_events.push_back(ev);
  if (islock)
  {
    _mutex.unlock();
    islock = true;
  }
}

void  DeleteObjectFromMap(int id)
{
   if (G_ObjectsContainer)
  {
    Bomb::ListObj           *list_world = G_ObjectsContainer->GetObjByTag(Bomb::World_o);
    Bomb::IEntity           *Object = G_ObjectsContainer->GetObjById(id);
    Bomb::PositionComponent *pos = 0;
    Bomb::World             *world = 0;
    Bomb::MapComponent      *map = 0;

    if (Object)
      pos = static_cast<Bomb::PositionComponent *>(Object->GetComponent(Bomb::Position_c));
    if (list_world)
      world = static_cast<Bomb::World *>(list_world->front());
    if (world)
      map = static_cast<Bomb::MapComponent *>(world->GetComponent(Bomb::Map_c));

    if (map && pos)
      {
	map->RemoveEntity(pos->GetPosition(Bomb::PositionComponent::X),
			  pos->GetPosition(Bomb::PositionComponent::Y), id);
	G_EvDispatcher->SendEvent(new Event::GraphicEvent(Object, Graphic::MESHDEL), Event::COMMON);
      }
  }
}

void  DeleteObject(int id)
{
  if (G_ObjectsContainer)
  {
    DeleteObjectFromMap(id);
    G_ObjectsContainer->RemoveObjById(id);
  }
}

void  Bomb::SysGame::EventTreatment()
{
  while (this->_events.size())
    {
      Event::Event *ev = this->_events.front();
      if (ev && ev->Scope() == Event::GAME)
	{
	  if (ev->Subject() == Event::DESTROY)
	    {
	      Event::DestroyEvent  *destruction = static_cast<Event::DestroyEvent *>(ev);
	      IEntity  *entity = G_ObjectsContainer->GetObjById(destruction->id);

	      if (entity)
		{
		  DeleteObject(entity->GetId());
		}
	    }
	}
      delete ev;
      this->_events.pop_front();
    }
}

void	Bomb::SysGame::Update()
{
  _mutex.lock();
  _isInside = true;
  if (G_GameSettings->gameState == Settings::RUNNING)
  {
    for (std::list<IEntity *>::iterator it = G_ObjectsContainer->Begin();
      it != G_ObjectsContainer->End(); ++it)
      (*it)->Update();
  }
  this->EventTreatment();
  if (G_GameSettings && G_GameSettings->SaveState)
  {
    G_GameSettings->SaveState = false;
    this->SaveGame();
  }
  _isInside = false;
  _mutex.unlock();
}

void    *Bomb::SysGame::MainLoop(void *param)
{
  SysGame*     obj = reinterpret_cast<SysGame*>(param);

  obj->Loop();
  return 0;
}

void	Bomb::SysGame::Destroy()
{
  if (_isdestroy)
    return ;
  _isdestroy = true;
  if (_free)
    (_free)();
  if (_gamethread)
    _gamethread->stop();
  if (G_ObjectsContainer)
    {
      delete G_ObjectsContainer;
      G_ObjectsContainer = 0;
    }
  if (G_EntityFactory)
    {
      delete G_EntityFactory;
      G_EntityFactory = 0;
    }
  _events.clear();
  delete _gamethread;
}

void	Bomb::SysGame::Loop()
{
  try
  {
    while (G_GameSettings && G_GameSettings->gameState != Settings::END)
    {
      this->Update();
    }
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }
}

void  Bomb::SysGame::SaveMap(std::string const &name)
{
  if (G_ObjectsContainer)
  {
    ListObj *list_world = G_ObjectsContainer->GetObjByTag(World_o);
    if (list_world)
    {
      IEntity *world = list_world->front();
      if (world)
      {
        MapComponent  *map = static_cast<MapComponent *>(world->GetComponent(Map_c));
        if (map)
         map->Save(name);
      }
    }
  }
}

static void serialize_game(std::string const &save)
{
 system(("touch " + save + ".save").c_str());
 std::ofstream ofile((save + ".save").c_str());
 boost::archive::binary_oarchive oTextArchive(ofile);

 oTextArchive.register_type(static_cast<Settings::GameContext *>(0));
 oTextArchive.register_type(static_cast<Settings::Map *>(0));
 oTextArchive.register_type(static_cast<Settings::Player *>(0));
 oTextArchive.register_type(static_cast<Settings::InputConf *>(0));
 oTextArchive.register_type(static_cast<Settings::SavePlayer *>(0));

 oTextArchive << G_GameSettings;
}

static void updateMenu(std::string const &save)
{
  system("touch ./Saves/Saves.txt");
  Load  *menuLoad = Load::Instance();

  if (menuLoad)
  {
    std::fstream    fs;
    std::vector<std::string>  saves = menuLoad->Parse();

    fs.open("./Saves/Saves.txt");
    fs << save << std::endl;
    int idx = 2;
    size_t  i = 0;
    while (idx <= 10)
    {
      if (i < saves.size())
        fs << saves[i] << std::endl;
      else
        fs << "Empty" << std::endl;
      ++i;
      ++idx;
    }
    fs.close();

  }
}

void	Bomb::SysGame::SaveGame()
{
  ListObj                         *MenuList = G_ObjectsContainer->GetObjByTag(Menu_o);
  std::list<IEntity *>::iterator  obj = MenuList->Begin();
  G_EvDispatcher->SendEvent(new Event::GraphicEvent(*obj, Graphic::MESHDEL), Event::SYS);
  std::stringstream save;
  time_t  rawtime;
  struct tm *time_info;

  time(&rawtime);
  time_info = localtime(&rawtime);
  save << (1900 + time_info->tm_year) << "." << (1 + time_info->tm_mon)
       << "." << time_info->tm_mday << ".";
  save << time_info->tm_hour << ":" << time_info->tm_min << ":" << time_info->tm_sec;

  try
  {
    mkdir("Saves", 0744);
    G_EvDispatcher->SendEvent(new Event::GraphicEvent(0, Graphic::SCREENSHOT), Event::SYS);

    enum Settings::MapType  saveType = G_GameSettings->map.mapType;

    G_GameSettings->map.mapType = Settings::MAP;
    this->SaveMap("./Saves/" + save.str() + ".map");
    G_GameSettings->map.mapPath = "./Saves/" + save.str() + ".map";
    G_GameSettings->Save = "./Saves/" + save.str() + ".save";

    G_GameSettings->SavePlayers.clear();
    if (G_ObjectsContainer)
    {
      ListObj *list_players = G_ObjectsContainer->GetObjByTag(Player_o);
      if (list_players)
      {
        for (std::list<IEntity *>::iterator it = list_players->Begin();
          it != list_players->End();
          ++it)
        {
          Settings::SavePlayer *p = new Settings::SavePlayer();
          p->SetPlayer(*it);
          G_GameSettings->SavePlayers.push_back(p);
        }
      }
    }

    serialize_game("./Saves/" + save.str());
    updateMenu(save.str());
    G_GameSettings->map.mapType = saveType;


  }
  catch (std::exception &e)
  {
    std::cout << "SysGame : Fail to Save Game, " << e.what() << std::endl;
  }

 }
