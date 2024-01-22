#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h> 
#include <math.h> 

#include "robot.h"
#include "mrpiz.h"
#include "../utils.h"


int robot_start()
{
	return mrpiz_init();
}

void robot_set_speed(speed_pct left, speed_pct right)
{
	if (abs(left)<=100 || abs(left)>0){
		mrpiz_motor_set(MRPIZ_MOTOR_LEFT, left);
	}

	if (abs(right)<=100 || abs(right)>0){
		mrpiz_motor_set(MRPIZ_MOTOR_RIGHT, right);
	}
}

int robot_get_wheel_position(wheel wheel_id)
{
	if (wheel_id == LEFT_WHEEL){
		return mrpiz_motor_encoder_get(MRPIZ_MOTOR_LEFT);
	}

	if (wheel_id == RIGHT_WHEEL){
		return mrpiz_motor_encoder_get(MRPIZ_MOTOR_RIGHT);
	}
	return 0;
	
}

void robot_reset_wheel_pos()
{
	mrpiz_motor_encoder_reset(MRPIZ_MOTOR_LEFT);
	mrpiz_motor_encoder_reset(MRPIZ_MOTOR_RIGHT);
}

robot_status robot_get_status()
{
	robot_status status;
	status.left_encoder = mrpiz_motor_encoder_get(MRPIZ_MOTOR_LEFT);
	status.right_encoder = mrpiz_motor_encoder_get(MRPIZ_MOTOR_RIGHT);
	status.left_sensor = mrpiz_proxy_sensor_get(MRPIZ_PROXY_SENSOR_FRONT_LEFT);
	status.right_sensor = mrpiz_proxy_sensor_get(MRPIZ_PROXY_SENSOR_FRONT_RIGHT);
	status.center_sensor = mrpiz_proxy_sensor_get(MRPIZ_PROXY_SENSOR_FRONT_CENTER);
	status.battery = mrpiz_battery_level();

	return status;
}

void robot_signal_event(notification event)
{
	switch (event)
	{
	case ROBOT_OK :
		mrpiz_led_rgb_set(MRPIZ_LED_GREEN);
		break;
	case ROBOT_OBSTACLE :
		mrpiz_led_rgb_set(MRPIZ_LED_BLUE);
		break;
	case ROBOT_PROBLEM :
		mrpiz_led_rgb_set(MRPIZ_LED_RED);
		break;
	
	default:
		break;
	} 
}

void robot_stop()
{
	mrpiz_motor_set(MRPIZ_MOTOR_LEFT, 0);
	mrpiz_motor_set(MRPIZ_MOTOR_RIGHT, 0);
	mrpiz_led_rgb_set(MRPIZ_LED_OFF);
	mrpiz_close();
}


