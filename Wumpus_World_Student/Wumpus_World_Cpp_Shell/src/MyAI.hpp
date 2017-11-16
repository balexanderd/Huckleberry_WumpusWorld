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
#include "coordinate.h"
#include <algorithm>

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
		Action leftOrForward();
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

