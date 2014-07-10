/*
** BonusSpeedPlayer.cpp for Bomberman in /home/lejard_h/cpp_bomberman/Bomberman
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  mar. juin  10 21:35:58 2014 hadrien lejard
// Last update Sat Jun 14 22:27:10 2014 Marc Le Labourier
*/

#include "Settings.hpp"
#include "GraphicComponent.hh"
#include "BonusSpeedPlayer.hh"
#include "DamageEvent.hh"

bool    BSPMeshInit(Bomb::MeshComponent* mesh, Graphic::SysGraphic* sys)
{
  Graphic::ModelMap*    modelmap = sys->GetModels();
  Graphic::ModelTime*   modeltime = sys->GetModelTime();
  gdl::Model*           model = new gdl::Model();

  if (model->load(mesh->GetPath()->c_str()) == false)
    {
      std::cerr << "Cannot load the model" << std::endl;
      return false;
    }
  mesh->ApplicAnime(model);
  (*modelmap)[mesh->GetName()->c_str()] = model;
  (*modeltime)[mesh->GetName()->c_str()] = 0.f;
  mesh->SetAnime(0, true);
  return true;
}

bool    BSPMeshDraw(Bomb::MeshComponent* mesh, Graphic::SysGraphic* sys)
{
  Graphic::ModelMap*    modelmap = sys->GetModels();
  Graphic::ModelTime*   modeltime = sys->GetModelTime();
  double                time = (*modeltime)[mesh->GetName()->c_str()];
  gdl::Model*           model = (*modelmap)[mesh->GetName()->c_str()];
  Graphic::OGLContext* ogl = sys->GetContext();
  gdl::BasicShader* shader = ogl->GetShader();
  glm::mat4         transfo = mesh->GetPosition();
  transfo = glm::translate(transfo, glm::vec3(0.0, -0.4, 0.0));
  transfo = glm::scale(transfo, glm::vec3(0.03, 0.03, 0.03));
  model->draw(*shader, transfo, time);
  (*modeltime)[mesh->GetName()->c_str()] = 0.f;
  return true;
}

Bomb::BonusSpeedPlayer::BonusSpeedPlayer() : _idTarget(-1)
{
  this->ctor(BonusSpeed_o);

  PositionComponent	*pos = new PositionComponent();
  pos->AssignEntity(this);
  this->AddComponent(pos);

  PhysicComponent		*physic = new PhysicComponent(0.5);
  physic->AssignEntity(this);
  this->AddComponent(physic);

  TimerComponent		*timer = new TimerComponent(5);
  timer->AssignEntity(this);
  this->AddComponent(timer);

  MeshComponent           *graphic =
    new MeshComponent(MODEL,
		      new std::string("BSP"),
		      new std::string(MODELPATH"speedup.fbx"),
		      BSPMeshInit,
		      BSPMeshDraw,
		      G_Renderer);
  graphic->AssignEntity(this);
  this->AddComponent(graphic);
  this->_isDestroy = true;

  LifeComponent   *life = new LifeComponent(1);
  life->AssignEntity(this);
  this->AddComponent(life);

  AudioComponent*       audio = new AudioComponent(Event::COMMON);
  audio->AssignEntity(this);
  this->AddComponent(audio);
  _sound = new std::string("bonus");
  _soundpath = new std::string(SOUNDPATH"coin.wav");
  audio->AddSound(_soundpath, _sound);
  audio->Start();

  this->_idTarget = -1;
}

void	Bomb::BonusSpeedPlayer::EventTreatment()
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
	      if (this->_idTarget != -1)
		return ;
	      AudioComponent    *audio = static_cast<AudioComponent *>(this->GetComponent(Audio_c));
	      if (audio)
	      	audio->PlaySound(_sound);
	      TimerComponent	*timer = static_cast<TimerComponent *>(this->GetComponent(Timer_c));
	      if (timer)
		{
		  timer->Start();
		  this->_idTarget = entity->GetId();
		  DeleteObjectFromMap(this->GetId());
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

void	Bomb::BonusSpeedPlayer::Start()
{
	this->_isDestroy = false;
}

void	Bomb::BonusSpeedPlayer::Update()
{
  this->EventTreatment();
  TimerComponent	*timer = static_cast<TimerComponent *>(this->GetComponent(Timer_c));

  if (this->_idTarget != -1 && G_ObjectsContainer)
    {
      timer->Update();
      IEntity	*target = G_ObjectsContainer->GetObjById(this->_idTarget);

      if (target)
	{
	  PhysicComponent	*physic
	    = static_cast<PhysicComponent *>(target->GetComponent(Physics_c));

	  if (timer && timer->IsStart() && !timer->IsDone())
	    {
	      physic->SetVelocityBonus(2.0);
	      DeleteObjectFromMap(this->GetId());
	    }
	  else if (timer && timer->IsStart() && timer->IsDone())
	    {
	      G_EvDispatcher->SendEvent(new Event::DestroyEvent(this->GetId()), Event::COMMON);
	      physic->SetVelocityBonus(1.0);
	    }
	}
    }
}

void	Bomb::BonusSpeedPlayer::OnEvent(Event::Event *e)
{
  if (e->Scope() == Event::GAME && (e->Subject() == Event::COLLIDE || e->Subject() == Event::DAMAGE))
    this->_events.push_back(e);
  else
    delete e;
}

Bomb::GameObject	*Bomb::BonusSpeedPlayer::Clone() const
{
  return new BonusSpeedPlayer();
}
