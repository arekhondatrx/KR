/*
 * DataMenager.h
 *
 *  Created on: 25.05.2017
 *      Author: Arek
 */

#ifndef DATAMENAGER_H_
#define DATAMENAGER_H_

#include "Arduino.h"

#include "Config.h"

class DataMenager {
public:
	DataMenager();
	virtual ~DataMenager();

public:
	bool dataRecive();
	void copyArray(char* src,char* dst,uint8_t length, uint8_t *dst_index);
	bool newData(){if(data_counter > 0)return true; else return false;}
	void dataSend(String message);
	void initialize();
	char* getData(){return data;}
	void resetFactorData(int index = 0){data[index] = 0;}
	uint8_t getDataCounter(){return data_counter;}
	void resetData(){data_counter = 0; sum_counter = 0;}

private:
	int charToInt(char*, int8_t);
	bool checkSum(char *,uint8_t,int);
	int exponentation(int,int); // I wrote this function by myself because
								//the pow function work uncorrect. For example,
								//when result should be 123 the pow function returned 122.
								//I think this is happening through 8 bits arduino.
private:
	char temp;
	char *data;
	char *sum;
	uint8_t data_counter;
	uint8_t sum_counter;
};

#endif /* DATAMENAGER_H_ */
