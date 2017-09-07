/*
 * Manipulators.cpp
 *
 *  Created on: 26.06.2017
 *      Author: Arek
 */

#include "Manipulators.h"

Manipulators::Manipulators(char *tab) {
	// TODO Auto-generated constructor stub
	available_moves = tab;
	compare_table[0] = 'L';
	compare_table[1] = 'U';
	compare_table[2] = 'R';
	compare_table[3] = 'D';
	compare_table[4] = 'B';
	compare_table[5] = 'F';


}

Manipulators::Manipulators() {
	// TODO Auto-generated constructor stub
	compare_table[0] = 'L';
	compare_table[1] = 'U';
	compare_table[2] = 'R';
	compare_table[3] = 'D';
	compare_table[4] = 'B';
	compare_table[5] = 'F';
	available_moves = NULL;
}

Manipulators::~Manipulators() {
	// TODO Auto-generated destructor stub
}

void Manipulators::maniInitialize(int8_t a1,int8_t a2,int8_t a3,int8_t a4) // separate function, because servo must be initialize in setup
{
	servo[0].attach(S1);
	servo[1].attach(S2);
	servo[2].attach(S3);
	servo[3].attach(S4);

	adjustment[0] = a1;
	adjustment[1] = a2;
	adjustment[2] = a3;
	adjustment[3] = a4;

	this->moto[0] = new Stepper(STEP1,DIR1);
	this->moto[1] = new Stepper(STEP2,DIR2);
	this->moto[2] = new Stepper(STEP3,DIR3);
	this->moto[3] = new Stepper(STEP4,DIR4);

	for(int i = 0; i<4; i++)
	{
	servo[i].write(SERVO_CLOSE + adjustment[i]);
	}
	delay(SERVO_DELAY);
	delay(SERVO_DELAY);
}

bool Manipulators::getColor(uint8_t step)
{
	switch(step)
	{
	case 1:
		return this->getColorStep1();

	case 2:
		return this->getColorStep2();

	case 3:
		return this->getColorStep3();

	case 4:
		return this->getColorStep4();

	case 5:
		return this->getColorStep5();

	case 6:
		return this->getColorStep6();

	case 7:
		return this->getColorStep7();

	default:
		return false;
	}
}

void Manipulators::moveOne(int8_t mNumber,bool direction){

	while(this->moto[mNumber]->move(direction) == false);
	this->moto[mNumber]->resetStepCounter();

	servo[mNumber].write(SERVO_OPEN);
	delay(SERVO_DELAY);

	while(this->moto[mNumber]->move(!direction) == false);
	this->moto[mNumber]->resetStepCounter();

	servo[mNumber].write(SERVO_CLOSE + adjustment[mNumber]);
	delay(SERVO_DELAY);
}

void Manipulators::moveDouble(int8_t mNumber,bool direction){

	while(this->moto[mNumber]->move(direction) == false);
	this->moto[mNumber]->resetStepCounter();
	while(this->moto[mNumber]->move(direction) == false);
	this->moto[mNumber]->resetStepCounter();

	servo[mNumber].write(SERVO_OPEN);
	delay(SERVO_DELAY);

	while(this->moto[mNumber]->move(!direction) == false);
	this->moto[mNumber]->resetStepCounter();
	while(this->moto[mNumber]->move(!direction) == false);
	this->moto[mNumber]->resetStepCounter();

	servo[mNumber].write(SERVO_CLOSE + adjustment[mNumber]);
	delay(SERVO_DELAY);

}

void Manipulators::moveZ(bool direction)
{
	servo[1].write(SERVO_OPEN);
	servo[3].write(SERVO_OPEN);
	delay(SERVO_DELAY);

	while(this->moto[0]->move(direction) == false &&
		  this->moto[2]->move(!direction) == false);
	this->moto[0]->resetStepCounter();
	this->moto[2]->resetStepCounter();

	servo[1].write(SERVO_CLOSE + adjustment[1]);
	servo[3].write(SERVO_CLOSE + adjustment[3]);
	delay(SERVO_DELAY);

	servo[0].write(SERVO_OPEN);
	servo[2].write(SERVO_OPEN);
	delay(SERVO_DELAY);

	while(this->moto[0]->move(!direction) == false &&
		  this->moto[2]->move(direction) == false);
	this->moto[0]->resetStepCounter();
	this->moto[2]->resetStepCounter();

	servo[0].write(SERVO_CLOSE + adjustment[0]);
	servo[2].write(SERVO_CLOSE + adjustment[2]);
	delay(SERVO_DELAY);

	zTableChanger(direction);//x
}

void Manipulators::moveY(bool direction)
{
	moveX(direction);
	moveZ(direction);
	moveX(!direction);
}

void Manipulators::moveX(bool direction)
{
	servo[0].write(SERVO_OPEN);
	servo[2].write(SERVO_OPEN);
	delay(SERVO_DELAY);

	while(this->moto[1]->move(direction) == false &&
		  this->moto[3]->move(!direction) == false);
	this->moto[1]->resetStepCounter();
	this->moto[3]->resetStepCounter();

	servo[0].write(SERVO_CLOSE + adjustment[0]);
	servo[2].write(SERVO_CLOSE + adjustment[2]);
	delay(SERVO_DELAY);

	servo[1].write(SERVO_OPEN);
	servo[3].write(SERVO_OPEN);
	delay(SERVO_DELAY);

	while(this->moto[1]->move(!direction) == false &&
		  this->moto[3]->move(direction) == false);
	this->moto[1]->resetStepCounter();
	this->moto[3]->resetStepCounter();

	servo[1].write(SERVO_CLOSE + adjustment[1]);
	servo[3].write(SERVO_CLOSE + adjustment[3]);
	delay(SERVO_DELAY);

	xTableChanger(direction);//z
}


void Manipulators::zTableChanger(bool direction)
{
	if(direction == true)
	{
		compare_table[6] = compare_table[0];
		compare_table[0] = compare_table[1];
		compare_table[1] = compare_table[2];
		compare_table[2] = compare_table[3];
		compare_table[3] = compare_table[6];
	}
	if(direction == false)
	{
		compare_table[6] = compare_table[0];
		compare_table[0] = compare_table[3];
		compare_table[3] = compare_table[2];
		compare_table[2] = compare_table[1];
		compare_table[1] = compare_table[6];
	}
	upDateAvailableMovesTabel();

}

void Manipulators::yTableChanger(bool direction)
{
	if(direction == true)
	{
		compare_table[6] = compare_table[0];
		compare_table[0] = compare_table[5];
		compare_table[5] = compare_table[2];
		compare_table[2] = compare_table[4];
		compare_table[4] = compare_table[6];
	}
	if(direction == false)
	{
		compare_table[6] = compare_table[0];
		compare_table[0] = compare_table[4];
		compare_table[4] = compare_table[2];
		compare_table[2] = compare_table[5];
		compare_table[5] = compare_table[6];
	}
	upDateAvailableMovesTabel();
}

void Manipulators::xTableChanger(bool direction)
{
	if(direction == true)
	{
		compare_table[6] = compare_table[5];
		compare_table[5] = compare_table[1];
		compare_table[1] = compare_table[4];
		compare_table[4] = compare_table[3];
		compare_table[3] = compare_table[6];
	}
	if(direction == false)
	{
		compare_table[6] = compare_table[4];
		compare_table[4] = compare_table[1];
		compare_table[1] = compare_table[5];
		compare_table[5] = compare_table[3];
		compare_table[3] = compare_table[6];
	}
	upDateAvailableMovesTabel();

}

void Manipulators::upDateAvailableMovesTabel()
{
	available_moves[0] = compare_table[0];
	available_moves[1] = compare_table[2];
	available_moves[2] = compare_table[4];
	available_moves[3] = compare_table[5];
}

bool Manipulators::getColorStep1()
{
	servo[1].write(SERVO_OPEN);
	servo[3].write(SERVO_OPEN);
	delay(SERVO_DELAY);

	while(this->moto[0]->move(true) == false &&
		  this->moto[2]->move(false) == false);
	this->moto[0]->resetStepCounter();
	this->moto[2]->resetStepCounter();

	return true;
}

bool Manipulators::getColorStep2()
{
	while(this->moto[0]->move(false) == false &&
		  this->moto[2]->move(true) == false);
	this->moto[0]->resetStepCounter();
	this->moto[2]->resetStepCounter();

	while(this->moto[0]->move(false) == false &&
		  this->moto[2]->move(true) == false);
	this->moto[0]->resetStepCounter();
	this->moto[2]->resetStepCounter();

	return true;
}

bool Manipulators::getColorStep3()
{
	servo[1].write(SERVO_CLOSE + adjustment[1]);
	servo[3].write(SERVO_CLOSE + adjustment[3]);
	delay(SERVO_DELAY);

	servo[0].write(SERVO_OPEN);
	servo[2].write(SERVO_OPEN);
	delay(SERVO_DELAY);

	while(this->moto[0]->move(true) == false &&
		  this->moto[2]->move(false) == false);
	this->moto[0]->resetStepCounter();
	this->moto[2]->resetStepCounter();

	while(this->moto[1]->move(true) == false &&
		  this->moto[3]->move(false) == false);
	this->moto[1]->resetStepCounter();
	this->moto[3]->resetStepCounter();

	return true;
}

bool Manipulators::getColorStep4()
{
	while(this->moto[1]->move(false) == false &&
		  this->moto[3]->move(true) == false);
	this->moto[1]->resetStepCounter();
	this->moto[3]->resetStepCounter();

	while(this->moto[1]->move(false) == false &&
		  this->moto[3]->move(true) == false);
	this->moto[1]->resetStepCounter();
	this->moto[3]->resetStepCounter();

	return true;
}

bool Manipulators::getColorStep5()
{
	servo[0].write(SERVO_CLOSE + adjustment[0]);
	servo[2].write(SERVO_CLOSE + adjustment[2]);
	delay(SERVO_DELAY);

	servo[1].write(SERVO_OPEN);
	servo[3].write(SERVO_OPEN);
	delay(SERVO_DELAY);

	while(this->moto[1]->move(true) == false &&
		  this->moto[3]->move(false) == false);
	this->moto[1]->resetStepCounter();
	this->moto[3]->resetStepCounter();

	while(this->moto[0]->move(false) == false &&
		  this->moto[2]->move(true) == false);
	this->moto[0]->resetStepCounter();
	this->moto[2]->resetStepCounter();

	return true;
}

bool Manipulators::getColorStep6()
{
	while(this->moto[0]->move(true) == false &&
		  this->moto[2]->move(false) == false);
	this->moto[0]->resetStepCounter();
	this->moto[2]->resetStepCounter();

	while(this->moto[0]->move(true) == false &&
		  this->moto[2]->move(false) == false);
	this->moto[0]->resetStepCounter();
	this->moto[2]->resetStepCounter();

	return true;
}

bool Manipulators::getColorStep7()
{
	while(this->moto[0]->move(false) == false &&
		  this->moto[2]->move(true) == false);
	this->moto[0]->resetStepCounter();
	this->moto[2]->resetStepCounter();

	servo[1].write(SERVO_CLOSE + adjustment[1]);
	servo[3].write(SERVO_CLOSE + adjustment[3]);
	delay(SERVO_DELAY);

	servo[0].write(SERVO_OPEN);
	servo[2].write(SERVO_OPEN);
	delay(SERVO_DELAY);

	while(this->moto[1]->move(false) == false &&
		  this->moto[3]->move(true) == false);
		this->moto[1]->resetStepCounter();
		this->moto[3]->resetStepCounter();

	servo[0].write(SERVO_CLOSE + adjustment[0]);
	servo[2].write(SERVO_CLOSE + adjustment[2]);
	delay(SERVO_DELAY);

	servo[1].write(SERVO_OPEN);
	servo[3].write(SERVO_OPEN);
	delay(SERVO_DELAY);

	while(this->moto[0]->move(true) == false &&
		  this->moto[2]->move(false) == false);
		this->moto[0]->resetStepCounter();
		this->moto[2]->resetStepCounter();

	servo[1].write(SERVO_CLOSE + adjustment[1]);
	servo[3].write(SERVO_CLOSE + adjustment[3]);
	delay(SERVO_DELAY);

	servo[0].write(SERVO_OPEN);
	servo[2].write(SERVO_OPEN);
	delay(SERVO_DELAY);

	while(this->moto[0]->move(true) == false &&
		  this->moto[2]->move(false) == false);
	this->moto[0]->resetStepCounter();
    this->moto[2]->resetStepCounter();

	servo[0].write(SERVO_CLOSE + adjustment[0]);
	servo[2].write(SERVO_CLOSE + adjustment[2]);
	delay(SERVO_DELAY);

	return true;
}
