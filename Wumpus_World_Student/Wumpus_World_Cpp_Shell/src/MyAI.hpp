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
		int maxPenalty;
		unsigned int X;
		unsigned int Y;
		std::vector<coordinate> myLocations;

		void printCurrentState(char prevSide);
		void printStates();
		Action leftOrForward();
		Action climbOrRandom(bool exitTrigger);
		Action previousSquare();
		Action randomTurn();
		char oppositeDirection(char otherDirection);
		Action ninetyDegAction(char prevDirection);
		Action goHome(bool wall);
		Action randomWeightedAction(bool wall);
		void addNewState(bool bump, bool breeze, bool stench);
		char evalSide(Action newAction);
		char getNewDirection(Action newAction);
		char getNewSide();
		Action getRandomAction(unsigned char decision);
	// ======================================================================
	// YOUR CODE ENDS
	// ======================================================================
};

#endif

