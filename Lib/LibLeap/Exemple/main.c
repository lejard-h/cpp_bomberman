/*
** main.c for  in /home/lelabo_m/rendu/cpp_bomberman/Leapd
**
** Made by Marc Le Labourier
** Login   <lelabo_m@epitech.net>
**
** Started on  Tue Jun 10 21:26:02 2014 Marc Le Labourier
** Last update Tue Jun 10 21:34:49 2014 Marc Le Labourier
*/

#include <unistd.h>
#include "LeapManager.hh"

int	main()
{
  Event::LeapManager	leap;
  Event::LeapData	data;

  data.gesture = Event::NOGESTURE;
  leap.Connect();
  while (data.gesture != Event::INVCIRCLE)
    {
      if (leap.HasUpdate())
	{
	  data = leap.GetLeapData();
	  Event::LeapManager::DebugData(data);
	}
      usleep(50000);
    }
  leap.Disconnect();
}
