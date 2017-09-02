/*
 * Manipulators.h
 *
 *  Created on: 26.06.2017
 *      Author: Arek
 */
#include "Stepper.h"
#include <Servo.h>
#include "config.h"

#ifndef MANIPULATORS_H_
#define MANIPULATORS_H_

class Manipulators {
public:
	Manipulators(char *);
	Manipulators();
	virtual ~Manipulators();

public:
	void maniInitialize(int8_t,int8_t,int8_t,int8_t);
	void moveOne(int8_t, bool = true);
	void moveDouble(int8_t, bool = true);
	void moveX(bool = true);
	void moveY(bool = true);
	void moveZ(bool = true);
	bool getColor(uint8_t);

private:
	void xTableChanger(bool = true);
	void yTableChanger(bool = true);
	void zTableChanger(bool = true);
	void upDateAvailableMovesTabel();

	bool getColorStep1();
	bool getColorStep2();
	bool getColorStep3();
	bool getColorStep4();
	bool getColorStep5();
	bool getColorStep6();
	bool getColorStep7();

private:
	Stepper *moto[4];
	Servo servo[4];
	char compare_table[7];
	char *available_moves;
	int8_t adjustment[4];

};

#endif /* MANIPULATORS_H_ */
