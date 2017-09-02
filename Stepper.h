/*
 * Stepper.h
 *
 *  Created on: 25.05.2017
 *      Author: Arek
 */

#ifndef STEPPER_H_
#define STEPPER_H_

#include "Arduino.h"

#include "Config.h"


class Stepper {
public:
	Stepper(int8_t, int8_t);
	virtual ~Stepper();

public:
	bool move(bool direction = true);
	void resetStepCounter(){stepCounter = 1;}
	int getStepperCounter(){return stepCounter;}

private:
	void moto(unsigned int delay = STEP_DELAY);

private:
	unsigned long time;
	bool state;
	int8_t stepPin;
	int8_t dirPin;
	int stepCounter;
};

#endif /* STEPPER_H_ */
