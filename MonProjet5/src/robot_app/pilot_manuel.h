// pilot_manuel.c
#include <math.h>
#include <stdlib.h>

#include "pilot.h" 
#include "robot.h"
#include "../utils.h"

#define FORWARD_STEP 142
#define ANGLE_STEP	221
#define DEFAULT_SPEED 20

static int emergency_stop = 0;
static move my_move;
static char c; 

extern void pilot_manuel_kb_move(void){

    fprintf(stdout,"================================\n");
	fprintf(stdout,"Press a button to start moving : \n\nPress 'z' for forward,\nPress 'q' for left,\nPress 's' for u turn,\nPress 'd' for right\n");
    fprintf(stdout,"================================\n");

	c = getchar();

	if (emergency_stop && c != 'e') {
        fprintf(stdout,"Emergency stop active. Press '%c' to start again.\n", 'e');
        return;
    }

    switch(c){
        case 'z':
                fprintf(stdout,"You pressed %c. The robot moves forward \n\n ", c);
                my_move.type = FORWARD;
                my_move.speed = DEFAULT_SPEED; 
                pilot_start_move(my_move);
            break;

        case 's':
            fprintf(stdout,"You pressed %c. The robot turn completely \n\n", c);
            my_move.type = ROTATION;
			my_move.range.angle = U_TURN;
            my_move.speed = DEFAULT_SPEED; 
			pilot_start_move(my_move); 
            break;

        case 'q':
            fprintf(stdout,"You pressed %c. The robot turns to the left \n\n", c);
            my_move.type = ROTATION;
            my_move.range.angle = LEFT;
            my_move.speed = DEFAULT_SPEED; 
			pilot_start_move(my_move); 
            break;

        case 'd':
            fprintf(stdout,"You pressed %c. The robot turn to the right \n\n", c);
            my_move.type = ROTATION;
            my_move.range.angle = RIGHT;
            my_move.speed = DEFAULT_SPEED; 
			pilot_start_move(my_move); 
            break;

		case 'a':
            fprintf(stdout,"You pressed %c. The robot is at an emmergency stop \n\n", c);
			my_move.type = NONE;
			my_move.speed = 0;
			emergency_stop = 1;
			fprintf(stdout,"Emergency stop active\n");
			break;
		
		case 'e' :
            fprintf(stdout,"You pressed %c. The robot can move again \n\n", c);
			my_move.type = NONE;
            my_move.speed = 0;
			emergency_stop = 0;
			break;


        default:
            fprintf(stdout,"Invalid key '%c' pressed\n\n", c);
            return;
    }

}
