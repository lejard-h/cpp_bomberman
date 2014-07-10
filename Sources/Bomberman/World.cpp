/*
** World.cpp for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Bomberman
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  jeu. mai  29 12:29:48 2014 hadrien lejard
// Last update Sun Jun 15 20:09:02 2014 Marc Le Labourier
*/

#include "World.hh"
#include "Settings.hpp"
#include "GraphicComponent.hh"

bool	WorldMeshInit(Bomb::MeshComponent* mesh, Graphic::SysGraphic* sys)
{
  Graphic::TextureMap*	tgamap = sys->GetTextures();
  gdl::Texture*		tga = new gdl::Texture();

  if (tga->load(mesh->GetPath()->c_str()) == false)
    {
      std::cerr << "Cannot load the ground texture" << std::endl;
      return false;
    }
  (*tgamap)[mesh->GetName()->c_str()] = tga;
  Graphic::GeometryMap* geomap = sys->GetGeometrys();
  gdl::Geometry*        geo = new gdl::Geometry();

  //geo->setColor(glm::vec4(1, 0, 0, 1));
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

bool	WorldMeshDraw(Bomb::MeshComponent* mesh, Graphic::SysGraphic* sys)
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

  Bomb::MapComponent	*map = static_cast<Bomb::MapComponent *>(mesh->GetParent()->GetComponent(Bomb::Map_c));

  if (map)
  {
    for (float x = 0.0; x < map->GetWidth() - 1; x += 1.0)
      {
	for (float y = 0.0; y < map->GetHeight() - 1; y += 1.0)
	  {
	    glm::mat4	transfo(1.0);
	    glm::vec3     vecpos(x - (G_GameSettings->map.x / 2.0) + 1.0,
				 0.05, y - (G_GameSettings->map.y / 2.0) + 1.0);
	    transfo = glm::translate(transfo, vecpos);
	    geo->draw(*shader, transfo, GL_QUADS);
	  }
      }
    return true;
  }
  return false;
}

Bomb::World::World()
{
	this->ctor(World_o);
	this->_isDestroy = true;

	MapComponent	*map;
	if (G_GameSettings && G_GameSettings->map.mapType ==  Settings::MAP)
		map = new MapComponent(G_GameSettings->map.mapPath);
	else
		map = new MapComponent(G_GameSettings->map.x, G_GameSettings->map.y);
	map->AssignEntity(this);
	this->AddComponent(map);

	MeshComponent	*graphic = new MeshComponent(GEOMETRY,
						     new std::string("ground"),
						     new std::string(MODELPATH"ground.tga"),
						     WorldMeshInit,
						     WorldMeshDraw,
						     G_Renderer);
	graphic->AssignEntity(this);
	this->AddComponent(graphic);
}

Bomb::GameObject	*Bomb::World::Clone() const
{
	return new World();
}

bool	Bomb::World::Collider(IEntity *entity, double x, double y)
{
	if (this->HasComponent(Map_c))
	{
		MapComponent	*map = static_cast<MapComponent *>(this->GetComponent(Map_c));
		return map->Collider(entity, x, y);
	}
	return true;
}

void	Bomb::World::RemoveEntity(size_t x, size_t y, int id)
{
	if (this->HasComponent(Map_c))
	{
		MapComponent	*map = static_cast<MapComponent *>(this->GetComponent(Map_c));
		map->RemoveEntity(x, y, id);
	}
}

void	Bomb::World::AddEntity(IEntity *entity, size_t x, size_t y)
{
	if (this->HasComponent(Map_c))
	{
		MapComponent	*map = static_cast<MapComponent *>(this->GetComponent(Map_c));
		map->AddEntity(entity, x, y);
	}
}

std::vector<Bomb::IEntity *>	*Bomb::World::OnCell(size_t x, size_t y)
{
	if (this->HasComponent(Map_c))
	{
		MapComponent	*map = static_cast<MapComponent *>(this->GetComponent(Map_c));
		return map->OnCell(x, y);
	}
	return 0;
}
