//
// GraphicComponent.hh for  in /home/lelabo_m/rendu/cpp_bomberman
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Thu May 29 17:39:54 2014 Marc Le Labourier
// Last update Sun Jun 15 01:45:50 2014 Marc Le Labourier
//

#ifndef GRAPHICCOMPONENT_HH_
# define GRAPHICCOMPONENT_HH_

#include <string>
#include "glm/ext.hpp"
#include "Component.hh"
#include "SysGraphic.hh"

#define DEGTORAD(x) ((x / M_PI) * 180.f)

namespace Bomb
{

  enum MeshType {MODEL, GEOMETRY};

  class MeshComponent;
  struct Animation;
  typedef bool	(*MeshFunction)(MeshComponent*, Graphic::SysGraphic*);

  typedef std::list<Animation*>		AnimationList;

  struct Animation
  {
    Animation(std::string *n, int b, int e) : name(n), begin(b), end(e) {};
    ~Animation() { delete name; };
    std::string		*name;
    int			begin;
    int			end;
  };

  class MeshComponent : public BaseComponent
  {
  public:
    MeshComponent(MeshType, std::string*, std::string*,
		  MeshFunction, MeshFunction, Graphic::SysGraphic*);
    ~MeshComponent();
    void			Start();
    void			OnEvent(Event::Event*);
    void			Update();
    void			Destroy();
    void			dump();
    // Important Method
    void			Draw();
    void			Init();
    glm::mat4			GetPosition();
    void			AddAnime(Animation*);
    void			DelAnime(Animation*);
    AnimationList*		GetAnimes();
    void			SetName(std::string *);
    bool			SetAnime(const std::string&, int, bool);
    bool			SetAnime(int, bool);
    static bool			ApplicAnime(AnimationList*, gdl::Model*);
    bool			ApplicAnime(gdl::Model*);
    // Getter
    std::string*		GetName() const;
    std::string*		GetPath() const;
    MeshType			GetType();
  private:
    MeshType			_type;
    std::list<Animation*>	_anims;
    std::string*		_name;
    std::string*		_path;
    MeshFunction		_initializer;
    MeshFunction		_drawer;
    Graphic::SysGraphic		*_renderer;
    bool			_isdestroy;
    char*			_slastanime;
    int				_ilastanime;
  };

  class AnimComponent;
  typedef bool	(*AnimFunction)(AnimComponent*, Graphic::SysGraphic*, double, double);

  class AnimComponent : public BaseComponent
  {
  public:
    AnimComponent(MeshType, std::string*, std::string*,
		  AnimFunction, AnimFunction, Graphic::SysGraphic*);
    ~AnimComponent();
    void			Destroy();
    void			dump();
    // Important Method
    void			Draw();
    void			Init(double, double);
    void			AddAnime(Animation*);
    void			DelAnime(Animation*);
    AnimationList*		GetAnimes();
    bool			SetAnime(const std::string&, int, bool);
    bool			SetAnime(int, bool);
    static bool			ApplicAnime(AnimationList*, gdl::Model*);
    bool			ApplicAnime(gdl::Model*);
    // Getter / setter
    void			SetPos(double, double);
    std::string*		GetName() const;
    std::string*		GetPath() const;
    MeshType			GetType();
  private:
    Graphic::SysGraphic		*_renderer;
    std::string*		_name;
    std::string*		_path;
    MeshType			_type;
    AnimFunction		_initializer;
    AnimFunction		_drawer;
    std::list<Animation*>	_anims;
    bool			_isdestroy;
    double			_posx;
    double			_posy;
  };
}

#endif /* !GRAPHICCOMPONENT_HH_ */
