//
// GraphicContext.cpp for  in /home/lelabo_m/rendu/cpp_bomberman
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Fri May 23 14:55:05 2014 Marc Le Labourier
// Last update Sat Jun 14 10:13:52 2014 Marc Le Labourier
//

#include <string>
#include "GraphicContext.hh"

Graphic::OGLContext::~OGLContext()
{
  Close();
}

bool	Graphic::OGLContext::IsClose()
{
  return _isClose;
}

void	Graphic::OGLContext::Close()
{
  if (_isClose)
    return ;
  if (_context && _shader && _input && _clock)
    {
      delete _shader;
      delete _input;
      delete _clock;
      if (_isClose == false)
	_context->stop();
      delete _context;
    }
  _isClose = true;
  _context = 0;
  _shader = 0;
  _input = 0;
  _clock = 0;
}

Graphic::OGLContext::OGLContext(glm::mat4& proj, glm::mat4& transfo)
  : _camprojection(proj), _camtransformation(transfo)
{
  _updateCam = false;
  _isinit = false;
  _context = 0;
  _shader = 0;
  _input = 0;
  _clock = 0;
  _isClose = true;
}

bool	Graphic::OGLContext::Init(int x, int y)
{
  _height = x;
  _width = y;
  _shader = 0;
  _input = 0;
  _clock = 0;
  return true;
}

bool			Graphic::OGLContext::Start()
{
  _context = new gdl::SdlContext();
  _isClose = false;
  if (!_context->start(_height, _width, "My bomberman!", SDL_INIT_VIDEO | SDL_INIT_JOYSTICK,
  		       SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN))
  // if (!_context->start(_height, _width, "My bomberman!", SDL_INIT_VIDEO,
  // 		       SDL_WINDOW_OPENGL/* | SDL_WINDOW_FULLSCREEN */))
    {
      std::cerr << "can not open a window" << std::endl;
      return false;
    }
  _shader = new gdl::BasicShader();
  _input = new gdl::Input();
  _clock = new gdl::Clock();
  glEnable(GL_DEPTH_TEST);
  std::string	path(PATH_TO_LIB);
  if (_shader->load(std::string(path + "shaders/basic.fp"), GL_FRAGMENT_SHADER) == false
      || _shader->load(std::string(path + "shaders/basic.vp"), GL_VERTEX_SHADER) == false
      || _shader->build() == false)
    {
      std::cerr << "can not load shader" << std::endl;
      return false;
    }
  AskCamUpdate();
  CamUpdate();
  _context->updateClock(*_clock);
  _context->updateInputs(*_input);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _context->flush();
  _isinit = true;
  return true;
}

gdl::SdlContext*	Graphic::OGLContext::GetContext()
{
  return _context;
}

gdl::Clock*	Graphic::OGLContext::GetClock()
{
  return _clock;
}

gdl::Input*	Graphic::OGLContext::GetInput()
{
  return _input;
}

gdl::BasicShader*	Graphic::OGLContext::GetShader()
{
  return _shader;
}

glm::mat4&		Graphic::OGLContext::GetCamProj()
{
  return _camprojection;
}

glm::mat4&		Graphic::OGLContext::GetCamTransfo()
{
  return _camtransformation;
}

void			Graphic::OGLContext::SetCamProj(glm::mat4& newproj)
{
  _camprojection = newproj;
}

void			Graphic::OGLContext::SetCamTransfo(glm::mat4& newtransfo)
{
  _camtransformation = newtransfo;
}

void			Graphic::OGLContext::AskCamUpdate()
{
  _updateCam = true;
}

void			Graphic::OGLContext::CamUpdate()
{
  if (_updateCam)
    {
      _updateCam = false;
      _shader->bind();
      _shader->setUniform("view", _camtransformation);
      _shader->setUniform("projection", _camprojection);
    }
}

void			Graphic::OGLContext::Lock()
{
  _m.lock();
}

void			Graphic::OGLContext::Unlock()
{
  _m.unlock();
}

bool			Graphic::OGLContext::IsInit()
{
  return _isinit;
}
