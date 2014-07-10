//
// AudioComponent.hh for  in /home/lelabo_m/rendu/cpp_bomberman/Bomberman
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Thu May 29 16:53:06 2014 Marc Le Labourier
// Last update Sat Jun 14 10:36:16 2014 Marc Le Labourier
//

#ifndef AUDIOCOMPONENT_HH_
# define AUDIOCOMPONENT_HH_

#include "Settings.hpp"
#include "Component.hh"

namespace Bomb
{
  class AudioComponent : public BaseComponent
  {
  public:
    AudioComponent(int);
    ~AudioComponent();
    void	Start();
    void	OnEvent(Event::Event *);
    void	Update();
    void	Destroy();
    void	dump() const;
    // Important Method
    void	AddSound(std::string* path, std::string* name);
    bool	PlaySound(std::string* name, double volume = 0.5);
  private:
    std::map<std::string *, std::string *>	_sound;
    bool					_isdestroy;
    std::list<Event::Event*>			_events;
    Mutex					_mutex;
    bool					_isInside;
    int						_chan;
  };
}

#endif /* !AUDIOCOMPONENT_HH_ */
