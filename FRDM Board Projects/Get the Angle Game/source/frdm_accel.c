/*
 * frdm_accel.c
 *
 *  Created on: Apr 9, 2021
 *      Author: dauma
 */

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL46Z4.h"
#include "fsl_debug_console.h"
#include "frdm_i2c.h"
#include "frdm_accel.h"
#include <math.h>
#define PI 3.141592654

signed int xa;//x acceleration
signed int ya;//y acceleration
signed int za;//z acceleration

void initAccel() //Set control to active and fast mode
{
	WriteByte(0x2A, 0x03);
}

void getPosition() //get x, y, and z accelerations
{
	signed char x[1]; //array for x
	signed char y[1]; //array for y
	signed char z[1]; //array for z

	ReadBlock(0x01,x,1); //get x_msb
	ReadBlock(0x03,y,1); //get y_msb
	ReadBlock(0x05,z,1); //get z_msb

	xa=x[0]; //save to variable
	ya=y[0]; //save to variable
	za=z[0]; //save to variable

}

float getAngle()
{
	getPosition();
	double xad = xa; //change to double
	double zad = za; //change to double
	float angle = 90 - (atan2(zad,xad)*(180/PI)); //get the angle
	if (angle > 180) //get value between -90 and -180
	{
		angle = angle -360;
	}
	return angle;
}
