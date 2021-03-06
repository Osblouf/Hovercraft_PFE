/**								      **\
*									*
*				PROTOCOL HELPER				*
*									*
**/								    //\**

#ifndef PROTOCOL_HELPER_H
#define PROTOCOL_HELPER_H

#include <Arduino.h>

/*
	Frame structure :
	ID|- |- |- |- |- |
  byte :0 |1 |2 |3 |4 |5 |	
*/

/**
*	Send/Extract : Encap structur
*
*/
typedef struct send_encap
{
	byte array[5];
}t_encap;

typedef struct recept_encap
{
	uint8_t type; // Frame ID and type
	void * data; // Elements Array
	uint8_t Elements; // Number elements
}t_recept_encap;

// ========================================================================
//		FRAME DEFINITION ZONE
// This is totally temporary, waiting to find a better solution to c++ 
// void * compilers' problem.
// ========================================================================
 
/* This defines an unsigned integer 8 bits composed frame.
// (corresponding to ID : 0,1,2 & 3)
*/
typedef struct recept_frame_bytes
{
	uint8_t type;
	uint8_t array[5];
}t_frame_bytes;

/* This defines a double composed frame.
// (corresponds to ID : 4)
*/
typedef struct recept_frame_doubles
{
	uint8_t type;
	double array[2];
}t_frame_doubles;

// ========================================================================
//		SENDING PROTOCOL HELPER (arduino side)
//	Features :
//		-> Ready Frame
//		-> Data Frame
//		-> Battery Status Frame 
// ========================================================================
/**
*	\brief encap_acq_data, encaps the acquisition data in format
*
*/
t_encap encap_acq_data(byte, byte, byte);

/**
*	\brief encap_ready, encaps the ready packet
*
*/
t_encap encap_ready();


/**
*	\brief encap_battery_data, encaps the battery data in format
*
*/
t_encap encap_battery_data(byte, byte);

// ========================================================================
//		EXTRACTION PROTOCOL HELPER (Arduino side)
//	Features :
//		-> State & Start Frame id : 0
//		-> Stop Frame : id 1
//		-> Move Frame : id 2
//		-> Power Frame : id 3
//		-> Point Frame : id 4
//	/!\ : Frame size = 5 bytes
// ========================================================================

/**
*	\brief extract_data, stores every bytes into an encap type variable
*	\param frame : array of 5 bytes aka a frame.
*/
t_recept_encap extract_data(byte*frame);


// ========================================================================
//		ENCAPSULATION PROTOCOL HELPER (Rasp side)
//	Features :
//		-> State & Start Frame id : 0
//		-> Stop Frame : id 1
//		-> Move Frame : id 2
//		-> Power Frame : id 3
//		-> Point Frame : id 4
//	/!\ : Frame size = 5 bytes
// ========================================================================

/**
*	\brief encap_special_frames : encaps raspberry side frames
*	\param uint8_t : frame type wanted
*	\param byte *  : 
* 	################################### TODO
*/
t_encap encap_special_frames(uint8_t, byte*, uint8_t);


// ========================================================================
//		EXTRACTION PROTOCOL HELPER (Raspberry PI side)
//	Features :
//		-> Ready Frame; id 0
//		-> Data Frame; id 1
//		-> Battery Status Frame; id 2
//	/!\ : Frame size = 5 bytes
// ========================================================================
// # TODO 
// t_recept_encap extract_data_computer(byte *frame); 

uint8_t get_frame_type(byte *);

t_frame_bytes extract_data_bytes(byte *);

t_frame_doubles extract_data_doubles(byte *);

#endif
