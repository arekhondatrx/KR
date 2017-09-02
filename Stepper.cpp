/*
 * Stepper.cpp
 *
 *  Created on: 25.05.2017
 *      Author: Arek
 */

#include "Stepper.h"

Stepper::Stepper(int8_t stepPin, int8_t dirPin) {
	// TODO Auto-generated constructor stub
	pinMode(stepPin,OUTPUT);
	pinMode(dirPin,OUTPUT);

	time = micros();
	state = true;
	this->stepPin = stepPin;
	this->dirPin = dirPin;
	stepCounter = 1;
}

Stepper::~Stepper() {
	// TODO Auto-generated destructor stub
}

void Stepper::moto(unsigned int delay){

	if(micros() - time > delay)
	{
		digitalWrite(stepPin,state);
		state = !state;
		time = micros();
		stepCounter++;
	}
}

bool Stepper::move(bool direction){

	digitalWrite(dirPin,direction);

	if(stepCounter <= 2 * STEPS_FOR_ONE_MOVE)
	{
		moto();
		return false;
	}
	else
	{
		return true;
	}
}
