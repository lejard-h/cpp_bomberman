/*
** IAchecks.hh for Bomber in /home/thomas_1/Desktop/Projets/Bomberman/cpp_bomberman/Bomberman/Header
**
** Made by Pierre-Yves THOMAS
** Login   <thomas_1@epitech.net>
**
** Started on  Tue Jun  10 21:25:13 2014 Pierre-Yves THOMAS
** Last update Tue Jun  10 21:25:13 2014 Pierre-Yves THOMAS
*/

#ifndef IAACTIONS_HH
#define IAACTIONS_HH

#include "IaComponent.hh"
#include "Astar.hh"
#include "Bomb.hh"

#define FCOS(angle) ((angle == 90 || angle == 270) ? (0) : ((angle == 0) ? (1) : (-1)))
#define FSIN(angle) ((angle == 0 || angle == 180) ? (0) : ((angle == 90) ? (1) : (-1)))
#define INCRS(v1, v2) 	((v1 > v2) ? (-1) : (1))

namespace Bomb
{
	class IaComponent;
	class NormalBomb;

	class IAactions
	{
	public:
		IAactions(IaComponent *Ia);
		~IAactions();

		bool 	isSafe();
		bool	isSafe(int, int);
		bool 									isDestructibleObjectOnRange();
		bool 									isDestructibleObjectOnRange(double, double);
		bool 									getPathAtRange(int);
		bool 									getBonusAtRange(int);
		bool									getDestructibleObjectAtRange(int);
		bool									findOtherAI();
		bool 									findShortestPath(const std::list<std::pair<int, int> > &);
		const std::list<std::pair<double, double> > 	&getShortestPath() const;
		const std::list<std::pair<int, int> > 			&getSafePath() const;
		const std::list<std::pair<int, int> > 			&getBonusPath() const;
		const std::list<std::pair<int, int> > 			&getDestruciblePath() const;
		const std::list<std::pair<int, int> > 			&getOtherAIPath() const;

	private:
		IaComponent 		*_ia;
		MapComponent		*_map;
		ListObj 			*_bombs;
		ListObj				*_AI;

		std::list<std::pair <int, int> > 		_safePaths;
		std::list<std::pair <int, int> > 		_bonusPaths;
		std::list<std::pair <int, int> > 		_destructiblePaths;
		std::list<std::pair <int, int> >		_otherAIPaths;
		std::list<std::pair <double, double> > 	_shortestPath;
		
		bool 	isExplodingAt(NormalBomb * const) const;
		bool 	isExplodingAt(NormalBomb * const, int, int) const;
	};
}

#endif