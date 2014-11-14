/**								      **\
*									*
*				PROTOCOL HELPER				*
*									*
**/								      \**

#ifndef PROTOCOL_HELPER_H
#define PROTOCOL_HELPER_H

typedef struct send_encap
{
	byte array[5];
}t_encap;


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

#endif
