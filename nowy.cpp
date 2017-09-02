// Do not remove the include below
#include "nowy.h"
#include "DataMenager.h"
#include "Solv.h"
#include <Servo.h>
#include "Config.h"

DataMenager conection;
Solv solver;
// :RRUULLDDBBFFrruullddbbffRRUULLDDBBFFrruullddbbffXX:4520:
//char tablica_testowa[15]={'F','L','B','R','R','R','r','l','U','U','u','B','f','X','D'};
char *tab_moves;
uint8_t* index;
uint8_t move_counter;
char end_data;
uint8_t get_color_step;
String doneMoves = "";

uint8_t calculateDoneMovePercentage(uint8_t moves, uint8_t done)
{
	float temp = 0;
	temp = float(done) / float(moves);
	temp = temp * 100;
	return uint8_t(temp);
}

void onOff(bool on_off)
{
	digitalWrite(A4,!on_off);
	digitalWrite(5,!on_off);
	digitalWrite(12,!on_off);
	digitalWrite(13,!on_off);
}

void setup()
{
	pinMode(A4,OUTPUT);
	pinMode(5,OUTPUT);
	pinMode(12,OUTPUT);
	pinMode(13,OUTPUT);

	onOff(false);

	solver.solvInitialize();
	conection.initialize();


	tab_moves = new char [MAX_SIZE_TAB_MOVES];
	index = new uint8_t;
	*index = 0;
	move_counter = 0;
	end_data = 0;
	get_color_step = 0;
}
bool serial = false;

void loop()
{
// Menu /////////////////////////////////////////////////////////////////////
	if(conection.dataRecive() == true)
	{
		if(conection.getData()[0] == START)
		{
			if(conection.newData() == true)
			{
				end_data = END_DATA;
				//tab_moves[(*index)] = START;
				conection.dataSend("Start");
			}
		}
		else if(conection.getData()[0] == PAUSE)
		{
			if(conection.newData() == true)
			{
				conection.dataSend("Pause");
				end_data = 0;
			}
		}
		else if(conection.getData()[0] == STOP)
		{
			if(conection.newData() == true)
			{
				end_data = 0;
				(*index) = 0;
				move_counter = 0;
				conection.resetData();
				onOff(false);
				conection.dataSend("Stop");
			}
		}
		else if(conection.getData()[0] == GET_COLOR)
		{
			if(get_color_step <= 7)
			{
				get_color_step++;
				onOff(true);
				solver.getColor(get_color_step);
				delay(GET_COLOR_DELAY);
				conection.resetFactorData();
				conection.dataSend("<");
			}
			else
			{
				get_color_step = 0;
				conection.dataSend(">");
			}
			//conection.dataSend("Get color");
		}
		else if(conection.newData() == true)
		{
			conection.copyArray(conection.getData(),tab_moves,conection.getDataCounter(),index);
			conection.dataSend(String(*index));
			conection.dataSend("OK");
			//Serial.flush();
		}

	}
//////////////////////////////////////////////////////////////////////////////////////

// Solve /////////////////////////////////////////////////////////////////////////////
	else if(end_data == END_DATA)
	{
		onOff(true);


		if((*index) != move_counter)//tab_moves[move_counter] != END_DATA
		{
			solver.solver(tab_moves[move_counter], tab_moves[move_counter + 1]);
			//conection.dataSend(String(tab_moves[move_counter]));

			if(tab_moves[move_counter] == tab_moves[move_counter + 1])
			{
				doneMoves = "M2" + String(tab_moves[move_counter]);
				Serial.flush();
				conection.dataSend(doneMoves);
				move_counter +=2;
			}
			else
			{
				doneMoves = "M1" + String(tab_moves[move_counter]);
				Serial.flush();
				conection.dataSend(doneMoves);
				move_counter++;
			}
		}
		doneMoves = "%" + String(calculateDoneMovePercentage((*index),move_counter));
		//doneMoves = "M" + String(move_counter);
		conection.dataSend(doneMoves);

		if((*index) == move_counter)
		{
			conection.dataSend("Zrobione :D");
			end_data = 0;
		}
	}
//////////////////////////////////////////////////////////////////////////////////////
}
