/**
 * hello robot main program
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>


#include "robot_app/robot.h"
#include "robot_app/pilot.h"
#include "robot_app/pilotManuel.h"
#include "robot_app/copilot.h"

#define TEMPO	1000000
#define POLLING_PERIOD	10000

							
/* Custom type for process state management */
typedef enum{
	STOPPED = 0,
	LIVE
}process_state;

static void robot_loop(void);

/* global variable used for program clean exit */
static process_state running = LIVE;

/**
 * Function for CTRL+C signal management
 */
static void sigint_handler(int dummy)
{
    running = STOPPED;
}

int main (void)
{

  	
	if (robot_start() == -1) {
		return EXIT_FAILURE;
	}

	/* Interception d'un Ctrl+C pour arrêter le programme proprement. */
	signal(SIGINT, sigint_handler);
	
	/* Procédure hello de manipulation du robot. */
	robot_loop();

	/* Arrêt du robot. */
	robot_stop();

	return EXIT_SUCCESS;
}

/**
 * Robot control function 
 *
 * Send commands to the robot using the keyboard and display status data with a specific period
 */

static void robot_loop()
{
	robot_status my_status;
	
	
	int step_counter = 0;	
	char c;

	while(running)
	{	
		my_status = robot_get_status();
		pilotManuel_kb_move();

		for(int i=0;i<200;i++)
		{
			usleep(POLLING_PERIOD);
			pilot_stop_at_target();
		}
	}
}
