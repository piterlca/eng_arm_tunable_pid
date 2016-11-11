#ifndef _ADAPTIVE_PID_H_
#define _ADAPTIVE_PID_H_

struct s_adaptive_pid;
typedef struct s_adaptive_pid* adaptive_pid_h;

void
adaptive_pid_init(
void);

WORD 
adaptive_pid(
	SWORD input,
	SDWORD offset,
	adaptive_pid_h h_adaptive_pid
);

void
zn_calculate_period(
void);
		
void
zn_calculate_amplitude(void);

#endif
