//
// KeyboardManager.hh for  in /home/lelabo_m/rendu/cpp_bomberman/GameEngine
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Sun May 25 15:58:38 2014 Marc Le Labourier
// Last update Thu Jun 12 11:16:40 2014 Marc Le Labourier
//

#ifndef KEYBOARDMANAGER_HH
#define KEYBOARDMANAGER_HH

#include <map>
#include "Event.hpp"
#include "GraphicContext.hh"

typedef std::map<int, bool>                 keyMap;
typedef std::map<int, bool>::iterator       keyMap_it;
typedef std::map<int, bool>::const_iterator	keyMap_itConst;

namespace Event
{
  class KeyboardManager
  {
  public:
    KeyboardManager();
    ~KeyboardManager();
    void		setValue(bool);
    void		updateValue(gdl::Input &);
    bool		isUpdated() const;
    keyMap		&getKeyboard();
    void		displayUsedKey() const;

  private:
    keyMap 		_keyMap;
    bool		_update;
  };

  class KeyboardEvent : public InputEvent
  {
  public:
    KeyboardEvent(keyMap& d, size_t subj = KEYBOARD) : InputEvent(subj), data(d)
    {
    }

    virtual Event*		Clone() const
    {
      KeyboardEvent*	k = new KeyboardEvent(data, Subject());
      k->SetScope(this->Scope());
      return (k);
    }

    keyMap&	data;
  };
}

#endif
