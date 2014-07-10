/*
** Image.cpp for Bomber in /home/thomas_1/Desktop/Projets/Bomberman/cpp_bomberman/Bomberman
**
** Made by Pierre-Yves THOMAS
** Login   <thomas_1@epitech.net>
**
** Started on  Sat Jun  07 17:43:14 2014 Pierre-Yves THOMAS
// Last update Sun Jun 15 14:20:36 2014 Marc Le Labourier
*/

#include <sstream>
#include "InputComponent.hh"
#include "GraphicComponent.hh"
#include "AudioComponent.hh"
#include "SysAudio.hh"
#include "Menu.hh"

bool	MenuMeshInit(Bomb::MeshComponent*, Graphic::SysGraphic*)
{
  return true;
}

bool    MenuMeshDraw(Bomb::MeshComponent* mesh, Graphic::SysGraphic*)
{
  Bomb::IEntity*	parent = mesh->GetParent();

  Bomb::Menu*	menu = dynamic_cast<Bomb::Menu*>(parent);
  if (!menu)
    return false;
  Bomb::Sprite*	sp = menu->GetSprite();
  Bomb::SpriteState*	sps = menu->GetSpriteState();

  for (Bomb::SpriteState::iterator it = sps->begin(); it != sps->end(); ++it)
    {
      if (it->second == true)
	{
	  Bomb::Image*	obj = (*sp)[it->first];
	  if (!obj)
	    continue;
	  Bomb::IComponent*         graphicComponent = obj->GetComponent(Bomb::Render_c);
	  if (!graphicComponent)
	    continue;
	  Bomb::MeshComponent*  drawer = static_cast<Bomb::MeshComponent*>(graphicComponent);
	  if (drawer)
	    drawer->Draw();
	}
    }
  return true;
}


Bomb::Menu::Menu(int posX, int posY, int width, int height, std::string name, std::string path)
{
  _state = 0;

  _ressources["pause_1"] = ASSETPATH"Menu/pausefont.tga";
  _ressources["pause_21"] = ASSETPATH"Menu/pausecontinue_b.tga";
  _ressources["pause_22"] = ASSETPATH"Menu/pausecontinue.tga";
  _ressources["pause_31"] = ASSETPATH"Menu/pausesave_b.tga";
  _ressources["pause_32"] = ASSETPATH"Menu/pausesave.tga";
  _ressources["pause_41"] = ASSETPATH"Menu/pausequit_b.tga";
  _ressources["pause_42"] = ASSETPATH"Menu/pausequit.tga";

  _posX["pause_1"] = width;
  _posX["pause_21"] = width / 2;
  _posX["pause_22"] = width / 2;
  _posX["pause_31"] = width / 2;
  _posX["pause_32"] = width / 2;
  _posX["pause_41"] = width / 2;
  _posX["pause_42"] = width / 2;

  _posY["pause_1"] = height;
  _posY["pause_21"] = (height / 10);
  _posY["pause_22"] = (height / 10);
  _posY["pause_31"] = (height / 10);
  _posY["pause_32"] = (height / 10);
  _posY["pause_41"] = (height / 10);
  _posY["pause_42"] = (height / 10);

  _dec["pause_1"] = 0;
  _dec["pause_21"] = (height / 10) * 0;
  _dec["pause_22"] = (height / 10) * 0;
  _dec["pause_31"] = (height / 10) * 1 + 20;
  _dec["pause_32"] = (height / 10) * 1 + 20;
  _dec["pause_41"] = (height / 10) * 2 + 40;
  _dec["pause_42"] = (height / 10) * 2 + 40;

  for (std::map<std::string, std::string>::iterator it = _ressources.begin();
       it != _ressources.end(); ++it)
    {
      Bomb::Image   *img
	= new Bomb::Image(WIN_X / 2 - _posX[it->first] / 2,
			  WIN_Y / 2 - _posY[it->first] / 2 + (_dec[it->first]),
			  _posX[it->first], _posY[it->first],
			  it->first, it->second);
      _sprite[it->first] = img;
      _spritestate[it->first] = false;
      G_EvDispatcher->SendEvent(new Event::GraphicEvent(img, Graphic::MESHINIT), Event::SYS);
    }

  Reset();
  Std();

  this->ctor(Menu_o);

  this->posX = posX;
  this->posY = posY;
  this->width = width;
  this->height = height;
  this->path = path;
  this->name = name;

  MeshComponent           *graphic =
    new MeshComponent(GEOMETRY,
		      0,
		      0,
		      MenuMeshInit,
		      MenuMeshDraw,
		      G_Renderer);
  graphic->AssignEntity(this);
  this->AddComponent(graphic);
  // SYSTEM INPUT EVENT
  G_EvDispatcher->AddSubscriber(Event::ENGINE, this);
}

void			Bomb::Menu::Start()
{
  Reset();
  Std();
}

Bomb::GameObject	*Bomb::Menu::Clone() const
{
  return new Image(this->posX, this->posY, this->width, this->height, this->name, this->path);
}

void			Bomb::Menu::Reset()
{
  for (Sprite::iterator it = _sprite.begin(); it != _sprite.end(); ++it)
    G_EvDispatcher->SendEvent(new Event::GraphicEvent(it->second, Graphic::MESHDEL), Event::SYS);
}

void			Bomb::Menu::Std()
{
  for (SpriteState::iterator it = _spritestate.begin(); it != _spritestate.end(); ++it)
    it->second = false;
  _spritestate["pause_1"] = true;
  _spritestate["pause_21"] = true;
  _spritestate["pause_32"] = true;
  _spritestate["pause_42"] = true;
  _state = 0;
}

Bomb::Sprite*		Bomb::Menu::GetSprite()
{
  return &_sprite;
}

Bomb::SpriteState*	Bomb::Menu::GetSpriteState()
{
  return &_spritestate;
}

void		Bomb::Menu::Inc()
{
  std::string		s;
  std::stringstream	ss;
  ss << "pause_";
  ss << _state + 2;
  ss >> s;
  _spritestate[s + "1"] = false;
  _spritestate[s + "2"] = true;
  _state += 1;
  _state %= 3;
  ss.clear();
  ss << "pause_";
  ss << _state + 2;
  ss >> s;
  _spritestate[s + "1"] = true;
  _spritestate[s + "2"] = false;
}

void		Bomb::Menu::Dec()
{
  std::string		s;
  std::stringstream	ss;
  ss << "pause_";
  ss << _state + 2;
  ss >> s;
  _spritestate[s + "1"] = false;
  _spritestate[s + "2"] = true;
  _state -= 1;
  if (_state < 0)
    _state = 2;
  ss.clear();
  ss << "pause_";
  ss << _state + 2;
  ss >> s;
  _spritestate[s + "1"] = true;
  _spritestate[s + "2"] = false;
}

void		Bomb::Menu::Valid()
{
  if (_state == 0) // resume
    G_EvDispatcher->SendEvent(new Event::EngineEvent(Event::ENGINEPAUSE), Event::SYS);
  else if (_state == 1) // save
    {
       G_EvDispatcher->SendEvent(new Event::EngineEvent(Event::ENGINEPAUSE), Event::SYS);
       G_GameSettings->SaveState = true;
    }
  else // exit
    G_EvDispatcher->SendEvent(new Event::EngineEvent(Event::ENGINEQUIT), Event::SYS);
 }

void		Bomb::Menu::OnEvent(Event::Event *ev)
{
  Event::KeyboardEvent*	key = 0;
  if (ev->Scope() == Event::ENGINE)
    key = dynamic_cast<Event::KeyboardEvent*>(ev);
  if (key)
    {
      if (key->data[SDLK_UP] || key->data[SDLK_DOWN] || key->data[SDLK_RETURN])
	{
	  if (key->data[SDLK_UP])
	    Dec();
	  else if (key->data[SDLK_DOWN])
	    Inc();
	  else
	    Valid();
	}
    }
  delete ev;
}
