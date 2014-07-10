/*
** DestructibleBox.cpp for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Bomberman
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  lun. mai  26 17:01:25 2014 hadrien lejard
// Last update Wed Jun 11 20:48:32 2014 Marc Le Labourier
*/

#include "DestructibleBox.hh"
#include "GraphicComponent.hh"
#include "DropBonusComponent.hh"
#include "ScoreEvent.hh"

bool	DestructibleBoxMeshInit(Bomb::MeshComponent* mesh, Graphic::SysGraphic* sys)
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

bool	DestructibleBoxMeshDraw(Bomb::MeshComponent* mesh, Graphic::SysGraphic* sys)
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
  tga->bind();
  geo->draw(*shader, mesh->GetPosition(), GL_QUADS);
  return true;
}

Bomb::DestructibleBox::DestructibleBox()
{
	this->ctor(DestructibleBox_o);

	PositionComponent	*pos = new PositionComponent();
	pos->AssignEntity(this);
	this->AddComponent(pos);

	LifeComponent		*life = new LifeComponent(1);
	life->AssignEntity(this);
	this->AddComponent(life);

	PhysicComponent		*physic = new PhysicComponent(DESTRUCTIBLE_BOX_HITBOX);
	physic->AssignEntity(this);
	this->AddComponent(physic);


  DropBonusComponent   *dropBonus = new DropBonusComponent();
  dropBonus->AssignEntity(this);
  this->AddComponent(dropBonus);

	MeshComponent		*graphic =
	  new MeshComponent(GEOMETRY,
			    new std::string("box2"),
			    new std::string(MODELPATH"box2.tga"),
			    DestructibleBoxMeshInit,
			    DestructibleBoxMeshDraw,
			    G_Renderer);
	graphic->AssignEntity(this);
	this->AddComponent(graphic);

  this->_isDestroy = true;

	/*AudioComponent		*audio = new AudioComponent();
	audio->AssignEntity(this);
	this->AddComponent(audio);*/
}

void  Bomb::DestructibleBox::EventTreatment()
{
  if (this->_events.size())
  {
    Event::DamageEvent  *dam = static_cast<Event::DamageEvent *>(this->_events.front());
    this->_events.pop_front();

    if (dam && dam->id == this->GetId())
    {
      LifeComponent *life = static_cast<LifeComponent *>(this->GetComponent(Life_c));
      if (life)
      {
        life->Damage(dam->damage);
        if (life->GetLife() <= 0)
          G_EvDispatcher->SendEvent(new Event::ScoreEvent(Event::KillTargetScoring, dam->sender, this->GetId()), Event::COMMON);
      }
    }
    delete dam;
  }
}

void Bomb::DestructibleBox::OnEvent(Event::Event *e)
{
  if (e && e->Scope() == Event::GAME && e->Subject() == Event::DAMAGE)
    this->_events.push_back(e);
  else 
    delete e;
}

void  Bomb::DestructibleBox::Update()
{
  this->EventTreatment();
  for (std::map<enum ComponentType, IComponent *>::const_iterator it = this->_components.begin();
    it != this->_components.end() && !this->_isDestroy;
    ++it)
    it->second->Update();
}

Bomb::GameObject *Bomb::DestructibleBox::Clone() const
{
  DestructibleBox*	d = new DestructibleBox();
  G_EvDispatcher->SendEvent(new Event::GraphicEvent(d, Graphic::MESHADD), Event::COMMON);
  return d;
}
