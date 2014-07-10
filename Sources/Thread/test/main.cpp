//
// main.cpp for  in /home/lelabo_m/rendu/cpp_bomberman/Thread/test
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Sat May 31 12:17:22 2014 Marc Le Labourier
// Last update Tue Jun  3 09:56:15 2014 Marc Le Labourier
//

#include <iostream>
#include <unistd.h>
#include "Thread.hh"

int	var = 0;

void	*func(void *)
{
  for (int n = 0; n < 5000000; ++n)
    {
      ++var;
      usleep(5000);
    }
  return (0);
}

// int	main()
// {
//   TaskThread*	th = new TaskThread(func, 0);

//   th->run();
//   for (int i = 0; i <= 10000; ++i)
//     {
//       th->wait();
//       std::cout << var << std::endl;
//       th->update();
//     }
//   std::cout << var << std::endl;
//   th->stop();
//   return (0);
// }

int	main()
{
  Thread	*th = 0;

  th = new Thread(func, 0);
  th->run();
  std::cout << "Thread" << std::endl;
  th->join();
  delete th;
  return 0;
}
