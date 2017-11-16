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
	side = 'B';
	condition = 0;
	prevAction = CLIMB;
	score = 0;
	maxPenalty = -24;
	srand(time(NULL));
	myLocations.push_back(coordinate(0,0,'E', false, false, true));
	X = 0;
	Y = 0;
	for(int i = 0; i < 7; i++)
		for(int j = 0; j < 7; j++)
			allLocations[i][j] = coordinate(i, j, 'U', false, false, false);
	allLocations[0][0].visited = true;
	eWall = 7;
	nWall = 7;
	norSum = easSum = souSum = wesSum = 0;
	timeout = 0;
	moveNumber = 0;
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
	moveNumber++;
	addNewState(bump, breeze, stench);
	neighbors = getNeighbors();
	Action newAction;
	char prevSide = side;
	
	if(glitter) {
		gold = true;
		newAction = GRAB;
	}

	else {
		if(breeze || stench) {
			if(prevAction == CLIMB) {
				allLocations[0][0].stench = myLocations[0].stench = stench;
				allLocations[0][0].breeze = myLocations[0].breeze = breeze;
				newAction = climbOrRandom(breeze || stench);
			}
			else
				newAction = previousSquare();
		}

		else if(gold || score <= maxPenalty)
			newAction = goHome(bump);

		else
			newAction = randomWeightedAction(bump);
	}

	direction = getNewDirection(newAction);
	side = evalSide(newAction);
	prevAction = newAction;

	//printCurrentState(prevSide);
	//printStates();
	//printNeighbors();
	//std::cout << "==============================================" << std::endl;

	if((gold || score <= maxPenalty) && side == 'B')
		return CLIMB;

	return newAction;
	// ======================================================================
	// YOUR CODE ENDS
	// ======================================================================
}

// ======================================================================
// YOUR CODE BEGINS
// ======================================================================
void MyAI::printCurrentState(char prevSide)
{
	std::cout << "X: " << myLocations[myLocations.size()-1].X << ", "
                  << "Y: " << myLocations[myLocations.size()-1].Y << ", "
                  << "Dir: " << myLocations[myLocations.size()-1].direction << ", "
                  << "Breeze: " << myLocations[myLocations.size()-1].breeze << ", "
                  << "Stench: " << myLocations[myLocations.size()-1].stench << ", "
                  << "side " << prevSide << std::endl;
}

void MyAI::printStates()
{
	for(int i = 0; i < myLocations.size(); i++)
		std::cout << "X: " << myLocations[i].X << ", "
                	  << "Y: " << myLocations[i].Y << ", "
                	  << "Dir: " << myLocations[i].direction << ", "
                	  << "Breeze: " << myLocations[i].breeze << ", "
                	  << "Stench: " << myLocations[i].stench << std::endl;
}

void MyAI::printNeighbors()
{
	for(int i = 0; i < neighbors.size(); i++)
		neighbors[i].printCoordinate();
}

Agent::Action MyAI::leftOrForward()
{
	int random = rand() % 10 + 1;
	if(random <= 3)
		return TURN_LEFT;
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
		condition = 1;
		return randomTurn();
	}
	if(condition == 1)
	{
		condition = 2;
		return prevAction;
	}
	condition = 0;
	return FORWARD;
}

Agent::Action MyAI::randomTurn()
{
	bool decision = rand() % 2;
	return decision ? TURN_LEFT : TURN_RIGHT;
}

char MyAI::oppositeDirection(char otherDirection)
{
	if(otherDirection == 'N')
		return 'S';
	if(otherDirection == 'E')
		return 'W';
	if(otherDirection == 'S')
		return 'N';
	/*else west*/
	return 'E';
}

Agent::Action MyAI::ninetyDegAction(char prevDirection)
{
	if(direction == 'N')
		if(prevDirection == 'E')
			return TURN_LEFT;
	if(direction == 'E')
		if(prevDirection == 'S')
			return TURN_LEFT;
	if(direction == 'S')
		if(prevDirection == 'W')
			return TURN_LEFT;
	if(direction == 'W')
		if(prevDirection == 'N')
			return TURN_LEFT;
			
	return TURN_RIGHT;
}

Agent::Action MyAI::goHome(bool wall)
{
	//return randomWeightedAction(wall);
	if(X == 0 && Y == 0)
		return CLIMB;
	coordinate prevState = myLocations[myLocations.size()-2];
	if(direction == oppositeDirection(prevState.direction))
		return FORWARD;
	if(direction == prevState.direction)	
		return randomTurn();
	return ninetyDegAction(prevState.direction);
}

Agent::Action MyAI::randomWeightedAction(bool wall)
{
	/*bool aidedByHeuristic = false;
	if(moveNumber%10 == 0)
		aidedByHeuristic = updateUnexploredRegionScore();
	if(aidedByHeuristic)
		int timeout = 7;
	if(timeout > 0) {
		timeout--;
		return suggestUnexploredDirection();
	}*/
	
	bool foundUnvisited = false;
	coordinate desiredCoordinate;
	for(int i = 0; i < neighbors.size(); i++) {
		if(!neighbors[i].visited) {
			desiredCoordinate = neighbors[i];
			foundUnvisited = true;
			break;
		}
	}


	if(foundUnvisited) {
		//std::cout << "I should have done this." << std::endl;
		char desiredDirection = getDesiredBearing(desiredCoordinate.X, desiredCoordinate.Y);
		//std::cout << "desiredDirection : " << desiredDirection << std::endl;
		return alignDirectionToSuggested(desiredDirection);
	}

	return goHome(wall);
	
	unsigned char decision = rand() % 12 + 1;
	if(wall)
		side = getNewSide();
	return getRandomAction(decision);
}

void MyAI::addNewState(bool wall, bool breeze, bool stench)
{
	updateAllLocations(wall, breeze, stench); //Adds Information about square to map.
	if(prevAction == FORWARD && !wall)
        {
		if(wall == true)
			std::cout << "Why am I in here?" << std::endl;
                if(direction == 'N')
                        Y++;
                else if(direction == 'E')
                        X++;
                else if(direction == 'S')
                        Y--;
                else if(direction == 'W')
			X--;
		if(!(breeze || stench)) {
			coordinate newState = coordinate(X, Y, direction, breeze, stench, true);
			bool add = true;
			int pos = 0;
			for(pos; pos < myLocations.size(); pos++) {
				if(newState == myLocations[pos])
				{
					add = false;
					break;
				}
			}
			if(add == false)
				myLocations.erase(myLocations.begin()+pos+1, myLocations.end());
			else
				myLocations.push_back(coordinate(X, Y, direction, breeze, stench, true));
        	}
	}
    else
        myLocations[myLocations.size()-1].direction = direction;
}

std::vector<coordinate> MyAI::getNeighbors()
{
	std::vector<coordinate> newNeighbors;
	if(X != 0)
		newNeighbors.push_back(coordinate(allLocations[X-1][Y]));
	if(X != eWall)
		newNeighbors.push_back(coordinate(allLocations[X+1][Y]));
	if(Y != 0)
		newNeighbors.push_back(coordinate(allLocations[X][Y-1]));
	if(Y != nWall)
		newNeighbors.push_back(coordinate(allLocations[X][Y+1]));
	sort(newNeighbors.rbegin(), newNeighbors.rend());
	return newNeighbors;
}

void MyAI::updateAllLocations(bool wall, bool breeze, bool stench)
{
	if(wall)
		if(direction == 'N')
			nWall = Y;
		else if(direction == 'E')
			eWall = X;


	allLocations[X][Y].breeze = breeze;
	allLocations[X][Y].stench = stench;
	allLocations[X][Y].visited = true;
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
			if(prevAction == CLIMB) {
				side = 'B';
				return climbOrRandom(false);
			}
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

Agent::Action MyAI::ninetyDegAlignAction(char suggestedDirection)
{
	if(suggestedDirection == 'N') {
		if(direction == 'E')
			return TURN_LEFT;
		if(direction == 'W')
			return TURN_RIGHT;
	}
	else if(suggestedDirection == 'E') {
		if(direction == 'S')
			return TURN_LEFT;
		if(direction == 'N')
			return TURN_RIGHT;
	}
	else if(suggestedDirection == 'S') {
		if(direction == 'W')
			return TURN_LEFT;
		if(direction == 'E')
			return TURN_RIGHT;
	}
	else /*suggestedDirection == 'W'*/ {
		if(direction == 'N')
			return TURN_LEFT;
		if(direction == 'S')
			return TURN_RIGHT;
	}
	/*In case of bug, return something to at least continue*/
	return FORWARD;
}

Agent::Action MyAI::alignDirectionToSuggested(char suggestedDirection)
{
	if(direction == suggestedDirection)
		return FORWARD;
	if(oppositeDirection(suggestedDirection) == direction)
		return randomTurn();
	return ninetyDegAlignAction(suggestedDirection);
}

char MyAI::getDesiredBearing(unsigned int desiredX, unsigned int desiredY)
{
	if(desiredX == X+1)
		return 'E';
	if(desiredX == X-1)
		return 'W';
	if(desiredY == Y+1)
		return 'N';
	/*else*(desiredY == Y-1)*/
	return 'S';
}

char MyAI::getSuggestedDirection()
{
	if(norSum > souSum) {
		if(norSum > easSum) {
			if(norSum > wesSum)
				return 'N';
			return 'W';
		}
		if(easSum > wesSum)
			return 'E';
		return 'W';
	}
	else /*souSum >= norSum*/ {
		if(souSum > easSum) {
			if(souSum > wesSum)
				return 'S';
			return 'W';
		}
		if(easSum > wesSum)
			return 'E';
		return 'W';
	}
}

Agent::Action MyAI::suggestUnexploredDirection()
{
	char suggestedDirection = getSuggestedDirection();

	return alignDirectionToSuggested(suggestedDirection);
}

bool MyAI::updateUnexploredRegionScore()
{
	norSum = easSum = souSum = wesSum = 0;
	
	for(int i = 0; i < 7; i++){
		if(eWall && i == eWall)
			continue;
		for(int j = 0; j < 7; j++){
			if(nWall && j == nWall)
				continue;
			if( !(allLocations[i][j].visited) ){
				if(i > X)
					easSum++;
				else if(i < X)
					wesSum++;
				if(j > Y)
					norSum++;
				else if(j < Y)
					souSum++;
			}
		}
	}
	
	if(norSum-2 <= souSum && norSum+2 >= souSum)
		if(wesSum-2 <= easSum && wesSum+2 >= easSum)
			return false;

	return true;
}
// ======================================================================
// YOUR CODE ENDS
// ======================================================================

