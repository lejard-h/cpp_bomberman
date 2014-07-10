/*
** BonusSizeBomb.cpp for Bomberman in /home/lejard_h/cpp_bomberman/Bomberman
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  mar. juin  10 23:27:44 2014 hadrien lejard
// Last update Sat Jun 14 22:28:03 2014 Marc Le Labourier
*/

#include "GraphicComponent.hh"
#include "BonusSizeBomb.hh"
#include "ColliderEvent.hh"
#include "LifeComponent.hh"
#include "DamageEvent.hh"

bool    BSBMeshInit(Bomb::MeshComponent* mesh, Graphic::SysGraphic* sys)
{
  Graphic::ModelMap*    modelmap = sys->GetModels();
  gdl::Model*           model = new gdl::Model();
  Graphic::ModelTime*   modeltime = sys->GetModelTime();

  if (model->load(mesh->GetPath()->c_str()) == false)
    {
      std::cerr << "Cannot load the model" << std::endl;
      return false;
    }
  mesh->ApplicAnime(model);
  (*modelmap)[mesh->GetName()->c_str()] = model;
  mesh->SetAnime(0, true);
  (*modeltime)[mesh->GetName()->c_str()] = 0.f;
  return true;
}

bool    BSBMeshDraw(Bomb::MeshComponent* mesh, Graphic::SysGraphic* sys)
{
  Graphic::ModelMap*    modelmap = sys->GetModels();
  gdl::Model*           model = (*modelmap)[mesh->GetName()->c_str()];
  Graphic::ModelTime*   modeltime = sys->GetModelTime();
  double                time = (*modeltime)[mesh->GetName()->c_str()];
  Graphic::OGLContext* ogl = sys->GetContext();
  gdl::BasicShader* shader = ogl->GetShader();
  glm::mat4         transfo = mesh->GetPosition();
  transfo = glm::translate(transfo, glm::vec3(0.0, -0.4, 0.0));
  transfo = glm::scale(transfo, glm::vec3(0.03, 0.03, 0.03));
  model->draw(*shader, transfo, time);
  (*modeltime)[mesh->GetName()->c_str()] = 0.f;
  return true;
}

Bomb::BonusSizeBomb::BonusSizeBomb()
{
  this->ctor(BonusSizeBomb_o);

  PositionComponent	*pos = new PositionComponent();
  pos->AssignEntity(this);
  this->AddComponent(pos);

  PhysicComponent		*physic = new PhysicComponent(0.5);
  physic->AssignEntity(this);
  this->AddComponent(physic);

  MeshComponent           *graphic =
    new MeshComponent(MODEL,
		      new std::string("BSB"),
		      new std::string(MODELPATH"fire.fbx"),
		      BSBMeshInit,
		      BSBMeshDraw,
		      G_Renderer);
  graphic->AssignEntity(this);
  this->AddComponent(graphic);
  this->_isDestroy = true;

  LifeComponent	*life = new LifeComponent(1);
  life->AssignEntity(this);
  this->AddComponent(life);

  AudioComponent*       audio = new AudioComponent(Event::COMMON);
  audio->AssignEntity(this);
  this->AddComponent(audio);
  _sound = new std::string("bonus");
  _soundpath = new std::string(SOUNDPATH"coin.wav");
  audio->AddSound(_soundpath, _sound);
  audio->Start();
}

void	Bomb::BonusSizeBomb::Start()
{
  this->_isDestroy = false;
}

void	Bomb::BonusSizeBomb::Update()
{
  if (this->_events.size())
    {
      Event::Event *ev = this->_events.front();
      this->_events.pop_front();
      if (ev->Subject() == Event::COLLIDE)
	{
	  Event::CollideEvent	*collide = static_cast<Event::CollideEvent *>(ev);
	  IEntity  *entity = G_ObjectsContainer->GetObjById(collide->id2);

	  if (collide && entity && entity->HasComponent(Bomb_c) && collide->id1 == this->GetId())
	    {
	      BombComponent	*bomb = static_cast<BombComponent *>(entity->GetComponent(Bomb_c));
	      if (bomb)
		{
		  AudioComponent    *audio = static_cast<AudioComponent *>(this->GetComponent(Audio_c));
                  if (audio)
                    audio->PlaySound(_sound);
		  bomb->IncreaseSizeBombs();
		  G_EvDispatcher->SendEvent(new Event::DestroyEvent(this->GetId()), Event::COMMON);
		}
	    }
	}
      else if (ev->Subject() == Event::DAMAGE)
	{
	  Event::DamageEvent  *dam = static_cast<Event::DamageEvent *>(ev);

	  if (dam && dam->id == this->GetId())
	    {
	      LifeComponent *life = static_cast<LifeComponent *>(this->GetComponent(Life_c));
	      if (life)
		life->Damage(dam->damage);
	    }
	}

      delete ev;
    }
  this->GetComponent(Life_c)->Update();
}

void	Bomb::BonusSizeBomb::OnEvent(Event::Event *e)
{
  if (e->Scope() == Event::GAME && (e->Subject() == Event::COLLIDE || e->Subject() == Event::DAMAGE))
    this->_events.push_back(e);
  else
    delete e;
}

Bomb::GameObject	*Bomb::BonusSizeBomb::Clone() const
{
	return new BonusSizeBomb();
}
