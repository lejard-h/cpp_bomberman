//
// FireAnim.cpp for  in /home/lelabo_m/rendu/cpp_bomberman/Bomberman
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Tue Jun 10 15:54:09 2014 Marc Le Labourier
// Last update Wed Jun 11 20:50:34 2014 Marc Le Labourier
//

#include "Settings.hpp"
#include "FireAnim.hh"

bool		FireAnimMeshInit(Bomb::AnimComponent *mesh, Graphic::SysGraphic* sys, double, double)
{
  Graphic::TextureMap*	tgamap = sys->GetTextures();
  gdl::Texture*		tga = new gdl::Texture();
  if (tga->load(mesh->GetPath()->c_str()) == false)
    {
      //TODO : Exception
      std::cerr << "Cannot load the cube texture" << std::endl;
      return (false);
    }
  (*tgamap)[mesh->GetName()->c_str()] = tga;

  Graphic::GeometryMap*	geomap = sys->GetGeometrys();
  gdl::Geometry*	geo = new gdl::Geometry();

  // Face1
  // geo->setColor(glm::vec4(1, 0, 0, 1));
  geo->pushVertex(glm::vec3(0.5, -0.5, 0.5));
  geo->pushVertex(glm::vec3(0.5, 0.5, 0.5));
  geo->pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  geo->pushVertex(glm::vec3(-0.5, -0.5, 0.5));
  geo->pushUv(glm::vec2(0.0f, 0.0f));
  geo->pushUv(glm::vec2(1.0f, 0.0f));
  geo->pushUv(glm::vec2(1.0f, 1.0f));
  geo->pushUv(glm::vec2(0.0f, 1.0f));
  // Face2
  // geo->setColor(glm::vec4(1, 1, 0, 1));
  geo->pushVertex(glm::vec3(0.5, -0.5, -0.5));
  geo->pushVertex(glm::vec3(0.5, 0.5, -0.5));
  geo->pushVertex(glm::vec3(-0.5, 0.5, -0.5));
  geo->pushVertex(glm::vec3(-0.5, -0.5, -0.5));
  geo->pushUv(glm::vec2(0.0f, 0.0f));
  geo->pushUv(glm::vec2(1.0f, 0.0f));
  geo->pushUv(glm::vec2(1.0f, 1.0f));
  geo->pushUv(glm::vec2(0.0f, 1.0f));
  //Face3
  // geo->setColor(glm::vec4(0, 1, 1, 1));
  geo->pushVertex(glm::vec3(0.5, -0.5, -0.5));
  geo->pushVertex(glm::vec3(0.5, 0.5, -0.5));
  geo->pushVertex(glm::vec3(0.5, 0.5, 0.5));
  geo->pushVertex(glm::vec3(0.5, -0.5, 0.5));
  geo->pushUv(glm::vec2(0.0f, 0.0f));
  geo->pushUv(glm::vec2(1.0f, 0.0f));
  geo->pushUv(glm::vec2(1.0f, 1.0f));
  geo->pushUv(glm::vec2(0.0f, 1.0f));
  //Face4
  // geo->setColor(glm::vec4(1, 0, 1, 1));
  geo->pushVertex(glm::vec3(-0.5, -0.5, 0.5));
  geo->pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  geo->pushVertex(glm::vec3(-0.5, 0.5, -0.5));
  geo->pushVertex(glm::vec3(-0.5, -0.5, -0.5));
  geo->pushUv(glm::vec2(0.0f, 0.0f));
  geo->pushUv(glm::vec2(1.0f, 0.0f));
  geo->pushUv(glm::vec2(1.0f, 1.0f));
  geo->pushUv(glm::vec2(0.0f, 1.0f));
  //Face5
  // geo->setColor(glm::vec4(0, 1, 0, 1));
  geo->pushVertex(glm::vec3(0.5, 0.5, 0.5));
  geo->pushVertex(glm::vec3(0.5, 0.5, -0.5));
  geo->pushVertex(glm::vec3(-0.5, 0.5, -0.5));
  geo->pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  geo->pushUv(glm::vec2(0.0f, 0.0f));
  geo->pushUv(glm::vec2(1.0f, 0.0f));
  geo->pushUv(glm::vec2(1.0f, 1.0f));
  geo->pushUv(glm::vec2(0.0f, 1.0f));
  //Face6
  // geo->setColor(glm::vec4(0, 0, 1, 1));
  geo->pushVertex(glm::vec3(0.5, -0.5, -0.5));
  geo->pushVertex(glm::vec3(0.5, -0.5, 0.5));
  geo->pushVertex(glm::vec3(-0.5, -0.5, 0.5));
  geo->pushVertex(glm::vec3(-0.5, -0.5, -0.5));
  geo->pushUv(glm::vec2(0.0f, 0.0f));
  geo->pushUv(glm::vec2(1.0f, 0.0f));
  geo->pushUv(glm::vec2(1.0f, 1.0f));
  geo->pushUv(glm::vec2(0.0f, 1.0f));
  geo->build();
  (*geomap)[mesh->GetName()->c_str()] = geo;
  return true;
}

bool		FireAnimMeshDraw(Bomb::AnimComponent *mesh, Graphic::SysGraphic* sys,
				double x, double y)
{
  Graphic::OGLContext*	ogl = sys->GetContext();
  gdl::BasicShader*	shader = ogl->GetShader();
  Graphic::TextureMap*	tgamap = sys->GetTextures();
  gdl::Texture*		tga = (*tgamap)[mesh->GetName()->c_str()];

  //TODO : throw Execption
  if (!tga)
    return false;
  Graphic::GeometryMap*	geomap = sys->GetGeometrys();
  gdl::Geometry*	geo = (*geomap)[mesh->GetName()->c_str()];

  if (!geo)
    return false;
  glm::mat4	transfo(1.0);
  transfo = glm::translate(x - (G_GameSettings->map.x / 2), 0.0, y - (G_GameSettings->map.y / 2));
  tga->bind();
  geo->draw(*shader, transfo, GL_QUADS);
  return true;
}

Bomb::FireAnim::FireAnim()
{
  this->ctor(FireAnim_o);

  AnimComponent           *graphic =
    new AnimComponent(GEOMETRY,
		      new std::string("fireAnim"),
		      new std::string(MODELPATH"fireAnim.tga"),
		      FireAnimMeshInit,
		      FireAnimMeshDraw,
		      G_Renderer);
  graphic->AssignEntity(this);
  this->AddComponent(graphic);
  this->_isDestroy = true;
}

void			Bomb::FireAnim::Start()
{
  this->_isDestroy = false;
  for (std::map<enum ComponentType, IComponent *>::const_iterator it = this->_components.begin();
       it != this->_components.end(); ++it)
    {
      it->second->Start();
    }
}

Bomb::GameObject	*Bomb::FireAnim::Clone() const
{
  FireAnim*	fire = new FireAnim();
  return fire;
}
