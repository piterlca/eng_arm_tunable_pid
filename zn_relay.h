#ifndef _ZN_RELAY_H_
#define _ZN_RELAY_H_

#include "type.h"
#include "PID.h"

#define MIN_PERIODS_TO_CALCULATE_AMPLITUDE 				5
#define MAX_PERIOD_DIFF_IN_SAMPLES 								10
#define MAX_RELATIVE_AMPLITUDE_ERROR_IN_PERCENT		10
#define ZN_DELAY_IN_SAMPLES												50
#define DELTA_AMPLITUDE														0x0010


struct 													zn_relay_s;
typedef struct 	zn_relay_s* 		zn_relay_h;


void
zn_relay_init(
	WORD 				relay_output_amplitude,
	WORD 				relay_input_hysteresis,
	zn_relay_h	zn_relay
);

WORD
zn_relay(
	SWORD 				input,
	SDWORD 				output_offset,
	zn_relay_h 		zn_relay
);

#endif
