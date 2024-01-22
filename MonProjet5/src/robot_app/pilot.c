// pilot.c
#include <math.h>
#include <stdlib.h>

#include "pilot.h" 
#include "robot.h"
#include "../utils.h"

#define FORWARD_STEP 142
#define ANGLE_STEP	221
#define DEFAULT_SPEED 20

#define SENSOR_THRESHOLD	120

static move_status robot_moving = DONE;
static int target_pos = 0;
static wheel reference_wheel = LEFT_WHEEL;
static int emergency_stop = 0;

extern void pilot_start_move(move my_move)
{
	if(robot_moving != IN_PROGRESS)
	{
		switch(my_move.type)
		{
			case FORWARD:
			robot_set_speed(my_move.speed, my_move.speed);
			target_pos = FORWARD_STEP;
			break;
			
			case ROTATION:
				switch(my_move.range.angle)
				{
					case NONE:
						return;
						break;
						
					case LEFT:
						robot_set_speed(-my_move.speed, my_move.speed);
						target_pos = ANGLE_STEP;
						break;
						
					case RIGHT:
						robot_set_speed(my_move.speed, -my_move.speed);
						target_pos = ANGLE_STEP;
						break;
												
					case U_TURN:
						robot_set_speed(-my_move.speed, my_move.speed);
						target_pos = 2*ANGLE_STEP;
						break;
				}
			break;
			
			default:
			TRACE("default case reached");
			break;
		}
		switch(robot_moving)
		{
			case IDLE:
				TRACE("move status cannot be IDLE");
			break;
			case DONE:
				robot_signal_event(ROBOT_OK);
			break;
			case OBSTACLE:
				robot_signal_event(ROBOT_OBSTACLE);
			break;
			case IN_PROGRESS:
				TRACE("move status cannot be IN_PROGRESS here");
			break;
			default:
			TRACE("default case reached");
			break;
		}
		robot_moving = IN_PROGRESS;
	}	
}

extern move_status pilot_stop_at_target(void)
{
	robot_status my_status = robot_get_status();
	
	if( my_status.center_sensor < SENSOR_THRESHOLD)
	{
		robot_moving = OBSTACLE;
	}
	if( robot_moving && abs(robot_get_wheel_position(LEFT_WHEEL)) >= target_pos)
	{
		robot_reset_wheel_pos();
		robot_set_speed(0, 0);
		robot_moving = DONE;  
	}
	
	return robot_moving;
}

extern move_status pilot_get_status(void)
{
	return robot_moving;
}

// Ajout pour la mission 5
extern void pilot_kb_move(void){
    move my_move;
	char c; 

	while(1){
		c = getchar();
		getchar();

		if (emergency_stop && c != 'e') {
       		fprintf(stdout,"Emergency stop active. Press '%c' to start again.\n", 'e');
        	return;
    	}

    	switch(c){
        	case 'z':
            	my_move.type = FORWARD;
            	my_move.speed = DEFAULT_SPEED; 
				pilot_start_move(my_move);
            	break;
			/*
        	case 's':
				my_move.type = ROTATION;
				my_move.range.angle = U_TURN;
				my_move.speed = DEFAULT_SPEED; 
				pilot_start_move(my_move); 
				break;
			*/

			case 'q':
				my_move.type = ROTATION;
				my_move.range.angle = LEFT;
				my_move.speed = DEFAULT_SPEED; 
				pilot_start_move(my_move); 
				break;

			case 'd':
				my_move.type = ROTATION;
				my_move.range.angle = RIGHT;
				my_move.speed = DEFAULT_SPEED; 
				pilot_start_move(my_move); 
				break;

			case 'a':
				my_move.type = NONE;
				my_move.speed = 0;
				emergency_stop = 1;
				fprintf(stdout,"Emergency stop active\n");
				break;
			
			case 'e' :
				my_move.type = NONE;
				my_move.speed = 0;
				emergency_stop = 0;
				break;


			default:
				fprintf(stdout,"Invalid key '%c' pressed\n", c);
				return;
		}

		
    }

}
