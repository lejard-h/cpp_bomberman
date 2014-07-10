//
// SysGraphic.hh for  in /home/lelabo_m/rendu/cpp_bomberman/GameEngine
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Sat May 31 11:02:26 2014 Marc Le Labourier
// Last update Sun Jun 15 12:54:15 2014 Marc Le Labourier
//

#ifndef SYSGRAPHIC_HH_
# define SYSGRAPHIC_HH_

#include <list>
#include <map>
#include <string>
#include "Sys.hh"
#include "Texture.hh"
#include "Model.hh"
#include "Geometry.hh"
#include "Thread.hh"
#include "GraphicContext.hh"
#include "GameObject.hh"

namespace Graphic
{
  enum GraphicFunc {MESHINIT, MESHADD, MESHDEL,
		    ANIMINIT, ANIMADD, PAUSE,
		    SCREENSHOT};

  typedef std::map<std::string, double> ModelTime;
  typedef std::map<std::string, gdl::Model*> ModelMap;
  typedef std::map<std::string, gdl::Texture*> TextureMap;
  typedef std::map<std::string, gdl::Geometry*> GeometryMap;

  class SysGraphic : public Bomb::ISys
  {
  public:
    SysGraphic(OGLContext*);
    ~SysGraphic();
    bool		Init();
    void		Destroy();
    void		Update();
    static void		*Mainloop(void *);
    void		Loop();
    void		TreatEvent();
    void		OnEvent(Event::Event*);
    static void		*InitThread(void *);
    void		InitContext();
    void		UpdateModelTime(double);
    // Getter
    OGLContext*		GetContext();
    ModelTime*		GetModelTime();
    GeometryMap*	GetGeometrys();
    TextureMap*		GetTextures();
    ModelMap*		GetModels();
    // Function
    bool		InitMeshRenderer(Event::GraphicEvent*);
    bool		AddMeshRenderer(Event::GraphicEvent*);
    bool		DelMeshRenderer(Event::GraphicEvent*);
    bool		InitAnimRenderer(Event::GraphicEvent*);
    bool		AddAnimRenderer(Event::GraphicEvent*);
    bool		ScreenShot(Event::GraphicEvent*);
  private:
    TaskThread			*_graphicthread;
    OGLContext			*_ogl;
    bool			_isdestroy;
    Mutex			_mutex;
    std::list<Event::Event*>	_events;
    bool			_isinit;
    // Resources
    typedef bool	(SysGraphic::*funcSysRenderer)(Event::GraphicEvent*);
    std::map<GraphicFunc, funcSysRenderer>	_mapGraphicFunc;
    GeometryMap					_geometrys;
    TextureMap					_textures;
    ModelMap					_models;
    ModelTime					_modeltime;
    std::list<Bomb::IEntity *>			_objs;
    std::vector<Event::AnimeEvent *>		_anims;
  };
}

extern Graphic::SysGraphic*	G_Renderer;

#endif /* !SYSGRAPHIC_HH_ */
