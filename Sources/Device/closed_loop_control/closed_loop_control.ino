/*  /!\Arduino 
	CLOSED LOOP CONTROL MAIN PROGRAM : Eq. Autopilot
	For Hovercraft using 4 lateral motors
*/

#include <Arduino.h>

// Perso libraries
#include "network_manager.h"
#include "pid_manager.h"
#include "scheduler.h"
#include "motor_handler.h"
#include "acq_handler.h"

#define DBG

typedef struct control
{
	Motor_handler *motor;
	PID_manager *pid;
	Network_manager *net;
	Scheduler *scheduler;
	ACQ_handler *acq;
	bool start;
	uint8_t state;
}control_t;

control_t controller;

void Control_Process_Com();
void Control_Process_Acq();
void Control_Process_MotorEncoder();
void Control_Process_Decision();

void setup()
{
	// Static inits
	controller.start = false;
	controller.state = -1; // No state

	// Network init
	controller.net = new Network_manager(9600);

	// Motors Init
	controller.motor = new Motor_handler(0,180,0,2,4,6,8);

	// ACQ Handler init
	controller.acq = new ACQ_handler();

	// PID manager Init
	controller.pid = new PID_manager();

	// Scheduler
	controller.scheduler = new Scheduler();

	// Send OK ready signal to Raspberry PI
	controller.net->send_data_to_computer(0xFF); // Sends  : all set !
	#ifdef DBG
		controller.net->send_dbg_message_to_computer("Init finished.");
	#endif
}


///// LOOP IS CONSTRUCTED AS FOLLOW :
/*
	Time :
Div1 : ACQ process, readings taken from ADNS2610 & MPU6050 (12ms)
Div1 : Motor Update : we need to continuously reset the motor process
Div2 : PID computation (every 24 ms) : ensures stability
Div1 : Network communication : send and receive orders. Ensures safety. 
*/
void loop()
{

	// Network Manager
	controller.net->run_the_magic();
	Control_Process_Com();	
	
	while(controller.start && controller.state != -1)
	{
		// Com reading
		controller.net->run_the_magic();
		
		// Up motors
		controller.motor->run_the_magic();		

		// State gestionary
		stateGestionary();

		// Up motors
		controller.motor->run_the_magic();

		// Loop Regulation
		controller.scheduler->regulate_loop();
	}
}

void Control_Process_Com()
{
	// TO BE IMPLEMENTED
}

void Control_Process_Acq()
{
	// TO BE IMPLEMENTED
}

void Control_Process_MotorEncoder()
{
	// TO BE IMPLEMENTED
}

void Control_Process_Decision()
{
	// TO BE IMPLEMENTED
}

/**
*	\Brief stateGestionary : real main loop
*
*/
void stateGestionary()
{
	switch(controller.state)
	{
		case 0 : // Manual + PID
			// ACQ process...
			controller.acq->run_the_magic();
			Control_Process_Acq();

			// Up motors
			controller.motor->run_the_magic();

			// PID manager process...
			controller.pid->run_the_magic();
			Control_Process_MotorEncoder();		
		break;

		case 1 : // Manual Pure
			// Not usefull at the moment
		break;	

		case 2 : // Autonomous Process
			
			// ACQ process...
			controller.acq->run_the_magic();
			Control_Process_Acq();

			// Up motors
			controller.motor->run_the_magic();

			// PID manager process...
			controller.pid->run_the_magic();
			Control_Process_Decision();
			Control_Process_MotorEncoder();	

			// Up motors
			controller.motor->run_the_magic();			
		break;

		default :
		break;
	}
}


