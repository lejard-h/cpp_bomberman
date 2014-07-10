//
// Player.cpp for  in /home/lelabo_m/rendu/cpp_bomberman/Bomberman
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Wed Jun 11 15:30:15 2014 Marc Le Labourier
// Last update Sun Jun 15 15:14:01 2014 Marc Le Labourier
//

#include "Settings.hpp"
#include "Player.hh"
#include "SysAudio.hh"
#include "GraphicComponent.hh"
#include "AudioComponent.hh"
#include "DamageEvent.hh"
#include "ScoreComponent.hh"
#include "World.hh"

bool	PlayerMeshInit(Bomb::MeshComponent* mesh, Graphic::SysGraphic* sys)
{
  Graphic::ModelMap*	modelmap = sys->GetModels();
  Graphic::ModelTime*	modeltime = sys->GetModelTime();
  Bomb::Player*		p = static_cast<Bomb::Player*>(mesh->GetParent());
  if (!p)
    return false;
  Bomb::PlayerData::iterator itn = p->GetNames()->begin();
  Bomb::PlayerData::iterator itp = p->GetPaths()->begin();
  while (itn != p->GetNames()->end() && itp != p->GetPaths()->end())
    {
      gdl::Model*		model = new gdl::Model();

      if (model->load(itp->second->c_str()) == false)
	{
	  std::cerr << "Cannot load the model" << std::endl;
	  return false;
	}
      (*modelmap)[itn->second->c_str()] = model;
      (*modeltime)[itn->second->c_str()] = 0.1f;
      Bomb::MeshComponent::ApplicAnime(mesh->GetAnimes(), model);
      mesh->SetName(itn->second);
      mesh->SetAnime("run", 0, true);
      ++itn;
      ++itp;
    }
  return true;
}

bool	PlayerMeshDraw(Bomb::MeshComponent* mesh, Graphic::SysGraphic* sys)
{
  Graphic::ModelMap*	modelmap = sys->GetModels();
  Graphic::ModelTime*	modeltime = sys->GetModelTime();
  Bomb::Player*		p = static_cast<Bomb::Player*>(mesh->GetParent());
  if (!p || !p->GetMyName())
    return false;
  double		time = (*modeltime)[p->GetMyName()->c_str()];
  gdl::Model*		model = (*modelmap)[p->GetMyName()->c_str()];

  Graphic::OGLContext* ogl = sys->GetContext();
  gdl::BasicShader* shader = ogl->GetShader();
  glm::mat4	    transfo = mesh->GetPosition();
  transfo = glm::translate(transfo, glm::vec3(0.0, -0.4, 0.0));
  transfo = glm::scale(transfo, glm::vec3(p->GetMySize(),
					  p->GetMySize(),
					  p->GetMySize()));
  model->draw(*shader, transfo, time);
  (*modeltime)[p->GetMyName()->c_str()] = 0.f;
  return true;
}

size_t	Bomb::Player::_nb = 0;

Bomb::Player::~Player()
{
  for (PlayerData::iterator it = _name.begin();
       it != _name.end(); ++it)
    delete it->second;
  for (PlayerData::iterator it = _path.begin();
       it != _path.end(); ++it)
    delete it->second;
  for (PlayerData::iterator it = _sound.begin();
       it != _sound.end(); ++it)
    delete it->second;
}

Bomb::Player::Player()
{
  // NAME
  _name[Settings::RABBIT2] = new std::string("lapin_final.fbx");
  _name[Settings::RABBIT1] = new std::string("lapin_invert.FBX");
  _name[Settings::MINION1] = new std::string("minionred.FBX");
  _name[Settings::MINION2] = new std::string("minionblue.FBX");
  _name[Settings::IA] = new std::string("lapin_lave.FBX");

  // PATH
  _path[Settings::RABBIT2] = new std::string(MODELPATH"lapin_final.fbx");
  _path[Settings::RABBIT1] = new std::string(MODELPATH"lapin_invert.FBX");
  _path[Settings::MINION1] = new std::string(MODELPATH"minionred.FBX");
  _path[Settings::MINION2] = new std::string(MODELPATH"minionblue.FBX");
  _path[Settings::IA] = new std::string(MODELPATH"lapin_lave.FBX");

  // SOUND
  _soundpath[Settings::RABBIT2] = new std::string(SOUNDPATH"error.mp3");
  _soundpath[Settings::RABBIT1] = new std::string(SOUNDPATH"error.mp3");
  _soundpath[Settings::MINION1] = new std::string(SOUNDPATH"what.mp3");
  _soundpath[Settings::MINION2] = new std::string(SOUNDPATH"what.mp3");
  _soundpath[Settings::IA] = new std::string(SOUNDPATH"error.mp3");

  _sound[Settings::RABBIT2] = new std::string("error.mp3");
  _sound[Settings::RABBIT1] = new std::string("error.mp3");
  _sound[Settings::MINION1] = new std::string("what.mp3");
  _sound[Settings::MINION2] = new std::string("what.mp3");
  _sound[Settings::IA] = new std::string("error.mp3");

  // SIZE
  _size[Settings::RABBIT2] = 0.001;
  _size[Settings::RABBIT1] = 0.001;
  _size[Settings::MINION1] = 0.01;
  _size[Settings::MINION2] = 0.01;
  _size[Settings::IA] = 0.001;

  // MY DATA
  _myname = 0;
  _mypath = 0;
  _mysound = 0;

  this->ctor(Player_o);

  PositionComponent	*pos = new PositionComponent();
  pos->AssignEntity(this);
  this->AddComponent(pos);

  LifeComponent		*life = new LifeComponent(PLAYER_LIFE, PLAYER_LIFE);
  life->AssignEntity(this);
  this->AddComponent(life);

  PhysicComponent		*physic = new PhysicComponent(PLAYER_HITBOX);
  physic->AssignEntity(this);
  this->AddComponent(physic);

  BombComponent		*bomb = new BombComponent();
  bomb->AddBomb(Normal);
  bomb->AssignEntity(this);
  this->AddComponent(bomb);

  MeshComponent           *graphic =
    new MeshComponent(MODEL,
		      0,
		      0,
		      PlayerMeshInit,
		      PlayerMeshDraw,
		      G_Renderer);
  Animation*	a1 = new Animation(new std::string("run"), 0, 20);
  Animation*	a2 = new Animation(new std::string("nothing"), 60, 75);
  Animation*	a3 = new Animation(new std::string("die"), 75, 100);
  graphic->AddAnime(a1);
  graphic->AddAnime(a2);
  graphic->AddAnime(a3);
  graphic->AssignEntity(this);
  this->AddComponent(graphic);
  this->_isDestroy = true;

  ScoreComponent  *score = new ScoreComponent();
  score->AssignEntity(this);
  this->AddComponent(score);

  AudioComponent		*audio = new AudioComponent(Event::COMMON);
  audio->AssignEntity(this);
  this->AddComponent(audio);
  PlayerData::iterator itn  = _sound.begin();
  PlayerData::iterator itp  = _soundpath.begin();
  while (itn != _sound.end() && itp != _soundpath.end())
    {
      audio->AddSound(itp->second, itn->second);
      ++itn;
      ++itp;
    }
  audio->Start();
}

void  Bomb::Player::Start()
{
  this->InitInput();
  Settings::Character character;

  if (_slot >= 4)
    character = Settings::IA;
  else
    character = G_GameSettings->players[_slot]->character;
  if (_name[character] != 0)
    {
      _myname = _name[character];
      _mypath = _path[character];
      _mysound = _sound[character];
      _mysize = _size[character];
      _errorsound = _soundpath[character];
    }
  this->_isDestroy = false;
  for (std::map<enum ComponentType, IComponent *>::const_iterator it = this->_components.begin();
       it != this->_components.end(); ++it)
    {
      it->second->Start();
    }
}

void  Bomb::Player::EventTreatment()
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
        {
          G_EvDispatcher->SendEvent(new Event::ScoreEvent(Event::KillTargetScoring,
							  dam->sender, this->GetId()), Event::COMMON);
          if (G_GameSettings->gamemode != Settings::SURVIVAL)
            this->Respawn();
        }
      }
    }
    delete dam;
  }
}

void Bomb::Player::OnEvent(Event::Event *e)
{
  if (e && e->Scope() == Event::GAME && e->Subject() == Event::DAMAGE)
    this->_events.push_back(e);
  else
    delete e;
}

Bomb::GameObject	*Bomb::Player::Clone() const
{
  Player	*p = new Player();
  G_EvDispatcher->SendEvent(new Event::GraphicEvent(p, Graphic::MESHADD), Event::COMMON);
  return p;
}

void  Bomb::Player::Update()
{
  this->EventTreatment();

  for (std::map<enum ComponentType, IComponent *>::const_iterator it = this->_components.begin();
       it != this->_components.end() && !this->_isDestroy;
       ++it)
    it->second->Update();
}

Bomb::PlayerType	Bomb::Player::GetPlayerType()
{
  if (this->HasComponent(PlayerInput_c))
  {
    PlayerInputComponent	*input
      = static_cast<PlayerInputComponent *>(this->GetComponent(PlayerInput_c));

    PlayerType	type;
    type = static_cast<PlayerType>(input->GetSlot());
    return type;
  }
  if (this->HasComponent(Ia_c))
    return Ia;
  return PlayerUndefined;
}

size_t	Bomb::Player::GetNbPlayer()
{
  size_t		tmp;

  tmp = _nb;
  _nb++;
  return tmp;
}

void	Bomb::Player::Reset()
{
  _nb = 0;
}

void	Bomb::Player::InitInput()
{
  size_t	nb = this->GetNbPlayer();

  if (nb < G_GameSettings->nb_players)
    {
      PlayerInputComponent	*input = new PlayerInputComponent(nb);
      input->AssignEntity(this);
      this->AddComponent(input);
      _slot = nb;
      nb++;
    }
  else if (nb < G_GameSettings->nb_players + G_GameSettings->nb_ia)
    {
      IaComponent	*ia = new IaComponent(G_GameSettings->ialevel);
      ia->AssignEntity(this);
      this->AddComponent(ia);
      _slot = 4;
      nb++;
    }
}

void  Bomb::Player::Respawn()
{
  PositionComponent *pos = static_cast<PositionComponent *>(this->GetComponent(Position_c));
  LifeComponent *life = static_cast<LifeComponent *>(this->GetComponent(Life_c));
  AudioComponent *audio = static_cast<AudioComponent *>(this->GetComponent(Audio_c));

  if (pos)
    pos->Respawn();
  if (life)
    life->Respawn();
  if (audio)
    audio->PlaySound(_mysound);
  ListObj *list_world = G_ObjectsContainer->GetObjByTag(World_o);
  if (list_world)
  {
    World *world = static_cast<World *>(list_world->front());
    if (world)
      world->AddEntity(this, pos->GetPosition(PositionComponent::X),
       pos->GetPosition(PositionComponent::Y));
  }
  G_EvDispatcher->SendEvent(new Event::GraphicEvent(this, Graphic::MESHADD),
   Event::COMMON);
}

Bomb::PlayerData*	Bomb::Player::GetNames()
{
  return &_name;
}

Bomb::PlayerData*	Bomb::Player::GetPaths()
{
  return &_path;
}

Bomb::PlayerData*	Bomb::Player::GetSounds()
{
  return &_sound;
}

Bomb::PlayerSize*	Bomb::Player::GetSizes()
{
  return &_size;
}

std::string*	Bomb::Player::GetMyName()
{
  return _myname;
}

const std::string*	Bomb::Player::GetMyPath() const
{
  return _mypath;
}

const std::string*	Bomb::Player::GetMySound() const
{
  return _mysound;
}

double			Bomb::Player::GetMySize() const
{
  return _mysize;
}
