//
// Renderer.cpp for  in /home/lelabo_m/rendu/cpp_bomberman/GameEngine
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Sat May 31 11:34:28 2014 Marc Le Labourier
// Last update Sun Jun 15 18:07:23 2014 Marc Le Labourier
//

#include <sstream>
#include <unistd.h>
#include "ScreenShot.hh"
#include "Component.hh"
#include "Settings.hpp"
#include "SysGraphic.hh"
#include "GraphicComponent.hh"
#include "Exception.hh"

Graphic::SysGraphic*	G_Renderer = 0;

Graphic::SysGraphic::SysGraphic(OGLContext *ogl) : _ogl(ogl)
{
  _isdestroy = true;
  _isinit = false;
  _mapGraphicFunc[MESHINIT] = &SysGraphic::InitMeshRenderer;
  _mapGraphicFunc[MESHADD] = &SysGraphic::AddMeshRenderer;
  _mapGraphicFunc[MESHDEL] = &SysGraphic::DelMeshRenderer;
  _mapGraphicFunc[ANIMADD] = &SysGraphic::AddAnimRenderer;
  _mapGraphicFunc[ANIMINIT] = &SysGraphic::InitAnimRenderer;
  _mapGraphicFunc[SCREENSHOT] = &SysGraphic::ScreenShot;
}

Graphic::SysGraphic::~SysGraphic()
{
  if (!_isdestroy)
    Destroy();
}

void	Graphic::SysGraphic::Destroy()
{
  if (_isdestroy)
    return ;
  _isdestroy = true;
  Update();
  if (_graphicthread)
    _graphicthread->stop();
  if (_isinit)
    {
      _objs.clear();
      for (GeometryMap::iterator it = _geometrys.begin();
      	   it != _geometrys.end(); ++it)
      	delete it->second;
      _geometrys.clear();
      for (TextureMap::iterator it = _textures.begin();
      	   it != _textures.end(); ++it)
      	delete it->second;
      _textures.clear();
      for (ModelMap::iterator it = _models.begin();
	   it != _models.end(); ++it)
	delete it->second;
      _models.clear();
      _events.clear();
    }
  delete _graphicthread;
}

bool	Graphic::SysGraphic::Init()
{
  if (!G_EvDispatcher)
    return false;
  _isdestroy = false;
  G_EvDispatcher->AddSubscriber(Event::RENDER, this);
  _graphicthread = new TaskThread(&SysGraphic::InitThread, &SysGraphic::Mainloop, this);
  _graphicthread->run();
  return true;
}

void	*Graphic::SysGraphic::InitThread(void *param)
{
  SysGraphic*     obj = reinterpret_cast<SysGraphic*>(param);

  obj->InitContext();
  return 0;
}

void	Graphic::SysGraphic::InitContext()
{
  _ogl->Lock();
  if (!_ogl->Start())
    {
      if (G_EvDispatcher)
	G_EvDispatcher->SendEvent(new Event::EngineEvent(Event::ENGINEERROR), Event::ABS);
    }
  else
    _isinit = true;
  _ogl->Unlock();
}

void	Graphic::SysGraphic::Update()
{
  _graphicthread->wait();
  _graphicthread->update();
}

void	*Graphic::SysGraphic::Mainloop(void *param)
{
  SysGraphic*     obj = reinterpret_cast<SysGraphic*>(param);

  obj->Loop();
  return 0;
}

void	Graphic::SysGraphic::Loop()
{
  if (!_isinit)
    return ;
  _mutex.lock();
  if (_isdestroy)
    {
      _ogl->Lock();
      _ogl->Close();
      usleep(50000);
      _ogl->Unlock();
      return ;
    }
  if (!(G_GameSettings && G_GameSettings->gameState != Settings::END))
    {
      _mutex.unlock();
      return ;
    }
  _ogl->Lock();
  TreatEvent();
  _ogl->CamUpdate();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  gdl::BasicShader*	shader = _ogl->GetShader();
  shader->bind();
  gdl::SdlContext*	context = _ogl->GetContext();
  context->updateInputs(*_ogl->GetInput());
  context->updateClock(*_ogl->GetClock());
  gdl::Clock*	clock = _ogl->GetClock();
  UpdateModelTime(clock->getElapsed());
 // std::cout << "-> START DRAWING" << std::endl;
  for (std::list<Bomb::IEntity*>::iterator it = _objs.begin();
       it != _objs.end(); ++it)
    {
      Bomb::IComponent*		graphicComponent = (*it)->GetComponent(Bomb::Render_c);
      if (graphicComponent)
	{
	  Bomb::MeshComponent*	drawer = static_cast<Bomb::MeshComponent*>(graphicComponent);
	  if (drawer)
	    drawer->Draw();
	}
    }
  if (_anims.empty() == false)
    {
      for (std::vector<Event::AnimeEvent*>::iterator it = _anims.begin();
	   it != _anims.end(); )
	{
	  Bomb::IEntity*	obj = (*it)->obj;
	  if (!obj)
	    break;
	  Bomb::IComponent*		graphicComponent = obj->GetComponent(Bomb::Anim_c);
	  if (graphicComponent)
	    {
	      Bomb::AnimComponent*	drawer = static_cast<Bomb::AnimComponent*>(graphicComponent);
	      if (drawer)
		{
		  drawer->SetPos((*it)->posx, (*it)->posy);
		  drawer->Draw();
		  (*it)->life--;
		}
	      if ((*it)->life == 0)
	      	it = _anims.erase(it);
	      else
		++it;
	    }
	}
    }
  context->flush();
  _ogl->Unlock();
  _mutex.unlock();
  usleep(5000);
}

void	Graphic::SysGraphic::OnEvent(Event::Event *ev)
{
  _mutex.lock();
  if (ev)
    _events.push_back(ev);
  _mutex.unlock();
}

void	Graphic::SysGraphic::TreatEvent()
{
  while (_events.size())
    {
      Event::Event*	ev = _events.front();
      Event::GraphicEvent*	gev = dynamic_cast<Event::GraphicEvent*>(ev);
      if (gev)
	{
	  GraphicFunc		value = (GraphicFunc)(gev->Subject());
	  funcSysRenderer	f = _mapGraphicFunc[value];
	  if (f)
	    (this->*f)(gev);
	}
      _events.pop_front();
      delete ev;
    }
}

bool	Graphic::SysGraphic::InitAnimRenderer(Event::GraphicEvent* ev)
{
  if (!ev->obj)
    return false;
  Event::AnimeEvent*	aev = static_cast<Event::AnimeEvent*>(ev);
  if (!aev)
    return false;
  Bomb::IComponent*		graphicComponent = aev->obj->GetComponent(Bomb::Anim_c);
  if (graphicComponent)
    {
      Bomb::AnimComponent*	drawer = dynamic_cast<Bomb::AnimComponent*>(graphicComponent);
      if (drawer)
	drawer->Init(aev->posx, aev->posy);
    }
  return true;
}

bool	Graphic::SysGraphic::AddAnimRenderer(Event::GraphicEvent* ev)
{
  if (!ev)
    return false;
  Event::AnimeEvent*	aev = static_cast<Event::AnimeEvent*>(ev->Clone());
  if (!aev)
    return false;
  _anims.push_back(aev);
  return true;
}

bool	Graphic::SysGraphic::InitMeshRenderer(Event::GraphicEvent* ev)
{
  if (!ev->obj)
    return false;
  Bomb::IComponent*		graphicComponent = ev->obj->GetComponent(Bomb::Render_c);
  if (graphicComponent)
    {
      Bomb::MeshComponent*	drawer = dynamic_cast<Bomb::MeshComponent*>(graphicComponent);
      if (drawer)
	drawer->Init();
    }
  return true;
}

bool	Graphic::SysGraphic::AddMeshRenderer(Event::GraphicEvent* ev)
{
  if (!ev)
    return false;
  Bomb::IEntity*	obj = ev->obj;
  if (!obj)
    return false;
  _objs.push_back(obj);
  return true;
}

bool	Graphic::SysGraphic::DelMeshRenderer(Event::GraphicEvent* ev)
{
  if (!ev)
    return false;
  Bomb::IEntity*	obj = ev->obj;
  if (!obj)
    return false;
  unsigned int		size = _objs.size();
  _objs.remove(obj);
  if (_objs.size() != size)
    return true;
  return false;
}

bool	Graphic::SysGraphic::ScreenShot(Event::GraphicEvent*)
{
  std::stringstream	save;
  time_t		rawtime;
  struct tm		*time_info;

  time(&rawtime);
  time_info = localtime(&rawtime);
  save << (1900 + time_info->tm_year) << "." << (1 + time_info->tm_mon)
       << "." << time_info->tm_mday << ".";
  save << time_info->tm_hour << ":" << time_info->tm_min << ":" << time_info->tm_sec;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  gdl::BasicShader*	shader = _ogl->GetShader();
  shader->bind();
  gdl::SdlContext*	context = _ogl->GetContext();
  context->updateInputs(*_ogl->GetInput());
  context->updateClock(*_ogl->GetClock());
  gdl::Clock*	clock = _ogl->GetClock();
  UpdateModelTime(clock->getElapsed());
  for (std::list<Bomb::IEntity*>::iterator it = _objs.begin();
       it != _objs.end(); ++it)
    {
      Bomb::IComponent*		graphicComponent = (*it)->GetComponent(Bomb::Render_c);
      if (graphicComponent)
	{
	  Bomb::MeshComponent*	drawer = static_cast<Bomb::MeshComponent*>(graphicComponent);
	  if (drawer)
	    drawer->Draw();
	}
    }
  std::string		name = "./Saves/" + save.str() + ".tga";
  std::cout << "Screenshot : " << name << " done" << std::endl;
  MyScreenShot		screen(name, WINSIZE_X, WINSIZE_Y);
  screen.TakeScreenShot();
  return true;
}

void		Graphic::SysGraphic::UpdateModelTime(double time)
{
  for (ModelTime::iterator it = _modeltime.begin();
       it != _modeltime.end(); ++it)
    it->second = time;
}

Graphic::OGLContext*	Graphic::SysGraphic::GetContext()
{
  return _ogl;
}

Graphic::ModelMap*		Graphic::SysGraphic::GetModels()
{
  return &_models;
}

Graphic::TextureMap*		Graphic::SysGraphic::GetTextures()
{
  return &_textures;
}

Graphic::GeometryMap*		Graphic::SysGraphic::GetGeometrys()
{
  return &_geometrys;
}

Graphic::ModelTime*		Graphic::SysGraphic::GetModelTime()
{
  return &_modeltime;
}
