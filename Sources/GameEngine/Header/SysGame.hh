/*
** SysGame.hh for Bomberman in /home/lejard_h/rendu/cpp_bomberman/GameEngine
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  mar. mai  20 22:01:18 2014 hadrien lejard
// Last update Sun Jun  8 19:29:53 2014 Marc Le Labourier
*/

#ifndef __SYSGAME_HH__
# define __SYSGAME_HH__

#include <iostream>
#include <map>
#include <list>
#include <fstream>
#include "Sys.hh"
#include "GameObject.hh"
#include "Mutex.hh"
#include "ScopedLock.hh"
#include "Thread.hh"
#include "Factory.hpp"
#include "Settings.hpp"
#include "GraphicContext.hh"

namespace Bomb
{
  class ListObj
  {
  public:
    ListObj();
    ~ListObj();
    ListObj(ListObj  &);

    std::list<IEntity *>  &GetList();
    void	AddObj(IEntity *);
    IEntity	*GetObjById(int id);
    bool	RemoveObjById(int id);
    std::list<IEntity *>::iterator  Begin();
    std::list<IEntity *>::iterator  End();
    IEntity	*front();
    void 	dump(void);

    ListObj &operator=(ListObj &);

  private:
    std::list<IEntity *>			_list;
    Mutex					*_mutex;
  };

  class ObjContainer
  {
  public:
    ObjContainer();
    ~ObjContainer();
    ObjContainer(ObjContainer &);

    std::map<enum GameObjectTag, ListObj *> &GetMapObject();
    ListObj     &GetListObject();

    ObjContainer &operator=(ObjContainer &);
    void	AddObj(IEntity *);
    ListObj	*GetObjByTag(enum GameObjectTag);
    IEntity	*GetObjById(int id);
    IEntity	*GetObjById(int id, enum GameObjectTag);
    void	RemoveObjsByTag(enum GameObjectTag);
    void	RemoveObjById(int id);
    void	RemoveObjById(int id, enum GameObjectTag);
    std::list<IEntity *>::iterator  Begin();
    std::list<IEntity *>::iterator  End();
    void 	dump(void);

  private:
    Mutex					*_mutex;
    std::map<enum GameObjectTag, ListObj *>	_objs;
    ListObj					_list;
  };

  class SysGame : public ISys
  {
  public:
    typedef bool	(*Initializer)();
    SysGame(Graphic::OGLContext*, Initializer, Initializer);
    ~SysGame();

    bool	Init();
    void	Update();
    void	Destroy();

    void	OnEvent(Event::Event *);
    static void	*MainLoop(void *);
    void	Loop();
    static void	*InitContext(void *);
    void	InitObj();
    void	SaveGame();
    void  EventTreatment();
    void  SaveMap(std::string const &);
    
  private:
    Graphic::OGLContext		*_ogl;
    TaskThread			*_gamethread;
    bool			_isdestroy;
    std::list<Event::Event *>	_events;
    Mutex			_mutex;
    Initializer			_init;
    Initializer			_free;
    bool			_isInside;
  };
}

extern Pattern::Factory<Bomb::IEntity, Bomb::GameObjectTag>  *G_EntityFactory;
extern Bomb::ObjContainer                                    *G_ObjectsContainer;

void  DeleteObjectFromMap(int);

#endif
