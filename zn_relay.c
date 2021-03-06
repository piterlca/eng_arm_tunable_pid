// Header: Adaptatywny kontroler na potrzeby AFM
// File Name: zn_relay.c
// Author: PIOTR CIELECKI
// Date: 11.11.2016

#include "type.h"
#include "PID.h"
#include "zn_relay.h"
#include "zn_relay_pvt.h"

enum period_calculation_states{HOLD, OBSERVATION, HIT_IN_PHASE, HIT_COUNTERPHASE, SECOND_HIT_IN_PHASE, VERIFY, DONE};

typedef struct zn_relay_s
{
	SWORD 		m_in_hysteresis;
	SWORD 		m_out_amplitude;	
	WORD			m_last_output;
	
	SWORD			m_in_max;
	SWORD			m_in_min;
	WORD			m_in_amplitude;
	WORD			m_period_in_samples;
	WORD			m_n_samples_processed;
	WORD			m_ultimate_gain;
	
	BOOL			m_b_is_tuned;
	enum ctrlr_type
						m_ctrlr_type;
	
	enum period_calculation_states 
						m_pcs;
	
}zn_relay_s;

void
zn_init(
	WORD 				relay_output_amplitude,
	WORD 				relay_input_hysteresis,
	zn_relay_h	zn_relay
)
{
	struct zn_relay_s* rel = (struct zn_relay_s*)zn_relay;
	
	memset((void*)rel, sizeof(struct zn_relay_s), 0);
}


WORD
zn_relay(
	SWORD 				input,
	SDWORD 				output_offset,
	zn_relay_h 		zn_relay
)
{
	zn_relay_s* rel=(zn_relay_s*)zn_relay;
	
	calculate_amplitude(
		input, 
		zn_relay
	);
	
	calculate_period(
		input,
		zn_relay
	);
	
	++(rel->m_n_samples_processed);

	return generate_relay(
					input,
					output_offset,
					rel
				);
}

static WORD
generate_relay(
	SWORD 			input,
	SDWORD 			output_offset,
	zn_relay_s* rel
)
{
	WORD output;
	
	if			(input < output_offset + rel->m_in_hysteresis)
		output = output_offset + rel->m_out_amplitude;
	
	else if (input > output_offset + rel->m_in_hysteresis)
		output = output_offset - rel->m_out_amplitude;
	
	else
		output = rel->m_last_output;
	
	return output;
}

void
calculate_amplitude(
	SWORD 			input,
	zn_relay_h 	relay
)
{	
	SWORD		maxvals[MIN_PERIODS_TO_CALCULATE_AMPLITUDE];
	SWORD		minvals[MIN_PERIODS_TO_CALCULATE_AMPLITUDE];
	
	struct zn_relay_s* rel = (struct zn_relay_s*)zn_relay;
	
	if(input > rel->m_in_max)
		rel->m_in_max = input;
	else if(input < rel->m_in_min)
		rel->m_in_min = input;
	
	if(rel->m_n_samples_processed  > MIN_PERIODS_TO_CALCULATE_AMPLITUDE * rel->m_period_in_samples)
	{
		rel->m_in_amplitude = (rel->m_in_max - rel->m_in_min) >> 1;
		
		rel->m_b_is_tuned = 1;
		
		rel->m_ultimate_gain = 4*rel->m_out_amplitude /(PI*rel->m_in_amplitude);
	}
}

#define DUMMYVAL 1
#define HYSTERESIS_FRAME(in, centerval) (		in <= centerval + DELTA_AMPLITUDE			\
																				&& 	in >= centerval - DELTA_AMPLITUDE	)

void
calculate_period(
	SWORD 			input,
	zn_relay_h 	relay
)
{	
	static SWORD		observed_in_val;
	static WORD			t0 = 0;
	static WORD			t1 = 0;
	
	struct zn_relay_s* rel = (struct zn_relay_s*)zn_relay;
	
	switch(rel->m_pcs)
	{
		case HOLD:
			if(rel->m_n_samples_processed > ZN_DELAY_IN_SAMPLES)
			{
				if(input > rel->m_in_min && input < rel->m_in_max)			
					observed_in_val = input;
					rel->m_pcs = OBSERVATION;
			}	
			break;
		
		case OBSERVATION:
			if(	HYSTERESIS_FRAME(input, observed_in_val)	)	
			{
				if(0 == t0)
					rel->m_pcs = HIT_IN_PHASE;
				else if(0 == t1)
					rel->m_pcs = HIT_COUNTERPHASE;
				else
					rel->m_pcs = SECOND_HIT_IN_PHASE;
					}	
			break;
		
		case HIT_IN_PHASE:
			if(	!HYSTERESIS_FRAME(input, observed_in_val)	)
			{
						t0 = rel->m_n_samples_processed;			
						rel->m_pcs = OBSERVATION;
					}
			break;
					
		case HIT_COUNTERPHASE:
			if(	!HYSTERESIS_FRAME(input, observed_in_val)	)
			{
				t1 = DUMMYVAL;
				rel->m_pcs = OBSERVATION;
			}
			break;
		
		case DONE:
		{
			t1 = rel->m_n_samples_processed;
			rel->m_period_in_samples = (t1 - t0);
		}
		break;
		
		default:
			break;
	}
}

WORD
zn_get_p(
	zn_relay_h 	zn_relay
)
{
	return 0;
}

WORD
zn_get_i(
	zn_relay_h 	zn_relay
)
{
	return 0;
}

BOOL
zn_is_tuner_ready(
	zn_relay_h zn_relay
)
{
	struct zn_relay_s* rel = (struct zn_relay_s*)zn_relay;
	
	return rel->m_b_is_tuned;
}
