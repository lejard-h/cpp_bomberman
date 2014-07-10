/*
** Astar.hh for Bomber in /home/thomas_1/Desktop/Projets/Bomberman/cpp_bomberman/IA
**
** Made by Pierre-Yves THOMAS
** Login   <thomas_1@epitech.net>
**
** Started on  Wed Jun  04 21:17:11 2014 Pierre-Yves THOMAS
** Last update Wed Jun  04 21:17:11 2014 Pierre-Yves THOMAS
*/

#ifndef ASTAR_HH
#define ASTAR_HH

#include <utility>
#include <list>
#include "MapComponent.hh"

namespace Algo
{
	class nodeAstar;

	typedef std::pair<int, int> position;
	typedef std::pair<double, double> positionD;

	typedef std::list<position> path;
	typedef std::list<position>::iterator pathIt;
	typedef std::list<position>::const_iterator pathItConst;

	typedef std::list<positionD> pathD;
	typedef std::list<positionD>::iterator pathDIt;
	typedef std::list<positionD>::const_iterator pathDItConst;

	typedef std::list<nodeAstar *> listNode;
	typedef std::list<nodeAstar *>::iterator listNodeIt;
	typedef std::list<nodeAstar *>::const_iterator listNodeItConst;

	class nodeAstar
	{
		public:
			nodeAstar(int, int, nodeAstar * const);
			nodeAstar(const position &, nodeAstar * const);
			~nodeAstar();

			void 			calcRange(const position &);
			void 			calcRange(int, int);
			int 			getRange() const;
			const position &getPosition() const;
			nodeAstar * 	getParent() const;

		private:
			position 	_position;
			int 		_range;
			nodeAstar 	*_parent;
	};

	class Astar
	{
	public:
		Astar();
		~Astar();
		void 	updateMap(Bomb::MapComponent * const);
		void 	updatePosition(int, int);
		void 	updatePosition(const position &);
		void 	updateReach(int, int);
		void 	updateReach(const position &);
		bool 	calculatePath();
		const pathD &getPath() const;
		void 	displayPath() const;
		void 	reset();
		void 	clearNodes();
		void 	clearPath();

	private:
		Bomb::MapComponent			*_map;
		pathD 						_path;
		listNode 					_closedNodes;
		listNode 					_openedNodes;

		position	_begin;
		position 	_end;
		void  			createPath();
		bool 			calculateNodesAround(nodeAstar * const, const position &);
		bool 			insertNodeInList(int, int, nodeAstar * const, const position &);
		nodeAstar *defineNextNode() const;
	};
}

#endif