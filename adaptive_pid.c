#include "PID.h"
#include "zn_relay.h"
#include "adaptive_pid.h"

struct adaptive_pid_s{
	BOOL				b_pid_tuned;
	PIDSTRUCT* 	pid;
	zn_relay_h 	relay;
	
};

void
adaptive_pid_init(
)
{
}

WORD 
adaptive_pid(
	SWORD input,
	SDWORD offset,
	adaptive_pid_h h_adaptive_pid
)
{
	struct adaptive_pid_s* adaptive_pid = (struct adaptive_pid_s*)h_adaptive_pid;
	if(!	(adaptive_pid->b_pid_tuned)	)
	{
		zn_calculate_period();
		
		zn_calculate_amplitude();
		
		return zn_relay(input, offset, adaptive_pid->relay);
		
	}
	else
	{
		return PID(
			input,
			adaptive_pid->pid,
			offset
		) ; 
	}
}
