//
// GraphicComponent.cpp for  in /home/lelabo_m/rendu/cpp_bomberman
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Sun Jun  1 00:27:53 2014 Marc Le Labourier
// Last update Sun Jun 15 01:43:24 2014 Marc Le Labourier
//

#include <iostream>
#include "Settings.hpp"
#include "GraphicComponent.hh"
#include "PositionComponent.hh"

// Mesh Component
Bomb::MeshComponent::MeshComponent(Bomb::MeshType type, std::string *name, std::string *path,
				   MeshFunction init, MeshFunction draw,
				   Graphic::SysGraphic* sys)
{
  _type = type;
  _name = name;
  _path = path;
  _initializer = init;
  _drawer = draw;
  _renderer = sys;
  _isdestroy = false;
  _slastanime = 0;
  _ilastanime = -1;
  this->ctor(Render_c);
}

Bomb::MeshComponent::~MeshComponent()
{
  if (!_isdestroy)
    Destroy();
}

void	Bomb::MeshComponent::Destroy()
{
  _isdestroy = true;
  delete _path;
  _anims.clear();
}

void	Bomb::MeshComponent::Start()
{
}

void	Bomb::MeshComponent::Init()
{
  (_initializer)(this, _renderer);
}

void	Bomb::MeshComponent::OnEvent(Event::Event *)
{
}

void	Bomb::MeshComponent::Update()
{
}

void	Bomb::MeshComponent::dump()
{
  std::cout << "GraphicComponent : " << std::endl;
  std::cout << "Type : " << ((_type == MODEL) ? ("Model") : ("GEOMETRY")) << std::endl;
  std::cout << "Path : " << _path << std::endl;
  std::cout << "Animation :" << std::endl;
  for (AnimationList::iterator it = _anims.begin(); it != _anims.end(); ++it)
    std::cout << " - anime name : " << (*it)->name << " first frame : " << (*it)->begin
	      << " last frame : " << (*it)->end << std::endl;
}

void	Bomb::MeshComponent::Draw()
{
  (_drawer)(this, _renderer);
}

void	Bomb::MeshComponent::AddAnime(Bomb::Animation* a)
{
  _anims.push_back(a);
}

void	Bomb::MeshComponent::DelAnime(Bomb::Animation* a)
{
  _anims.remove(a);
}

Bomb::AnimationList*	Bomb::MeshComponent::GetAnimes()
{
  return &_anims;
}

bool		Bomb::MeshComponent::SetAnime(const std::string& anim, int mode, bool loop)
{
  if (anim.c_str() == _slastanime)
    return true;
  _slastanime = const_cast<char *>(anim.c_str());
  if (_type != MODEL)
    return false;
  Graphic::ModelMap	*modelmap = _renderer->GetModels();
  gdl::Model	*model = (*modelmap)[_name->c_str()];
  if (mode)
    model->setCurrentAnim(anim, loop);
  else
    model->setCurrentSubAnim(anim, loop);
  return true;
}

bool		Bomb::MeshComponent::SetAnime(int anim, bool loop)
{
  if (anim == _ilastanime)
    return true;
  _ilastanime = anim;
  if (_type != MODEL)
    return false;
  Graphic::ModelMap	*modelmap = _renderer->GetModels();
  gdl::Model	*model = (*modelmap)[_name->c_str()];
  if (model)
    model->setCurrentAnim(anim, loop);
  return true;
}

bool		Bomb::MeshComponent::ApplicAnime(gdl::Model* ourmodel)
{
  for (AnimationList::iterator it = _anims.begin(); it != _anims.end(); ++it)
    {
      if (ourmodel->createSubAnim(0, *(*it)->name, (*it)->begin, (*it)->end))
	return false;
    }
  return true;
}

bool		Bomb::MeshComponent::ApplicAnime(Bomb::AnimationList* anims, gdl::Model* ourmodel)
{
  for (AnimationList::iterator it = anims->begin(); it != anims->end(); ++it)
    {
      if (ourmodel->createSubAnim(0, *(*it)->name, (*it)->begin, (*it)->end))
	return false;
    }
  return true;
}

glm::mat4	Bomb::MeshComponent::GetPosition()
{
  glm::mat4	transfo(1);

  Bomb::IComponent*		component = (this->GetParent())->GetComponent(Bomb::Position_c);
  Bomb::PositionComponent*	position = dynamic_cast<Bomb::PositionComponent*>(component);

  if (position)
    {
      if (G_GameSettings)
	{
	  glm::vec3	vecpos(position->GetPosition(PositionComponent::X)
			       - (G_GameSettings->map.x / 2) - 0.5,
			       0.0, position->GetPosition(PositionComponent::Y)
			       - (G_GameSettings->map.y / 2) - 0.5);
	  transfo = glm::translate(transfo, vecpos);
	  transfo = glm::rotate(transfo, -90 + (glm::mediump_float)position->GetRotation(),
				glm::vec3(0, -1, 0));
	}
      else
	{
	  glm::vec3	vecpos(position->GetPosition(PositionComponent::X),
			       0.0, position->GetPosition(PositionComponent::Y));
	  transfo = glm::translate(transfo, vecpos);
	  transfo = glm::rotate(transfo, -90 + (glm::mediump_float)position->GetRotation(),
				glm::vec3(0, -1, 0));
	}
    }
  return transfo;
}

std::string*	Bomb::MeshComponent::GetName() const
{
  return _name;
}

std::string*	Bomb::MeshComponent::GetPath() const
{
  return _path;
}

Bomb::MeshType	Bomb::MeshComponent::GetType()
{
  return _type;
}

void		Bomb::MeshComponent::SetName(std::string* n)
{
  _name = n;
}

// Animation Component
Bomb::AnimComponent::AnimComponent(Bomb::MeshType type, std::string *name, std::string *path,
				   AnimFunction init, AnimFunction draw,
				   Graphic::SysGraphic* sys)
  : _renderer(sys), _name(name), _path(path), _type(type), _initializer(init), _drawer(draw)
{
  this->ctor(Anim_c);
  _isdestroy = false;
}

Bomb::AnimComponent::~AnimComponent()
{
  if (!_isdestroy)
    Destroy();
}

void	Bomb::AnimComponent::Destroy()
{
  _isdestroy = true;
  delete _path;
  _anims.clear();
}

void	Bomb::AnimComponent::Init(double x, double y)
{
  _posx = x;
  _posy = y;
  (_initializer)(this, _renderer, x, y);
}

void	Bomb::AnimComponent::dump()
{
  std::cout << "AnimComponent : " << std::endl;
  std::cout << "Type : " << ((_type == MODEL) ? ("Model") : ("GEOMETRY")) << std::endl;
  std::cout << "Path : " << _path << std::endl;
  std::cout << "Animation :" << std::endl;
  for (AnimationList::iterator it = _anims.begin(); it != _anims.end(); ++it)
    std::cout << " - anime name : " << (*it)->name << " first frame : " << (*it)->begin
	      << " last frame : " << (*it)->end << std::endl;
}

void	Bomb::AnimComponent::Draw()
{
  (_drawer)(this, _renderer, _posx, _posy);
}

void	Bomb::AnimComponent::AddAnime(Bomb::Animation* a)
{
  _anims.push_back(a);
}

void	Bomb::AnimComponent::DelAnime(Bomb::Animation* a)
{
  _anims.remove(a);
}

Bomb::AnimationList*	Bomb::AnimComponent::GetAnimes()
{
  return &_anims;
}

bool		Bomb::AnimComponent::SetAnime(const std::string& anim, int mode, bool loop)
{
  if (_type != MODEL)
    return false;
  Graphic::ModelMap	*modelmap = _renderer->GetModels();
  gdl::Model	*model = (*modelmap)[_name->c_str()];
  if (mode)
    model->setCurrentAnim(anim, loop);
  else
    model->setCurrentSubAnim(anim, loop);
  return true;
}

bool		Bomb::AnimComponent::SetAnime(int anim, bool loop)
{
  if (_type != MODEL)
    return false;
  Graphic::ModelMap	*modelmap = _renderer->GetModels();
  gdl::Model	*model = (*modelmap)[_name->c_str()];
  model->setCurrentAnim(anim, loop);
  return true;
}

bool		Bomb::AnimComponent::ApplicAnime(gdl::Model* ourmodel)
{
  for (AnimationList::iterator it = _anims.begin(); it != _anims.end(); ++it)
    {
      if (ourmodel->createSubAnim(0, *(*it)->name, (*it)->begin, (*it)->end))
	return false;
    }
  return true;
}

bool		Bomb::AnimComponent::ApplicAnime(Bomb::AnimationList* anims, gdl::Model* ourmodel)
{
  for (AnimationList::iterator it = anims->begin(); it != anims->end(); ++it)
    {
      if (ourmodel->createSubAnim(0, *(*it)->name, (*it)->begin, (*it)->end))
	return false;
    }
  return true;
}

std::string*	Bomb::AnimComponent::GetName() const
{
  return _name;
}

std::string*	Bomb::AnimComponent::GetPath() const
{
  return _path;
}

Bomb::MeshType	Bomb::AnimComponent::GetType()
{
  return _type;
}

void		Bomb::AnimComponent::SetPos(double x, double y)
{
  _posx = x;
  _posy = y;
}
