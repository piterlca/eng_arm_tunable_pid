#ifndef _ZN_RELAY_H_
#define _ZN_RELAY_H_

#include "type.h"
#include "PID.h"

struct 													zn_relay_s;
typedef struct 	zn_relay_s* 		zn_relay_h;


void
relay_init(
	WORD 				relay_output_amplitude,
	WORD 				relay_input_hysteresis,
	zn_relay_h	zn_relay
);

WORD
relay(
	SWORD 				input,
	SDWORD 				output_offset,
	zn_relay_h 		zn_relay,
	PIDSTRUCT*		pid
);

#endif