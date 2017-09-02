/*
 * Solv.h
 *
 *  Created on: 25.05.2017
 *      Author: Arek
 */

#ifndef SOLV_H_
#define SOLV_H_

#include "Arduino.h"

#include "Config.h"
#include "Manipulators.h"

class Solv  {
public:
	Solv();
	virtual ~Solv();

public:
	void solver(char,char);
	void solvInitialize();
	bool getColor(uint8_t);
	void changeManipulators(char,char,char,char);
	char* getManipulators(){return manipulators;}

private:
	bool leftOrRight(char comand);
	bool checkManipulator(char,bool);
	void singleOrDoubleMove(int,bool,bool);
	bool equalCommand(char,char);

private:
	Manipulators *mani;
	char *manipulators;

};

#endif /* SOLV_H_ */
