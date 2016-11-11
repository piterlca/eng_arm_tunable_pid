#include "PID.h"
#include "zn_relay.h"
#include "adaptive_pid.h"
#include "adaptive_pid_pvt.h"

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
	WORD output;
	
	struct adaptive_pid_s* adaptive_pid = (struct adaptive_pid_s*)h_adaptive_pid;	
	
	if(!	(adaptive_pid->b_pid_tuned)	&& zn_is_tuner_ready(adaptive_pid->relay)	)
	{
		apply_tuning(adaptive_pid);
		
		adaptive_pid->b_pid_tuned = TRUE;
	}
	if(!	(adaptive_pid->b_pid_tuned)	)
	{	
		return zn_relay(
			input, 
			offset, 
			adaptive_pid->relay
		);	
	}
	else
	{
		return PID(
			input,
			adaptive_pid->pid,
			offset
		); 
	}
}

static void
apply_tuning(
	struct adaptive_pid_s* adaptive_pid
)
{
	adaptive_pid->pid->kp;
	adaptive_pid->pid->ki;
	adaptive_pid->pid->kd;
}
