/*
 * DataMenager.cpp
 *
 *  Created on: 25.05.2017
 *      Author: Arek
 */

#include "DataMenager.h"

DataMenager::DataMenager() {
	// TODO Auto-generated constructor stub
	temp = 0;
	data_counter = 0;
	sum_counter = 0;
	sum = new char [5];
	data = new char [50];

}

DataMenager::~DataMenager() {
	// TODO Auto-generated destructor stub
	delete [] data;
}

void DataMenager::initialize(){
	Serial.begin(9600);
	Serial.setTimeout(1000);
}

bool DataMenager::dataRecive(){

	data_counter = 0;
	sum_counter = 0;

	while(Serial.available())
	{
		temp = Serial.read();

		if(temp == TERMINATOR)
		{
			do
			{
				temp = Serial.read();

				if(temp > DATA_SIGNS)
				{
					data[data_counter] = temp;
					data_counter++;
				}
				else if(temp == TERMINATOR && sum_counter == 0)
				{
				    temp = 0;
				}
				else if(temp > DOWN_NUMBER && temp < UP_NUMBER)
				{
					sum[sum_counter] = temp;
					sum_counter++;
				}
			}
			while(temp != TERMINATOR);

			//Serial.flush();
			return checkSum(data,data_counter,charToInt(sum,sum_counter));
		}
	}
	/*if(temp == TERMINATOR)
	{
		Serial.println("checksum");
		return checkSum(data,data_counter,charToInt(sum,sum_counter));
	}
	else return false;*/
	return false;
}

void DataMenager::dataSend(String message){

	Serial.println(message);

}

int DataMenager::charToInt(char *tab,int8_t length)
{
	int tmp = 0;
	uint8_t exp = 0;

	for(int i = length-1; i>=0; i--)
	{
	   tmp += (tab[i] - 48) * exponentation(10,exp);
	   exp++;
	}

	return tmp;
}

bool DataMenager::checkSum(char *tab, uint8_t length, int sum){

	int tmp = 0;

	for(int i = 0; i < length; i++)
	{
	   tmp += tab[i];
	}


	if(length == 0) return false;
	else if(data_counter == 0)return false;
	else if(tmp == sum)return true;
	else return false;
}

int DataMenager::exponentation(int number, int expo)
{
  int temp = number;

  for(int i = 0; i < expo-1; i++)
  {
    number *= temp;
  }

  if(expo == 0) return 1;
  else return number;
}

void DataMenager::copyArray(char* src, char* dst,uint8_t length, uint8_t *dst_index){

	for(int i = 0; i<length; i++)
	{
		dst[*dst_index] = src[i];
		(*dst_index)++;
	}
}
