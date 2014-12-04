// =========================================================================
// 			THIS IS A TEST PROTOCOL PROGRAM
// Its goal is to test the network modules and verify the data integrity.
// (On Arduino reception side)
// =========================================================================

#include <Arduino.h>

#include "protocol_helper.h"

typedef struct control
{
	Network_manager *net;
	bool start;
	uint8_t state;
}control_t;

control_t Controller;

t_encap sending_frame;

String mystring = "";

void setup()
{
	// Setting up environment values
	Controller.start = false;
	Controller.state = -1;	

	// Starting network module
	Serial.begin(9600);
	
	// Send handcheck : frame : controller Ready
	sending_frame = encap_ready();
	char * t = sending_frame.array;
	uint8_t bsent = Serial.write(t,5);
}

uint16_t cpt = 0;

void loop()
{
	// On récupère l'entrée utilisateur
	int value2;
  
  	while(Serial.available() > 0)
  	{
	  // We get the entry in 8bytes max.
   	  byte value[7]; 
          uint8_t ret = Serial.readBytes(value, 7);
    	  
	  Serial.print("Frame read : ");
	  Serial.println(++cpt,DEC);

	  for (int i=0;i<7;i++)
		Serial.print(value[i] + ':');
	  Serial.println("End_Of_Frame");
	}
}


