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
#include "robot_app/copilot.h"

#define TEMPO	1000000

#define POLLING_PERIOD	5000
							
/* Custom type for process state management */
typedef enum{
	STOPPED = 0,
	LIVE
}process_state;

static move path[6] =
    {
        {FORWARD, {20}, 20},
        {ROTATION, {RIGHT}, 20},
        {FORWARD, {20}, 20},
        {ROTATION, {LEFT}, 20},
		{FORWARD, {20}, 20},
        {ROTATION, {U_TURN}, 20},
	};

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
	
	/* Manipulation du robot. */
	robot_loop();

	/* Arrêt du robot. */
	robot_stop();

	return EXIT_SUCCESS;
}

static void robot_loop()
{
	robot_status my_status;
	my_status = robot_get_status();
	
	while(running)
	{
		
		//fprintf(stdout, "codeurs: g = %d, d = %d\n", my_status.left_encoder, my_status.right_encoder);
		//fprintf(stdout, "proxy: g = %d, c = %d, d = %d\n", my_status.left_sensor, my_status.center_sensor, my_status.right_sensor);
		//fprintf(stdout, "batterie: %d %%\n", my_status.battery);
		
		for(int i=0;i<TEMPO/POLLING_PERIOD;i++)
		{
			pilot_kb_move();
		}
	}
}
