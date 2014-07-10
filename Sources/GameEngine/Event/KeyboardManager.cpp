//
// KeyboardManager.cpp for  in /home/lelabo_m/rendu/cpp_bomberman/GameEngine
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Sun May 25 15:57:48 2014 Marc Le Labourier
// Last update Tue Jun 10 22:05:43 2014 Marc Le Labourier
//

#include <iostream>
#include "KeyboardManager.hh"

Event::KeyboardManager::KeyboardManager()
  {
    this->_update = false;
    this->_keyMap[SDL_QUIT]			= false;
    this->_keyMap[SDLK_BACKSPACE] 		= false;
    this->_keyMap[SDLK_TAB] 			= false;
    this->_keyMap[SDLK_CLEAR] 			= false;
    this->_keyMap[SDLK_RETURN] 			= false;
    this->_keyMap[SDLK_PAUSE] 			= false;
    this->_keyMap[SDLK_ESCAPE] 			= false;
    this->_keyMap[SDLK_SPACE] 			= false;
    this->_keyMap[SDLK_EXCLAIM]			= false;
    this->_keyMap[SDLK_QUOTEDBL] 		= false;
    this->_keyMap[SDLK_HASH] 			= false;
    this->_keyMap[SDLK_DOLLAR] 			= false;
    this->_keyMap[SDLK_AMPERSAND] 		= false;
    this->_keyMap[SDLK_QUOTE] 			= false;
    this->_keyMap[SDLK_LEFTPAREN] 		= false;
    this->_keyMap[SDLK_RIGHTPAREN] 		= false;
    this->_keyMap[SDLK_ASTERISK] 		= false;
    this->_keyMap[SDLK_PLUS] 			= false;
    this->_keyMap[SDLK_COMMA] 			= false;
    this->_keyMap[SDLK_MINUS] 			= false;
    this->_keyMap[SDLK_PERIOD] 			= false;
    this->_keyMap[SDLK_SLASH] 			= false;
    this->_keyMap[SDLK_0]			= false;
    this->_keyMap[SDLK_1]			= false;
    this->_keyMap[SDLK_2]			= false;
    this->_keyMap[SDLK_3]			= false;
    this->_keyMap[SDLK_4]			= false;
    this->_keyMap[SDLK_5]			= false;
    this->_keyMap[SDLK_6]			= false;
    this->_keyMap[SDLK_7]			= false;
    this->_keyMap[SDLK_8]			= false;
    this->_keyMap[SDLK_9]			= false;
    this->_keyMap[SDLK_COLON] 			= false;
    this->_keyMap[SDLK_SEMICOLON] 		= false;
    this->_keyMap[SDLK_LESS] 			= false;
    this->_keyMap[SDLK_EQUALS] 			= false;
    this->_keyMap[SDLK_GREATER]	 		= false;
    this->_keyMap[SDLK_QUESTION]	 	= false;
    this->_keyMap[SDLK_AT]			= false;
    this->_keyMap[SDLK_LEFTBRACKET]	 	= false;
    this->_keyMap[SDLK_BACKSLASH]		= false;
    this->_keyMap[SDLK_RIGHTBRACKET]	 	= false;
    this->_keyMap[SDLK_CARET] 			= false;
    this->_keyMap[SDLK_UNDERSCORE] 		= false;
    this->_keyMap[SDLK_BACKQUOTE] 		= false;
    this->_keyMap[SDLK_a]			= false;
    this->_keyMap[SDLK_b]			= false;
    this->_keyMap[SDLK_c]			= false;
    this->_keyMap[SDLK_d]			= false;
    this->_keyMap[SDLK_e]			= false;
    this->_keyMap[SDLK_f]			= false;
    this->_keyMap[SDLK_g]			= false;
    this->_keyMap[SDLK_h]			= false;
    this->_keyMap[SDLK_i]			= false;
    this->_keyMap[SDLK_j]			= false;
    this->_keyMap[SDLK_k]			= false;
    this->_keyMap[SDLK_l]			= false;
    this->_keyMap[SDLK_m]			= false;
    this->_keyMap[SDLK_n]			= false;
    this->_keyMap[SDLK_o]			= false;
    this->_keyMap[SDLK_p]			= false;
    this->_keyMap[SDLK_q]			= false;
    this->_keyMap[SDLK_r]			= false;
    this->_keyMap[SDLK_s]			= false;
    this->_keyMap[SDLK_t]			= false;
    this->_keyMap[SDLK_u]			= false;
    this->_keyMap[SDLK_v]			= false;
    this->_keyMap[SDLK_w]			= false;
    this->_keyMap[SDLK_x]			= false;
    this->_keyMap[SDLK_y]			= false;
    this->_keyMap[SDLK_z]			= false;
    this->_keyMap[SDLK_DELETE] 			= false;
    this->_keyMap[SDLK_KP_0] 			= false;
    this->_keyMap[SDLK_KP_1] 			= false;
    this->_keyMap[SDLK_KP_2] 			= false;
    this->_keyMap[SDLK_KP_3] 			= false;
    this->_keyMap[SDLK_KP_4] 			= false;
    this->_keyMap[SDLK_KP_5]		 	= false;
    this->_keyMap[SDLK_KP_6] 			= false;
    this->_keyMap[SDLK_KP_7] 			= false;
    this->_keyMap[SDLK_KP_8] 			= false;
    this->_keyMap[SDLK_KP_9] 			= false;
    this->_keyMap[SDLK_KP_PERIOD] 		= false;
    this->_keyMap[SDLK_KP_DIVIDE] 		= false;
    this->_keyMap[SDLK_KP_MULTIPLY]	 	= false;
    this->_keyMap[SDLK_KP_MINUS]	 	= false;
    this->_keyMap[SDLK_KP_PLUS]	 		= false;
    this->_keyMap[SDLK_KP_ENTER]	 	= false;
    this->_keyMap[SDLK_KP_EQUALS] 		= false;
    this->_keyMap[SDLK_UP]			= false;
    this->_keyMap[SDLK_DOWN] 			= false;
    this->_keyMap[SDLK_RIGHT] 			= false;
    this->_keyMap[SDLK_LEFT] 			= false;
    this->_keyMap[SDLK_INSERT] 			= false;
    this->_keyMap[SDLK_HOME] 			= false;
    this->_keyMap[SDLK_END] 			= false;
    this->_keyMap[SDLK_PAGEUP] 			= false;
    this->_keyMap[SDLK_PAGEDOWN]	 	= false;
    this->_keyMap[SDLK_F1]			= false;
    this->_keyMap[SDLK_F2]			= false;
    this->_keyMap[SDLK_F3]			= false;
    this->_keyMap[SDLK_F4]			= false;
    this->_keyMap[SDLK_F5]			= false;
    this->_keyMap[SDLK_F6]			= false;
    this->_keyMap[SDLK_F7]			= false;
    this->_keyMap[SDLK_F8]			= false;
    this->_keyMap[SDLK_F9]			= false;
    this->_keyMap[SDLK_F10] 			= false;
    this->_keyMap[SDLK_F11] 			= false;
    this->_keyMap[SDLK_F12] 			= false;
    this->_keyMap[SDLK_F13] 			= false;
    this->_keyMap[SDLK_F14] 			= false;
    this->_keyMap[SDLK_F15] 			= false;
    this->_keyMap[SDLK_NUMLOCKCLEAR] 		= false;
    this->_keyMap[SDLK_CAPSLOCK]	 	= false;
    this->_keyMap[SDLK_SCROLLLOCK]		= false;
    this->_keyMap[SDLK_RSHIFT] 			= false;
    this->_keyMap[SDLK_LSHIFT]			= false;
    this->_keyMap[SDLK_RCTRL] 			= false;
    this->_keyMap[SDLK_LCTRL] 			= false;
    this->_keyMap[SDLK_RALT] 			= false;
    this->_keyMap[SDLK_LALT] 			= false;
    this->_keyMap[SDLK_MODE] 			= false;
    this->_keyMap[SDLK_HELP] 			= false;
    this->_keyMap[SDLK_PRINTSCREEN]		= false;
    this->_keyMap[SDLK_SYSREQ] 			= false;
    this->_keyMap[SDLK_MENU] 			= false;
    this->_keyMap[SDLK_POWER] 			= false;
  }

Event::KeyboardManager::~KeyboardManager()
{
}

void 			Event::KeyboardManager::setValue(bool value)
{
  keyMap_it 	ite;

  for (ite = this->_keyMap.begin() ; ite != this->_keyMap.end() ; ++ite)
    (*ite).second = value;
}

void 			Event::KeyboardManager::updateValue(gdl::Input &_input)
{
  keyMap_it 	ite;
  bool        used;

  this->_update = false;
  for (ite = this->_keyMap.begin() ; ite != this->_keyMap.end() ; ++ite)
    {
      used = (_input.getInput((*ite).first)) ? (true) : (false);
      if (used != (*ite).second)
	this->_update = true;
      (*ite).second = used;
    }
}

void 			Event::KeyboardManager::displayUsedKey() const
{
  keyMap_itConst ite;

  for (ite = this->_keyMap.begin() ; ite != this->_keyMap.end() ; ++ite)
    if ((*ite).second == true)
      std::cout << "Key " << SDL_GetKeyName((*ite).first) << " used" << std::endl;
}

keyMap		&Event::KeyboardManager::getKeyboard()
{
  return (this->_keyMap);
}

bool            Event::KeyboardManager::isUpdated() const
{
  return (this->_update);
}
