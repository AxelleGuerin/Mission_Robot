//robot.h 

#ifndef ROBOT_H
#define ROBOT_H


typedef struct{
    int left_encoder;
    int right_encoder;
    int left_sensor;
    int right_sensor;
    int center_sensor;
    int battery;
} robot_status;

typedef enum{
    LEFT_WHEEL,
    RIGHT_WHEEL, 
    BOTH_WHEEL,
}wheel;

typedef int speed_pct;

typedef enum{
    ROBOT_OK,
    ROBOT_OBSTACLE,
    ROBOT_PROBLEM,
}notification;



int robot_start(void);
void robot_stop(void);
void robot_set_speed(speed_pct left_speed, speed_pct right_speed);
int robot_get_wheel_position(wheel wheel);
robot_status robot_get_status(void);
void robot_reset_wheel_pos();
void robot_signal_event(notification event);

#endif // ROBOT_H
