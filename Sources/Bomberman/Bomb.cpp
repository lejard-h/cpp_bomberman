/*
** Bomb.cpp for Bomberman in /home/lejard_h/rendu/cpp_bomberman/Bomberman
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  lun. juin  02 16:36:49 2014 hadrien lejard
// Last update Sat Jun 14 21:05:22 2014 Marc Le Labourier
*/

#include "DamageEvent.hh"
#include "GraphicComponent.hh"
#include "Bomb.hh"

bool    BombMeshInit(Bomb::MeshComponent* mesh, Graphic::SysGraphic* sys)
{
  Graphic::ModelMap*    modelmap = sys->GetModels();
  Graphic::ModelTime*   modeltime = sys->GetModelTime();
  gdl::Model*           model = new gdl::Model();

  if (model->load(mesh->GetPath()->c_str()) == false)
    {
      std::cerr << "Cannot load the model" << std::endl;
      return false;
    }
  (*modelmap)[mesh->GetName()->c_str()] = model;
  (*modeltime)[mesh->GetName()->c_str()] = 0.f;
  mesh->SetAnime(0, true);
  return true;
}

bool    BombMeshDraw(Bomb::MeshComponent* mesh, Graphic::SysGraphic* sys)
{
  Graphic::ModelMap*    modelmap = sys->GetModels();
  Graphic::ModelTime*   modeltime = sys->GetModelTime();
  double                time = (*modeltime)[mesh->GetName()->c_str()];
  gdl::Model*           model = (*modelmap)[mesh->GetName()->c_str()];

  Graphic::OGLContext*	ogl = sys->GetContext();
  gdl::BasicShader*	shader = ogl->GetShader();
  glm::mat4		transfo = mesh->GetPosition();
  transfo = glm::translate(transfo, glm::vec3(0.0, -0.6, 0.0));
  transfo = glm::scale(transfo, glm::vec3(5.0, 5.0, 5.0));
  model->draw(*shader, transfo, time);
  (*modeltime)[mesh->GetName()->c_str()] = 0;
  return true;
}

Bomb::DefaultBomb::DefaultBomb()
{
  this->ctor(DefaultBomb_o);

  PositionComponent	*position = new PositionComponent();
  position->AssignEntity(this);
  this->AddComponent(position);
  this->_isDestroy = true;
}

void	Bomb::DefaultBomb::SetOwner(int owner)
{
  ExplodeComponent	*explode;

  if ((explode = static_cast<ExplodeComponent *>(this->GetComponent(Explode_c))))
    explode->SetOwner(owner);
}

int		Bomb::DefaultBomb::GetOwner()
{
  ExplodeComponent	*explode;

  if ((explode = static_cast<ExplodeComponent *>(this->GetComponent(Explode_c))))
    return explode->GetOwner();
  return -1;
}

Bomb::NormalBomb::NormalBomb()
{
  this->ctor(NormalBomb_o);

  TimerComponent	*timer = new TimerComponent(NORMAL_BOMB_TIMER);
  timer->AssignEntity(this);
  this->AddComponent(timer);

  PhysicComponent   *physic = new PhysicComponent(0.5);
  physic->AssignEntity(this);
  this->AddComponent(physic);

  MeshComponent           *graphic =
    new MeshComponent(MODEL,
		      new std::string("bombe"),
		      new std::string(MODELPATH"bombe/bombe.fbx"),
		      BombMeshInit,
		      BombMeshDraw,
		      G_Renderer);
  graphic->AssignEntity(this);
  this->AddComponent(graphic);

  ExplodeComponent	*explode = new ExplodeComponent(NORMAL_BOMB_POWER, NORMAL_BOMB_SIZE);
  explode->AssignEntity(this);
  this->AddComponent(explode);
  this->_isDestroy = true;

  //	AudioComponent
  AudioComponent*	audio = new AudioComponent(Event::COMMON);
  audio->AssignEntity(this);
  this->AddComponent(audio);
  _sound = new std::string("explosion");
  _soundpath = new std::string(SOUNDPATH"BOMB_01.wav");
  audio->AddSound(_soundpath, _sound);
}

Bomb::NormalBomb::~NormalBomb()
{
  delete _sound;
  delete _soundpath;
}

bool	Bomb::NormalBomb::IsDone()
{
  if (this->HasComponent(Timer_c))
    {
      TimerComponent	*timer = static_cast<TimerComponent *>(this->GetComponent(Timer_c));
      return timer->IsDone();
    }
  return false;
}

Bomb::GameObject	*Bomb::NormalBomb::Clone() const
{
  NormalBomb*	b = new NormalBomb();
  G_EvDispatcher->SendEvent(new Event::GraphicEvent(b, Graphic::MESHADD), Event::COMMON);
  return b;
}

void Bomb::NormalBomb::OnEvent(Event::Event *e)
{
  if (e->Scope() == Event::GAME && e->Subject() == Event::DAMAGE)
    this->_events.push_back(e);
  else
    delete e;
}

void      Bomb::NormalBomb::EventTreatment()
{
  if (this->_events.size())
  {
    Event::Event *ev = this->_events.front();
    this->_events.pop_front();

    Event::DamageEvent  *dam = static_cast<Event::DamageEvent *>(ev);
    if (dam && dam->id == this->GetId() && !this->_isDestroy)
      this->Destroy();
    delete ev;
  }
}

void			Bomb::NormalBomb::Update()
{
  EventTreatment();
  if (this->HasComponent(Timer_c) && !this->_isDestroy)
  {
    TimerComponent	*timer = static_cast<TimerComponent *>(this->GetComponent(Timer_c));

    timer->Update();
    if (timer->IsDone() && !this->_isDestroy)
      this->Destroy();
  }
}

void			Bomb::NormalBomb::Destroy()
{
  if (this->HasComponent(Explode_c) && !this->_isDestroy)
    {
      AudioComponent	*audio = static_cast<AudioComponent *>(this->GetComponent(Audio_c));
      if (audio)
	audio->PlaySound(_sound);
      this->_isDestroy = true;
      ExplodeComponent  *explode
	= static_cast<ExplodeComponent *>(this->GetComponent(Explode_c));
      if (explode)
	{
	  explode->Update();
	  IEntity		*player
	    = static_cast<Player *>(G_ObjectsContainer->GetObjById(explode->GetOwner(), Player_o));
	  if (player)
	    {
	      if (player && player->HasComponent(Bomb_c))
		{
		  G_EvDispatcher->SendEvent(new Event::GraphicEvent(this, Graphic::MESHDEL),
					    Event::COMMON);
		  BombComponent	*bomb
		    = static_cast<BombComponent *>(player->GetComponent(Bomb_c));
		  if (bomb)
		    bomb->AddBomb(Normal);
		}
	    }
	}
      G_EvDispatcher->SendEvent(new Event::DestroyEvent(this->GetId()), Event::COMMON);
    }
}

size_t  Bomb::NormalBomb::GetSize()
{
  ExplodeComponent  *explode = static_cast<ExplodeComponent *>(this->GetComponent(Explode_c));

  if (explode)
    return explode->GetSize();
  return 0;
}


void  Bomb::NormalBomb::SetSize(int size)
{
  ExplodeComponent  *explode = static_cast<ExplodeComponent *>(this->GetComponent(Explode_c));

  if (explode)
    explode->SetSize(size);
}
