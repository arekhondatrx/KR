/*
 * Solv.cpp
 *
 *  Created on: 25.05.2017
 *      Author: Arek
 */

#include "Solv.h"

Solv::Solv() {

	manipulators = new char[4];
	this->changeManipulators('F', 'R', 'B', 'L');
	this->mani = new Manipulators(manipulators);
}

Solv::~Solv() {


}

void Solv::solvInitialize()
{
	this->mani->maniInitialize(0,-4,-7,-5);

}

bool Solv::getColor(uint8_t step)
{
	return this->mani->getColor(step);
}

void Solv::changeManipulators(char m1, char m2,char m3, char m4)
{
	this->manipulators[0] = m1; // np. F
	this->manipulators[1] = m2; // np. L
	this->manipulators[2] = m3; // np. B
	this->manipulators[3] = m4; // np. R
}

void Solv::solver(char command, char next_command)
{
	switch(command)
	{
	case 'X':
		this->mani->moveX(false);
		break;
	case 'x':
		this->mani->moveX(true);
		break;
	case 'Y':
		this->mani->moveY(false);
		break;
	case 'y':
		this->mani->moveY(true);
		break;
	case 'Z':
		this->mani->moveZ(false);
		break;
	case 'z':
		this->mani->moveZ(true);
		break;
	default:
		this->checkManipulator(command, equalCommand(command,next_command));
		break;
	}
}

bool Solv::checkManipulator(char command, bool one_move)// turn on suitable manipulator
{
	for(int i = 0; i<4; i++)
	{
		if(this->manipulators[i] == command ||
		   this->manipulators[i] == char(command - 32))
		{
			switch (i)
			{
			case 0:
				singleOrDoubleMove(i,leftOrRight(command),one_move);
				return true;
			case 1:
				singleOrDoubleMove(i,leftOrRight(command),one_move);
				return true;
			case 2:
				singleOrDoubleMove(i,leftOrRight(command),one_move);
				return true;
			case 3:
				singleOrDoubleMove(i,leftOrRight(command),one_move);
				return true;
			default:
				return false;
			}
		}
		else
		{
			if(i == 3)// if this condition is true, that means should rotate x axis to able other manipulators
			{
				this->mani->moveX(true);
				i = 0;
			}
		}
	}
	return false;
}

void Solv::singleOrDoubleMove(int mani_nr, bool direction, bool s_or_d) // checking double moves
{
	if(s_or_d == true)
	{
		this->mani->moveOne(mani_nr, direction);
	}
	else
	{
		this->mani->moveDouble(mani_nr, direction);
	}
}

bool Solv::leftOrRight(char command) // checking direction
{
	if(command < 97) return false;
	else return true;
}

bool Solv::equalCommand(char c1, char c2) // checking the equality of two commands
{
	if(c1 == c2) return false;
	else return true;
}
