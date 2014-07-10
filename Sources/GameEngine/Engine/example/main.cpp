/*
** main.c for  in /home/lelabo_m/rendu/cpp_bomberman/Engine/Event/example
**
** Made by Marc Le Labourier
** Login   <lelabo_m@epitech.net>
**
** Started on  Wed May 21 15:07:17 2014 Marc Le Labourier
// Last update Tue May 27 15:08:06 2014 Marc Le Labourier
*/

#include <iostream>
#include "Engine.hh"
#include "EventDispatcher.hh"
#include "KeyboardManager.hh"
#include "Settings.hpp"
#include <unistd.h>

class Sys : public Event::ISubscriber
{
public:
  Sys() {};
  ~Sys() {}
  void	OnEvent(Event::Event* ev)
  {
    _events.push_back(ev);
  }
  void	DisplayEvent(Bomb::Engine *engine)
  {
    _m.lock();
    std::cout << "list events size = " << _events.size() << std::endl;
    if (!_events.size())
      {
	_m.unlock();
	return ;
      }
    Event::Event	*ev = _events.front();
    Event::InputEvent	*evin = dynamic_cast<Event::InputEvent*>(ev);
    if (evin)
      {
	std::cout << "EVENT KEYBOARD" << std::endl;
	for (keyMap_itConst it = evin->keyboard.begin();
	     it != evin->keyboard.end(); ++it)
	  if ((*it).second == true)
	    {
	      std::cout << "Key " << SDL_GetKeyName((*it).first) << " used" << std::endl;
	      if ((*it).first == SDLK_ESCAPE)
		engine->Stop();
	    }
	std::cout << "==============" << std::endl;
      }
    else
      std::cout << "FAIL TO READ EVENT" << std::endl;
    _events.clear();
    _m.unlock();
  }
private:
  std::list<Event::Event*>	_events;
  Mutex				_m;
};

int	main()
{
  Sys		s;
  glm::mat4 projection;
  glm::mat4 transformation;
  projection = glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 100.0f);
  transformation = glm::lookAt(glm::vec3(0, 10, -30), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
  Graphic::OGLContext   ogl(projection, transformation);
  ogl.Init(100, 80);
  Bomb::Engine	engine(&ogl);
  engine.Init();
  engine.Start();
  G_EvDispatcher->AddSubscriber(Event::INPUT ,&s);
  while (G_GameSettings && G_GameSettings->gameState == Settings::RUNNING)
    {
      s.DisplayEvent(&engine);
      usleep(50000);
    }
}
