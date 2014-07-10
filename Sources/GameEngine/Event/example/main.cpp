/*
** main.c for  in /home/lelabo_m/rendu/cpp_bomberman/Engine/Event/example
**
** Made by Marc Le Labourier
** Login   <lelabo_m@epitech.net>
**
** Started on  Wed May 21 15:07:17 2014 Marc Le Labourier
// Last update Sun May 25 16:24:26 2014 Marc Le Labourier
*/

#include <iostream>
#include "EventDispatcher.hh"
#include "KeyboardManager.hh"
#include <unistd.h>

class Plop : public Event::ISubscriber
{
public:
  Plop(int id) {_id = id;};
  ~Plop() {};
  void	OnEvent(Event::Event *e)
  {
    std::cout << "Plop id = " << _id << std::endl;
    Event::DebugEvent(*e);
  }
private:
  int	_id;
};

void	test_event_creation()
{
  Event::DebugEvent(*new Event::GameEvent());
  Event::DebugEvent(*new Event::AudioEvent());
  Event::DebugEvent(*new Event::UIEvent());
}

void	test_event_dispatcher()
{
  Event::EventDispatcher	ed;
  Plop				*p1 = new Plop(1);
  Plop				*p2 = new Plop(2);

  std::cout << "START THE TEST" << std::endl;
  ed.AddSubscriber(Event::RENDER, p1);
  ed.AddSubscriber(Event::RENDER, p2);
  ed.AddSubscriber(Event::UI, p1);
  ed.AddSubscriber(Event::AUDIO, p2);
  ed.SendEvent(new Event::AudioEvent(), Event::COMMON);
  ed.SendEvent(new Event::GraphicEvent(5), Event::COMMON);
  ed.SendEvent(new Event::AudioEvent(4), Event::COMMON);
  ed.SendEvent(new Event::UIEvent(10), Event::COMMON);
  ed.DelSubscriber(Event::RENDER, p1);
  ed.SendEvent(new Event::GraphicEvent(15), Event::COMMON);
  ed.DelSubscriber(Event::RENDER, p2);
  ed.SendEvent(new Event::GraphicEvent(25), Event::COMMON);
  ed.AddSubscriber(Event::RENDER, p2);
  ed.SendEvent(new Event::AudioEvent(42), Event::COMMON);
  ed.SwitchChannelState(Event::COMMON);
  ed.SendEvent(new Event::AudioEvent(42), Event::COMMON);
  ed.SendEvent(new Event::AudioEvent(42), Event::ABS);
  std::cout << "END THE TEST" << std::endl;
}

int	main()
{
  glm::mat4 projection;
  glm::mat4 transformation;
  projection = glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 100.0f);
  transformation = glm::lookAt(glm::vec3(0, 10, -30), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
  Graphic::OGLContext   ogl(projection, transformation);
  ogl.Init(100, 80);
  gdl::SdlContext		*sdl = ogl.GetContext();
  gdl::Input			*in = ogl.GetInput();
  Event::KeyboardManager	KM;
  bool				end;
  keyMap			km;

  end = false;
  while (!end)
    {
      KM.setValue(false);
      sdl->updateInputs(*in);
      KM.updateValue(*in);
      std::cout << "======= KEYBOARD ========" << std::endl;
      KM.displayUsedKey();
      std::cout << "=========================" << std::endl;
      km = KM.getKeyboard();
      if (km[SDLK_ESCAPE])
	end = true;
      usleep(100000);
    }
}
