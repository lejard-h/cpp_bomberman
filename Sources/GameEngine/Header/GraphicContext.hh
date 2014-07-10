//
// GraphicContext.hh for  in /home/lelabo_m/rendu/cpp_bomberman
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Fri May 23 16:31:05 2014 Marc Le Labourier
// Last update Wed Jun 11 21:33:11 2014 Marc Le Labourier
//

#ifndef GRAPHICCONTEXT_HH_
# define GRAPHICCONTEXT_HH_

#pragma once
#include <vector>
#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <Game.hh>
#include <SdlContext.hh>

#include "Mutex.hh"
#include "Game.hh"
#include "SdlContext.hh"
#include "Clock.hh"
#include "Model.hh"
#include "BasicShader.hh"

#define PATH_TO_LIB "Lib/LibGDL/"

namespace Graphic
{
  class OGLContext
  {
  public:
    OGLContext(glm::mat4&, glm::mat4&);
    ~OGLContext();
    bool		Init(int, int);
    bool		Start();
    gdl::SdlContext	*GetContext();
    gdl::Clock		*GetClock();
    gdl::Input		*GetInput();
    gdl::BasicShader	*GetShader();
    glm::mat4		&GetCamProj();
    void		SetCamProj(glm::mat4&);
    glm::mat4		&GetCamTransfo();
    void		SetCamTransfo(glm::mat4&);
    void		CamUpdate();
    void		AskCamUpdate();
    bool		IsInit();
    void		Lock();
    void		Unlock();
    void		Close();
    bool		IsClose();
  private:
    gdl::SdlContext	*_context;
    gdl::Clock		*_clock;
    gdl::Input		*_input;
    gdl::BasicShader	*_shader;
    glm::mat4		&_camprojection;
    glm::mat4		&_camtransformation;
    Mutex		_m;
    int			_height;
    int			_width;
    bool		_isinit;
    bool		_updateCam;
    bool		_isClose;
  };
}

#endif /* !GRAPHICCONTEXT_HH_ */
