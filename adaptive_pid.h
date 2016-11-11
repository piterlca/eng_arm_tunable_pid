#ifndef _ADAPTIVE_PID_H_
#define _ADAPTIVE_PID_H_

struct adaptive_pid_s;
typedef struct adaptive_pid_s* adaptive_pid_h;

enum ctrlr_type {PID_P, PID_PI, PID_PID};

void
adaptive_pid_init(void);

WORD 
adaptive_pid(
	SWORD input,
	SDWORD offset,
	adaptive_pid_h h_adaptive_pid
);
		
#endif
