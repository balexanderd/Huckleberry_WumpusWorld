	// ======================================================================
// FILE:        MyAI.hpp
//
// AUTHOR:      Abdullah Younis
//
// DESCRIPTION: This file contains your agent class, which you will
//              implement. You are responsible for implementing the
//              'getAction' function and any helper methods you feel you
//              need.
//
// NOTES:       - If you are having trouble understanding how the shell
//                works, look at the other parts of the code, as well as
//                the documentation.
//
//              - You are only allowed to make changes to this portion of
//                the code. Any changes to other portions of the code will
//                be lost when the tournament runs your code.
// ======================================================================

#ifndef MYAI_LOCK
#define MYAI_LOCK

#include "Agent.hpp"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>

// ==========================================================================
// YOUR CLASS BEGINS
// ==========================================================================
class coordinate
{
	public:
		unsigned int X, Y, hDistance;
		char direction;
		bool breeze, stench, visited;
		int pit, wumpus;
		coordinate() : X(0), Y(0), direction('U'), breeze(false), stench(false), visited(false), hDistance(0), pit(0), wumpus(0) {}
		coordinate(unsigned int x, unsigned int y, char dir, bool b, bool s, bool v)
			: X(x), Y(y), direction(dir), breeze(b), stench(s), visited(v), hDistance(x+y), pit(0), wumpus(0) {}
		coordinate(const coordinate& c)
		{
			if(this != &c) {
				this->X = c.X;
				this->Y = c.Y;
				direction = c.direction;
				this->breeze = c.breeze;
				this->stench = c.stench;
				this->visited = c.visited;
				this->pit = c.pit;
				this->wumpus = c.wumpus;
				this->hDistance = c.hDistance;
			}
		}
		coordinate& operator= (const coordinate& c)
		{
			if(this != &c) {
				this->X = c.X;
				this->Y = c.Y;
				direction = c.direction;
				this->breeze = c.breeze;
				this->stench = c.stench;
				this->visited = c.visited;
				this->pit = c.pit;
				this->wumpus = c.wumpus;
				this->hDistance = c.hDistance;
			}
			return *this;
		}
		bool operator== (const coordinate& c) const
		{
			return (this->X == c.X && this->Y == c.Y);
		}
		bool operator!= (const coordinate& c) const
		{
			return !(this->X == c.X && this->Y == c.Y);
		}
		bool operator< (const coordinate& c) const
		{
			return (this->hDistance < c.hDistance);
		}
		coordinate& operator+= (const coordinate& c)
		{
			this->X += c.X;
			this->Y += c.Y;
		}
		coordinate& operator-= (const coordinate& c)
		{
			if(this->X >= c.X && this->Y >= c.Y)
				this->X -= c.X, this->Y -= c.Y;
			return *this;
		}
		void printCoordinate()
		{
			std::cout << "(X, Y): (" << X << ", " << Y << ")  hDistance: " << hDistance
					  << "  Visited: " << visited << "  Breeze: " << breeze << "  Stench: "
					  << stench << "  Pit: " << pit << "  Wumpus: " << wumpus << std::endl;
		}
};
// ==========================================================================
// YOUR CLASS ENDS
// ==========================================================================


class MyAI : public Agent
{
public:
	MyAI ( void );
	
	Action getAction
	(
		bool stench,
		bool breeze,
		bool glitter,
		bool bump,
		bool scream
	);
	
	// ======================================================================
	// YOUR CODE BEGINS
	// ======================================================================
		bool gold;
		bool dead;
		bool shot;
		char direction;
		char side;
		char condition;
		Action prevAction;
		int score;
		unsigned int moveNumber;
		int maxPenalty;
		int wumpusSighting;
		unsigned int X;
		unsigned int Y;
		unsigned int eWall;
		unsigned int nWall;
		unsigned int norSum, easSum, souSum, wesSum;
		unsigned int timeout;
		std::vector<coordinate> myLocations;
		std::vector<coordinate> neighbors;
		coordinate allLocations[7][7];

		void printCurrentState(char prevSide);
		void printStates();
		void printNeighbors();
		void printBoard();
		Action leftOrForward();
		Action climbOrShoot(bool exitTrigger, bool stench, bool scream);
		Action shootWumpus();
		Action shootAction();
		coordinate getPrevStenchCoord();
		Action climbOrRandom(bool exitTrigger);
		Action previousSquare();
		Action randomTurn();
		char oppositeDirection(char otherDirection);
		Action ninetyDegAction(char prevDirection);
		Action goHome(bool wall);
		Action randomWeightedAction(bool wall);
		void addNewState(bool bump, bool breeze, bool stench);
		std::vector<coordinate> getNeighbors();
		void updateAllLocations(bool wall, bool breeze, bool stench);
		char evalSide(Action newAction);
		char getNewDirection(Action newAction);
		char getNewSide();
		Action getRandomAction(unsigned char decision);
		Action ninetyDegAlignAction(char suggestedDirection);
		Action alignDirectionToSuggested(char suggestedDirection);
		char getSuggestedDirection();
		char getDesiredBearing(unsigned int desiredX, unsigned int desiredY);
		Action suggestUnexploredDirection();
		bool updateUnexploredRegionScore();
	// ======================================================================
	// YOUR CODE ENDS
	// ======================================================================
};

#endif

