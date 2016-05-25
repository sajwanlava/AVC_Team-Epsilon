#include <sys/time.h>
#include <stdio.h>
#include <cmath>
#include <string.h>

#include "mazefollow.h"
#include "movement.h"
#include "extern.h"
#include "util.h"
#include "sensor_average.h"

void follow_wall(){
  
  /**
   * Reads data from the IR sensors,
   * stores the values in 3 variables
   * and adjusts motors accordingly
   */
	int frontVal, leftVal, rightVal = 0;
	while (true) {
		frontVal = get_sensor_average(FRONT_PIN, TESTS);
		leftVal = get_sensor_average(LEFT_PIN, TESTS);
		rightVal = get_sensor_average(RIGHT_PIN, TESTS);
		printf("Front: %d, Left: %d, Right: %d \n", frontVal, leftVal, rightVal)
		// If there is room on the left
		if (leftVal > LEFT_MIN){
			set_speed(0);
			turn(-1 * SHARP_TURN);
			Sleep(0, TURN_WAIT);
			reset_turn();
			set_speed(SPEED_DEF);
			move();
		}
		// If there is room at the front
		else if (frontVal > FRONT_MIN){
			set_speed(SPEED_DEF);
			move();
		}
		// If there is room on the right
		else if (rightVal > RIGHT_MIN){
			set_speed(0);
			turn(SHARP_TURN);
			Sleep(0, TURN_WAIT);
			reset_turn();
			set_speed(SPEED_DEF);
			move();
		}
		// If there is no room to the front or either side
		else{
			while(leftVal<50 && rightVal<50){
				set_motor(MOTOR_LEFT, (-SPEED_DEF));
				set_motor(MOTOR_RIGHT, (-SPEED_DEF)):
			}
			if(rightVal>50){
				turn(SHARP_TURN);
			}
			else if(leftVal>50){
				turn(-1 * SHARP_TURN);
			}
		}
		// Sleeps to allow robot to move forward
		Sleep(0, 250);
	}
	
}
