/*
** Image.cpp for Bomber in /home/thomas_1/Desktop/Projets/Bomberman/cpp_bomberman/Bomberman
**
** Made by Pierre-Yves THOMAS
** Login   <thomas_1@epitech.net>
**
** Started on  Sat Jun  07 17:43:14 2014 Pierre-Yves THOMAS
// Last update Thu Jun 12 16:11:55 2014 Marc Le Labourier
*/

#include "Image.hh"
#include "GraphicComponent.hh"


bool    ImageMeshInit(Bomb::MeshComponent* mesh, Graphic::SysGraphic* sys)
{

  Graphic::TextureMap*  tgamap = sys->GetTextures();
  gdl::Texture*         tga = new gdl::Texture();
  if (tga->load(mesh->GetPath()->c_str()) == false)
    {
      //TODO : Exception
      std::cerr << "Cannot load the image \"" << mesh->GetPath()->c_str() << "\"" << std::endl;
      return (false);
    }
  (*tgamap)[mesh->GetName()->c_str()] = tga;

  Graphic::GeometryMap* geomap = sys->GetGeometrys();
  gdl::Geometry*        geo = new gdl::Geometry();
  Bomb::Image*          img = dynamic_cast<Bomb::Image *>(mesh->GetParent());

  if (!img)
  {

    // TODO : Exception ?
    std::cerr << "Invalid dynamic conversion for mesh->GetParent" << std::endl;
    return(false);
  }

  //geo->setColor(glm::vec4(1, 1, 1, 1));
  geo->pushVertex(glm::vec3(img->getPosX(), img->getPosY(), 0));
  geo->pushVertex(glm::vec3(img->getPosX() + img->getWidth(), img->getPosY(), 0));
  geo->pushVertex(glm::vec3(img->getPosX() + img->getWidth(), img->getPosY() + img->getHeight(), 0));
  geo->pushVertex(glm::vec3(img->getPosX(), img->getPosY() + img->getHeight(), 0));
  geo->pushUv(glm::vec2(0.0f, 1.0f));
  geo->pushUv(glm::vec2(1.0f, 1.0f));
  geo->pushUv(glm::vec2(1.0f, 0.0f));
  geo->pushUv(glm::vec2(0.0f, 0.0f));
  geo->build();

  (*geomap)[mesh->GetName()->c_str()] = geo;

  return true;
}

bool    ImageMeshDraw(Bomb::MeshComponent* mesh, Graphic::SysGraphic* sys)
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
  glm::mat4 projection;
  projection = glm::ortho(0.0f, 1000.0f, 800.0f, 0.0f, -1.0f, 1.0f);

  shader->bind();
  shader->setUniform("view", glm::mat4(1));
  shader->setUniform("projection", projection);

  tga->bind();

  glDisable(GL_DEPTH_TEST);
  geo->draw(*shader, glm::mat4(1), GL_QUADS);
  glEnable(GL_DEPTH_TEST);
  ogl->AskCamUpdate();
  ogl->CamUpdate();
  return true;
}


Bomb::Image::Image(int posX, int posY, int width, int height, std::string name, std::string path)
{

  this->ctor(Image_o);

  PositionComponent	*pos = new PositionComponent();
  pos->AssignEntity(this);
  this->AddComponent(pos);

  /*
	PhysicComponent		*physic = new PhysicComponent(UNDESTRUCTIBLE_BOX_HITBOX);
	physic->AssignEntity(this);
	this->AddComponent(physic);
  */


  this->posX = posX;
  this->posY = posY;
  this->width = width;
  this->height = height;
  this->path = path;
  this->name = name;

  MeshComponent           *graphic =
    new MeshComponent(GEOMETRY,
		      new std::string(this->name),
		      new std::string(this->path),
		      ImageMeshInit,
		      ImageMeshDraw,
		      G_Renderer);
  graphic->AssignEntity(this);
  this->AddComponent(graphic);
}

Bomb::Image::Image()
{

  this->posX = 0;
  this->posY = 0;
  this->width = 0;
  this->height = 0;
  this->path = "";
  this->name = "";

}

Bomb::GameObject	*Bomb::Image::Clone() const
{
  return new Image(this->posX, this->posY, this->width, this->height, this->name, this->path);
}

int   Bomb::Image::getPosX() const
{
  return (this->posX);
}

int   Bomb::Image::getPosY() const
{
  return (this->posY);
}

int   Bomb::Image::getWidth() const
{
  return (this->width);
}

int   Bomb::Image::getHeight() const
{
  return (this->height);
}

void   Bomb::Image::setPosX(int value)
{
  this->posX = value;
}

void   Bomb::Image::setPosY(int value)
{
  this->posY = value;
}

void   Bomb::Image::setWidth(int value)
{
  this->width = value;
}

void   Bomb::Image::setHeight(int value)
{
  this->height = value;
}

void  Bomb::Image::setInformations(int posX, int posY, int width, int height)
{
  this->setPosX(posX);
  this->setPosY(posY);
  this->setWidth(width);
  this->setHeight(height);
}

const std::string  &Bomb::Image::getName() const
{
  return (this->name);
}

void  Bomb::Image::setName(const std::string &name)
{
  this->name = name;
}

const std::string  &Bomb::Image::getPath() const
{
  return (this->path);
}

void  Bomb::Image::setPath(const std::string &path)
{
  this->path = path;
}
