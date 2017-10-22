// ======================================================================
// FILE:        MyAI.cpp
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

#include "MyAI.hpp"

MyAI::MyAI() : Agent()
{
	// ======================================================================
	// YOUR CODE BEGINS
	// ======================================================================
	gold = false;
	dead = false;
	shot = false;
	direction = 'E';
	side = 'S';
	condition = 0;
	prevAction = CLIMB;
	score = 0;
	srand(time(NULL));
	// ======================================================================
	// YOUR CODE ENDS
	// ======================================================================
}
	
Agent::Action MyAI::getAction
(
	bool stench,
	bool breeze,
	bool glitter,
	bool bump,
	bool scream
)
{
	// ======================================================================
	// YOUR CODE BEGINS
	// ======================================================================
	score--;
	Action newAction;
	
	if(glitter) {
		gold = true;
		newAction = GRAB;
	}

	else {
		if(breeze || stench) {
			if(prevAction == CLIMB)
				newAction = climbOrRandom(breeze || stench);
			else
				newAction = previousSquare();
		}

		else if(gold || score <= -4)
			newAction = goHome(bump);

		else
			newAction = randomWeightedAction(bump);
	}

	direction = getNewDirection(newAction);
	side = evalSide(newAction);
	prevAction = newAction;

	std::cout << "side: " << side << ", direction: " << direction << std::endl;

	if((gold || score <= -4) && side == 'B')
		return CLIMB;
	return newAction;
	// ======================================================================
	// YOUR CODE ENDS
	// ======================================================================
}

// ======================================================================
// YOUR CODE BEGINS
// ======================================================================
Agent::Action MyAI::leftOrForward()
{
	int random = rand() % 10 + 1;
	if(random <= 3) {
		side = 'W';		//This should be changed!!!!
		direction = 'N';
		return TURN_LEFT;
	}
	return FORWARD;
}
Agent::Action MyAI::climbOrRandom(bool exitTrigger)
{
	if(exitTrigger)
		return CLIMB;
	return leftOrForward();
}

Agent::Action MyAI::previousSquare()
{
	if(condition == 0)
	{
		bool decision = rand() % 2;
		condition = 1;
		return decision ? TURN_LEFT : TURN_RIGHT;
	}
	if(condition == 1)
	{
		condition = 2;
		return prevAction;
	}
	condition = 0;
	return FORWARD;
}

Agent::Action MyAI::goHome(bool wall)
{
	return randomWeightedAction(wall);
}

Agent::Action MyAI::randomWeightedAction(bool wall)
{
	unsigned char decision = rand() % 12 + 1;
	if(wall)
		side = getNewSide();
	return getRandomAction(decision);
}

char MyAI::evalSide(Action newAction)
{
	if(newAction == FORWARD)
	{
		switch(side) {
			case 'N' :
				if(direction == 'S')
					return 'O';
				break;
			case 'E' :
				if(direction == 'W')
					return 'O';
				break;
			case 'S' :
				if(direction == 'N')
					return 'O';
				break;
			case 'W' :
				if(direction == 'E')
					return 'O';
				break;
			case 'B' :
				if(direction == 'N')
					return 'W';
				else if(direction == 'E')
					return 'S';
				break;
			case 'b' :
				if(direction == 'N')
					return 'E';
				else if(direction == 'W')
					return 'S';
				break;
			case 't' :
				if(direction == 'S')
					return 'E';
				else if(direction == 'W')
					return 'N';
				break;
			case 'T' :
				if(direction == 'S')
					return 'W';
				else if(direction == 'E')
					return 'N';
				break;
			default :
				return side;
		}
	}
	return side;	
}

char MyAI::getNewDirection(Action newAction)
{
	if(newAction == FORWARD || newAction == GRAB || newAction == SHOOT || newAction == CLIMB)/*No Direction Change*/
		return direction;
	
	if(direction == 'N') {
		if(newAction == TURN_LEFT)
			return 'W';
		return 'E';
	}
	if(direction == 'E') {
		if(newAction == TURN_LEFT)
			return 'N';
		return 'S';
	}
	if(direction == 'S') {
		if(newAction == TURN_LEFT)
			return 'E';
		return 'W';
	}
	/*else west*/
	if(newAction == TURN_LEFT)
		return 'S';
	return 'N';
}

char MyAI::getNewSide()
{
	char newSide;
	if(direction == 'N') {
		if(side == 'W')
			newSide = 'T';
		else if(side == 'E')
			newSide = 't';
		else
			newSide = 'N';
	}
	else if(direction == 'E') {
		if(side == 'N')
			newSide = 't';
		else if(side == 'S')
			newSide = 'b';
		else
			newSide = 'E';
	}
	else if(direction == 'S') {
		if(side == 'W')
			newSide = 'B';
		else if(side == 'E')
			newSide = 'b';
		else
			newSide = 'S';
	}
	else/*west*/ {
		if(side == 'S')
			newSide = 'B';
		else if(side == 'N')
			newSide = 'T';
		else
			newSide = 'W';
	}
	return newSide;
}

Agent::Action MyAI::getRandomAction(unsigned char decision)
{
	switch(side)
	{
		case 'S' :
			if(direction == 'N')
				return (decision <= 8) ? FORWARD : ( (decision <= 10) ? TURN_LEFT : TURN_RIGHT );
			else if(direction == 'E')
				return (decision <= 9) ? FORWARD : TURN_LEFT;
			else if(direction == 'S')
				return (decision <= 6) ? TURN_LEFT : TURN_RIGHT;
			/*else west*/
			return (decision <= 9) ? FORWARD : TURN_RIGHT;
		case 'W' :
			if(direction == 'N')
				return (decision <= 9) ? FORWARD : TURN_RIGHT;
			else if(direction == 'E')
				return (decision <= 8) ? FORWARD : ( (decision <= 10) ? TURN_LEFT : TURN_RIGHT );
			else if(direction == 'S')
				return (decision <= 9) ? FORWARD : TURN_LEFT;
			/*else west*/
			return (decision <= 6) ? TURN_LEFT : TURN_RIGHT;
		case 'N' :
			if(direction == 'N')
				return (decision <= 6) ? TURN_LEFT : TURN_RIGHT;
			else if(direction == 'E')
				return (decision <= 9) ? FORWARD : TURN_RIGHT;
			else if(direction == 'S')
				return (decision <= 8) ? FORWARD : ( (decision <= 10) ? TURN_LEFT : TURN_RIGHT );
			/*else west*/
			return (decision <= 9) ? FORWARD : TURN_LEFT;
		case 'E' :
			if(direction == 'N')
				return (decision <= 9) ? FORWARD : TURN_LEFT;
			else if(direction == 'E')
				return (decision <= 6) ? TURN_LEFT : TURN_RIGHT;
			else if(direction == 'S')
				return (decision <= 9) ? FORWARD : TURN_RIGHT;
			/*else west*/
			return (decision <= 8) ? FORWARD : ( (decision <= 10) ? TURN_LEFT : TURN_RIGHT );
		case 'T' :
			if(direction == 'N')
				return TURN_RIGHT;
			else if(direction == 'W')
				return TURN_LEFT;
			return FORWARD;
		case 't' :
			if(direction == 'N')
				return TURN_LEFT;
			else if(direction == 'E')
				return TURN_RIGHT;
			return FORWARD;
		case 'B' :
			if(direction == 'S')
				return TURN_LEFT;
			else if(direction == 'W')
				return TURN_RIGHT;
			return FORWARD;
		case 'b' :
			if(direction == 'S')
				return TURN_RIGHT;
			else if(direction == 'E')
				return TURN_LEFT;
			return FORWARD;
		default :
			break;
	}
	/*Not along a side or in a corner*/
	if(decision >= 10)
		return TURN_LEFT;
	else if(decision >= 7)
		return TURN_RIGHT;
	return FORWARD;
}
// ======================================================================
// YOUR CODE ENDS
// ======================================================================

