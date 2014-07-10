//
// timecounter.hh for  in /home/lelabo/rendu/cpp_nibbler/game
//
// Made by lelabo_m
// Login   <lelabo@epitech.net>
//
// Started on  Wed Apr  2 00:14:02 2014 lelabo_m
// Last update Wed Jun 11 13:44:57 2014 Marc Le Labourier
//

#ifndef TIMECOUNTER_HH_
# define TIMECOUNTER_HH_

class TimeCounter
{
public:
  TimeCounter();
  ~TimeCounter();
  int	GetTime();
  int	GetRealTime();
  void	Pause();
  void	Reset();
private:
  int	_starttime;
  int	_pausetime;
  bool	_pause;
};

#endif /* !TIMECOUNTER_HH_ */
