#line 1 "adaptive_pid.c"
#line 1 "PID.h"




#line 1 "type.h"




















typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef unsigned long  DWORD;
typedef unsigned long long  QWORD;
typedef unsigned int   BOOL;

typedef signed char SBYTE;
typedef signed short SWORD;
typedef signed long  SDWORD;
typedef signed long long  SQWORD;
typedef signed int   SBOOL;







#line 6 "PID.h"
typedef struct 
{
	WORD kp,ki,kd;
	BYTE dkp,dki,dkd;
	SBYTE sign;
	BYTE syn;
} PIDSTRUCT;
void PID_Init(void);
WORD PID(SWORD ADCbuf,PIDSTRUCT* factors,SDWORD off);

#line 2 "adaptive_pid.c"
#line 1 "zn_relay.h"



#line 5 "zn_relay.h"
#line 6 "zn_relay.h"








struct 												zn_relay_s;
typedef struct zn_relay_s* 		zn_relay_h;


void
zn_init(
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

WORD
zn_get_p(
	zn_relay_h 	zn_relay
);

WORD
zn_get_i(
	zn_relay_h 	zn_relay
);

BOOL
zn_tuner_ready(
	zn_relay_h zn_relay
);

#line 3 "adaptive_pid.c"
#line 1 "adaptive_pid.h"



struct s_adaptive_pid;
typedef struct s_adaptive_pid* adaptive_pid_h;

enum ctrlr_type {PID_P, PID_PI, PID_PID};

void
adaptive_pid_init(void);

WORD 
adaptive_pid(
	SWORD input,
	SDWORD offset,
	adaptive_pid_h h_adaptive_pid
);
		
#line 4 "adaptive_pid.c"

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
