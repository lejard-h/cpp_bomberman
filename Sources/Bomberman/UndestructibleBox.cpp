/*
** UndestructibleBox.cpp for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Bomberman
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  lun. mai  26 16:53:08 2014 hadrien lejard
// Last update Wed Jun 11 20:48:42 2014 Marc Le Labourier
*/

#include "UndestructibleBox.hh"
#include "GraphicComponent.hh"

bool    UndestructibleBoxMeshInit(Bomb::MeshComponent* mesh, Graphic::SysGraphic* sys)
{
  Graphic::TextureMap*  tgamap = sys->GetTextures();
  gdl::Texture*         tga = new gdl::Texture();
  if (tga->load(mesh->GetPath()->c_str()) == false)
    {
      //TODO : Exception
      std::cerr << "Cannot load the cube texture" << std::endl;
      return (false);
    }
  (*tgamap)[mesh->GetName()->c_str()] = tga;

  Graphic::GeometryMap* geomap = sys->GetGeometrys();
  gdl::Geometry*        geo = new gdl::Geometry();

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

bool    UndestructibleBoxMeshDraw(Bomb::MeshComponent* mesh, Graphic::SysGraphic* sys)
{
  Graphic::OGLContext*  ogl = sys->GetContext();
  gdl::BasicShader*     shader = ogl->GetShader();
  Graphic::TextureMap*  tgamap = sys->GetTextures();
  gdl::Texture*         tga = (*tgamap)[mesh->GetName()->c_str()];

  //TODO : throw Execption
  if (!tga)
    return false;
  Graphic::GeometryMap* geomap = sys->GetGeometrys();
  gdl::Geometry*        geo = (*geomap)[mesh->GetName()->c_str()];

  if (!geo)
    return false;
  tga->bind();
  geo->draw(*shader, mesh->GetPosition(), GL_QUADS);
  return true;
}

Bomb::UndestructibleBox::UndestructibleBox()
{
	this->ctor(UndestructibleBox_o);

	PositionComponent	*pos = new PositionComponent();
	pos->AssignEntity(this);
	this->AddComponent(pos);

	PhysicComponent		*physic = new PhysicComponent(UNDESTRUCTIBLE_BOX_HITBOX);
	physic->AssignEntity(this);
	this->AddComponent(physic);

	MeshComponent           *graphic =
	  new MeshComponent(GEOMETRY,
			    new std::string("box"),
			    new std::string(MODELPATH"box.tga"),
			    UndestructibleBoxMeshInit,
			    UndestructibleBoxMeshDraw,
			    G_Renderer);
	graphic->AssignEntity(this);
	this->AddComponent(graphic);
  this->_isDestroy = true;
}

Bomb::GameObject	*Bomb::UndestructibleBox::Clone() const
{
  UndestructibleBox*	u = new UndestructibleBox();
  G_EvDispatcher->SendEvent(new Event::GraphicEvent(u, Graphic::MESHADD), Event::COMMON);
  return u;
}
