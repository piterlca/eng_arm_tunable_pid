// Header: Adaptatywny kontroler na potrzeby AFM
// File Name: zn_relay.c
// Author: PIOTR CIELECKI
// Date: 11.11.2016

#include "type.h"
#include "PID.h"
#include "zn_relay.h"

struct zn_relay_s
{
	SWORD 		m_in_hysteresis;
	SWORD 		m_out_amplitude;
	WORD			m_last_output;
};

void
relay_init(
	WORD 				relay_output_amplitude,
	WORD 				relay_input_hysteresis,
	zn_relay_h	zn_relay
)
{
	zn_relay->m_in_hysteresis=relay_input_hysteresis;
	
	zn_relay->m_out_amplitude=relay_output_amplitude;
}


WORD
relay(
	SWORD 				input,
	SDWORD 				output_offset,
	zn_relay_h 		zn_relay,
	PIDSTRUCT*		pid
)
{
	WORD output;
	struct zn_relay_s* rel=(struct zn_relay_s*)zn_relay;
	
	if				(input < output_offset + rel->m_in_hysteresis)
	{
		output = output_offset + rel->m_out_amplitude;
	}	
	else if 	(input > output_offset + rel->m_in_hysteresis)
	{
		output = output_offset - rel->m_out_amplitude;
	}	
	else
	{
		output = rel->m_last_output;
	}
	
	return output;
}
