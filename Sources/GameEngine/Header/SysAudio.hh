//
// SysAudio.hh for  in /home/lelabo_m/rendu/cpp_bomberman/GameEngine
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Thu May 29 16:51:25 2014 Marc Le Labourier
// Last update Tue Jun 10 23:05:07 2014 Marc Le Labourier
//

#ifndef SYSAUDIO_HH_
# define SYSAUDIO_HH_

#include "Playlist.hh"
#include "GraphicContext.hh"
#include "Fonctor.hpp"
#include "Thread.hh"
#include "Event.hpp"
#include "Sys.hh"

namespace Audio
{
	class SysAudio;
	typedef       bool (SysAudio::*funcSysAudio)(const Event::AudioEvent *);

	enum EventAudio {LOAD, PLAY, PAUSE, UNPAUSE, UPDATEVOLUME};

	class SysAudio : public Bomb::ISys
	  {
	  public:
	    SysAudio(Graphic::OGLContext*);
	    ~SysAudio();
	    bool	Init();
	    void	Destroy();
	    void	Update();
	    static void	*MainLoop(void *);
	    void	Loop();
	    void	OnEvent(Event::Event *);
	  private:
	    Thread				*_eventThread;
	    Playlist				*_playlist;
	    bool				_isdestroy;
	    std::list<Event::Event*>		_events;
	    std::map<EventAudio, funcSysAudio> 	_mapSysAudioFunc;
	    Mutex				_mutex;
	private:
		bool	LoadSound(const Event::AudioEvent *);
		bool	PlaySound(const Event::AudioEvent *);
		bool	PauseSound(const Event::AudioEvent *);
		bool	UnpauseSound(const Event::AudioEvent *);
		bool	UpdateVolumeSound(const Event::AudioEvent *);
	  };

}

#endif /* !SYSAUDIO_HH_ */
