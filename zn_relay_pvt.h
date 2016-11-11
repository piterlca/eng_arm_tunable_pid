#ifndef _RELAY_PVT_
#define _RELAY_PVT_

#include "type.h"
#include "zn_relay.h"

static WORD
generate_relay(
	SWORD 			input,
	SDWORD 			output_offset,
	struct zn_relay_s* zn_relay
);

static void
calculate_period(
	SWORD input,
	zn_relay_h 	relay
);

static void
calculate_amplitude(
	SWORD 			input,
	zn_relay_h 	relay
);

#endif
