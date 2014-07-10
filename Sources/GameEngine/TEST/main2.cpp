/*
** main2.cpp for test in /home/thomas_1/Desktop/Projets/Bomberman/cpp_bomberman/GameEngine
**
** Made by Pierre-Yves THOMAS
** Login   <thomas_1@epitech.net>
**
** Started on  Thu May  29 19:21:42 2014 Pierre-Yves THOMAS
// Last update Wed Jun  4 21:39:05 2014 Marc Le Labourier
*/

#include <iostream>
#include <unistd.h>
#include "Engine.hh"
#include "EventDispatcher.hh"
#include "KeyboardManager.hh"
#include "Settings.hpp"
#include "SysAudio.hh"

std::string*	path1 = new std::string("../Audio/sounds/ALARM10.wav");
std::string*	path2 = new std::string("../Audio/sounds/ALARM11.wav");
std::string*	test1 = new std::string("test1");
std::string*	test2 = new std::string("test2");

class Sys : public Event::ISubscriber
{
public:
  Sys() {};
  ~Sys() {}
  void  OnEvent(Event::Event* ev)
  {
    _m.lock();
    _events.push_front(ev);
    _m.unlock();
  }
  void  DisplayEvent(Bomb::Engine *engine)
  {
    _m.lock();
    std::cout << "list events size = " << _events.size() << std::endl;
    if (!_events.size())
      {
        _m.unlock();
        return ;
      }
    Event::Event        *ev = _events.front();
    Event::InputEvent   *evin = dynamic_cast<Event::InputEvent*>(ev);
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
    if (evin->keyboard[SDLK_UP])
      G_EvDispatcher->SendEvent(new Event::AudioEvent(path1, test1, 0.5, Audio::PLAY), Event::COMMON);
    if (!evin->keyboard[SDLK_UP])
      G_EvDispatcher->SendEvent(new Event::AudioEvent(path1, test1, 0.5, Audio::PAUSE), Event::COMMON);
    if (evin->keyboard[SDLK_DOWN])
      G_EvDispatcher->SendEvent(new Event::AudioEvent(path2, test2, 0.5, Audio::PLAY), Event::COMMON);
    if (!evin->keyboard[SDLK_DOWN])
      G_EvDispatcher->SendEvent(new Event::AudioEvent(path2, test2, 0.5, Audio::PAUSE), Event::COMMON);
    _events.clear();
    _m.unlock();
  }
private:
  std::list<Event::Event*>      _events;
  Mutex                         _m;
};

bool	initializer()
{
  return true;
}

int 	main()
 {
   Sys		s;
   glm::mat4 projection;
   glm::mat4 transformation;
   projection = glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 100.0f);
   transformation = glm::lookAt(glm::vec3(0, 10, -30), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
   Graphic::OGLContext   ogl(projection, transformation);
   ogl.Init(1920, 1080);
   Bomb::Engine	eng(&ogl, initializer);
   eng.Init();
   G_EvDispatcher->SendEvent(new Event::AudioEvent(path1, test1, 0.5, Audio::LOAD), Event::COMMON);
   G_EvDispatcher->SendEvent(new Event::AudioEvent(path2, test2, 0.5, Audio::LOAD), Event::COMMON);
   eng.Start();
   eng.Stop();
   return (0);
 }
