
#include "network_manager.h"


		Network_manager::Network_manager(int baud)
		{
			Serial.begin(baud);
			Serial.flush();
			Serial.setTimeout(TIMEOUT); // See .h for details
			this->last_extraction.type = -1;
			for(int i=0;i<10;i++)
				this->encapsulation_stack[i].array[0] = 255;
		}
	
		void Network_manager :: run_the_magic()
		{
			// Reading data :
			Serial.flush();
    			char value[7];
    			Serial.readBytes(value,7);
    			this->last_extraction = extract_data_bytes((byte*)value);
		}
		
	int Network_manager :: get_last_frame_id()
	{
		return this->last_extraction.type;	
	}
		
	/**
	*	\brief get_array : returns data frame array
	*	\return uint8_t : contains 6 items.
	*
	*/
	uint8_t * Network_manager :: get_array()
	{
		return this->last_extraction.array;	
	}
	
	void Network_manager :: send(byte b0,byte b1,byte b2,byte b3,byte b4,byte b5)
	{
		this->encapsulation_stack[0].array[0] = b0;
		this->encapsulation_stack[0].array[1] = b1;
		this->encapsulation_stack[0].array[2] = b2;
		this->encapsulation_stack[0].array[3] = b3;
		this->encapsulation_stack[0].array[4] = b4;
		for(int i=0;i<5;i++) {
			Serial.print(this->encapsulation_stack[0].array[i]);
			//Serial.print(":"); 
		}
		Serial.print("\n");
	}




