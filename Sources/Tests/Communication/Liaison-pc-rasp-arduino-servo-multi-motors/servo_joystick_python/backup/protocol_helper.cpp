#include "protocol_helper.h"


/**
*	\brief encap_acq_data, encaps the acquisition data in format
*
*/
t_encap encap_acq_data(byte dx,byte dy,byte gz)
{
	t_encap t;

	t.array[0] = (byte)0;
	t.array[1] = dx;
	t.array[2] = dy;
	t.array[3] = gz;
	t.array[4] = '\n';

	return t;
}

/**
*	\brief encap_ready, encaps the ready packet
*
*/
t_encap encap_ready()
{
	t_encap t;

	t.array[0] = (byte)0;
	t.array[1] = 0;
	t.array[2] = 0;
	t.array[3] = 0;
	t.array[4] = '\n';
	
	return t;
}

/**
*	\brief encap_battery_data, encaps the battery data in format
*
*/
t_encap encap_battery_data(byte b1, byte b2)
{
	t_encap t;

	t.array[0] = (byte)2;
	t.array[1] = b1;
	t.array[2] = b2;
	t.array[3] = 0;
	t.array[4] = '\n';
	
	return t;
}

/**
*	\brief extract_data, stores every bytes into an encap type variable
*	\param frame : array of 5 bytes aka a frame.
*/
uint8_t get_frame_type(byte *frame)
{
	return (uint8_t)frame[0];
}

t_frame_bytes extract_data_bytes(byte *frame)
{
	t_frame_bytes extract;
	extract.type = frame[0];
	extract.array[0] = frame[0];
	switch(extract.type)
	{
		case 0 : // State and Start frame !
			// Typages et initialisations 
			extract.array[2] = (uint8_t)frame[2]; // Start 
			extract.array[1] = (uint8_t)frame[1]; // State
		break;
		case 1 : // Stop signal frame
			extract.array[1] = (uint8_t)frame[1];
		break;
		case 2 : // Move frame
			for(uint8_t i=1;i<5;i++)
				extract.array[i] = (uint8_t)frame[i];
		break;
		case 3 : // Power frame
			for(uint8_t i=1;i<5;i++)
				extract.array[i] = (uint8_t)frame[i];
		break;
	}

	return extract;
}

t_frame_doubles extract_data_doubles(byte *frame)
{
	t_frame_doubles extract;
	extract.type = frame[0];
	// Point frame
	uint16_t t = frame[1] << 8;
	t = t | frame[2];
	extract.array[0] = (double)t;
	t = frame[2] << 8; 
	t |= frame[3];
	extract.array[1] = (double)t;
	return extract;
}


/*
t_recept_encap extract_data(byte*frame)
{
	// STEP 1 : extraction de l'ID
	uint8_t frame_type = (uint8_t)frame[0];
	uint8_t elem = 0;
	void * array = NULL;
	switch(frame_type)
	{
		case 0 : // State and Start frame !
			// Typages et initialisations 
			array = new uint8_t[2]();
			array[0] = (uint8_t)frame[1]; // Start 
			array[0] = (uint8_t)frame[2]; // State
			elem = 2;
		break;
		case 1 : // Stop signal frame
			array = (*uint8_t)frame[1];
			elem = 1;
		break;
		case 2 : // Move frame
			array = new uint8_t[5]();
			for(uint8_t i=0;i<5;i++)
				array[i] = (uint8_t)frame[i];
			elem = 5;
		break;
		case 3 : // Power frame
			array = new uint8_t[5]();
			for(uint8_t i=0;i<5;i++)
				array[i] = (uint8_t)frame[i];
			elem = 5;
		break;
		case 4 : // Point frame
			uint16_t t = frame[0] << 8;
			t = t | frame[1];
			array = new double[2]();
			array[0] = (double)t;
			t = frame[2] << 8; 
			t |= frame[3];
			array[1] = (double)t;
			elem = 2;
		break;
		default : // Error frame
			uint8_t id = -1;
			array = NULL;
			elem = -1;
		break;
	}
	t_recept_encap encap;
	encap.type = frame_type;
	encap.Elements = elem;
	encap.data = array;	
}*/






