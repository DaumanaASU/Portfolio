/*
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    Project4.c
 * @brief   Application entry point.
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
/* TODO: insert other include files here. */

int targetAngle = 9; //target angle, set to 9 as that is not a valid value
int speed = 10000; //Time to complete the level in ms, starts at 10s
int timer = 0;//Timer in ms
int delay = 0;//Used for delay_ms, increases each ms
int level = 1;
float angle = 0;
int currentAngle = 8;//angle currently on the board, 8 is invalid value

void delay_ms(unsigned short delay_t);
void setupLEDs();
void turnOnLed(int LedNumber);
void turnOffLed(int LedNumber);
void angleLightOn(int targetAngle);
void angleLightOff(int targetAngle);
void win();
void lose();
void TPM0_IRQHandler(void);
void init_timer();
void setup_switch();
void waitToStart();
void runGame();
void startLevel();

void delay_ms(unsigned short delay_t) //modified to run together with tpm interrupt handler
{
	delay = 0;//reset delay
	while (delay < delay_t) //delay is increased by TPM0_IRQHandler()
	{}
}

void setupLEDs()
{
	SIM->SCGC5 |= (1<<11); // Enable clock
	//Setup LED1
	PORTC->PCR[0] &= ~0x700; // Clear MUX
	PORTC->PCR[0] |= 0x700 & (1 << 8); // Set to GPIO
	GPIOC->PDDR |= (1 << 0);  // Output
	GPIOC->PCOR |= (1 << 0); // Set off

	//Setup LED2
	PORTC->PCR[4] &= ~0x700; // Clear MUX
	PORTC->PCR[4] |= 0x700 & (1 << 8); // Set to GPIO
	GPIOC->PDDR |= (1 << 4);  // Output
	GPIOC->PCOR |= (1 << 4); // Set off

	//Setup LED3
	PORTC->PCR[6] &= ~0x700; // Clear MUX
	PORTC->PCR[6] |= 0x700 & (1 << 8); // Set to GPIO
	GPIOC->PDDR |= (1 << 6);  // Output
	GPIOC->PCOR |= (1 << 6); // Set off

	//Setup LED4
	PORTC->PCR[7] &= ~0x700; // Clear MUX
	PORTC->PCR[7] |= 0x700 & (1 << 8); // Set to GPIO
	GPIOC->PDDR |= (1 << 7);  // Output
	GPIOC->PCOR |= (1 << 7); // Set off
}

void turnOnLed(int LedNumber) // Turns on the led assigned to the number
{
	int list[] = {0,4,6,7};
	if (LedNumber >= 0 && LedNumber < 4 )
	{
		GPIOC->PSOR |= 1 << list[LedNumber];
	}
}

void turnOffLed(int LedNumber) // Turns off the led
{
	int list[] = {0,4,6,7};
	if (LedNumber >= 0 && LedNumber < 4 )
	{
		GPIOC->PCOR |= 1 << list[LedNumber];
	}
}

void angleLightOn(int targetAngle) //Turns on LEDs assigned to each angle
{
	switch(targetAngle)
	{
	case 0:
		turnOnLed(0);
		break;
	case 1:
		turnOnLed(0);
		turnOnLed(1);
		break;
	case 2:
		turnOnLed(1);
		break;
	case 3:
		turnOnLed(1);
		turnOnLed(2);
		break;
	case 4:
		turnOnLed(2);
		break;
	case 5:
		turnOnLed(2);
		turnOnLed(3);
		break;
	case 6:
		turnOnLed(3);
		break;
	default :
		break;
	}
}

void angleLightOff(int targetAngle) //Turns off LEDs assigned to each angle
{
	switch(targetAngle)
	{
	case 0:
		turnOffLed(0);
		break;
	case 1:
		turnOffLed(0);
		turnOffLed(1);
		break;
	case 2:
		turnOffLed(1);
		break;
	case 3:
		turnOffLed(1);
		turnOffLed(2);
		break;
	case 4:
		turnOffLed(2);
		break;
	case 5:
		turnOffLed(2);
		turnOffLed(3);
		break;
	case 6:
		turnOffLed(3);
		break;
	default :
		break;
	}
}

void win()
{
	for (int i = 0; i < 3; i++) // win sequence
	{
		angleLightOn(targetAngle);
		delay_ms(500);
		angleLightOff(targetAngle);
		delay_ms(500);
	}
	speed = 0.75*speed; // Speeds up the game
	printf("Completed level: %d\n\n", level); // Prints level completed
	level = level + 1; // Increases level
	delay_ms(2500); //Pause between win sequence and new Level
}

void lose()
{
	for (int i = 0; i < 4; i++) //Lose Sequence
	{
		turnOnLed(i);
	}
	delay_ms(1000);
	for (int i = 0; i < 4; i++)
	{
		turnOffLed(i);
		delay_ms(250);
	}
	printf("\nFailed level: %d\n\n\n",level);
	speed = 10000; // Resets Speed
	level = 1; // Resets level
	delay_ms(2500); // Pause between lose sequence and new Game
}

void TPM0_IRQHandler(void)
{
	TPM0->SC |= (1 << 7); // Reset Timer Interrupt Flag
	timer++; //Timer in ms
	delay++; //Constantly increases delay per ms
}

void init_timer()
{
	SIM->SCGC6 |= (1 << 24); // Clock enable TPM1
	SIM->SOPT2 |= (0x2 << 24); // TPM Clock Source OSCERCLK
	TPM0->MOD = 7999; // Reload every millisecond.

	NVIC_EnableIRQ(17);
	// Reset TOF, Enable Interrupt, Prescaler = 0, Start Timer
	TPM0->SC = (1 << 7) | (1 << 6) | (1 << 3);
}

void setup_switch()
{
	//Setup SW1
	PORTA->PCR[4] &= ~0x703; // Clear MUX, PE/PS
	PORTA->PCR[4] |= 0x703 & ((1 << 8) | 0x02); // Set MUX to HPIO, set pull down
	GPIOA->PDDR &= ~(1 << 4); // Input
}

void waitToStart() //Waits until button is pressed to start
{
	while(1)
	{
		delay_ms(20); // Debounce
		if (GPIOA->PDIR & (1<<4))
		{
			while (GPIOA->PDIR & (1<<4)) {}
			delay_ms(20); // Debounce
			return;
		}
	}
}

void runGame() //The clock is running to get to the desired angle
{
	while (timer <= speed) //Time for the level
	{
		angle = getAngle();
		if (-180 < angle && angle < -75) //-90 degrees
		{
			currentAngle = 0;
			angleLightOn(currentAngle);
			while (-180 < angle && angle < -75 && timer <= speed)
			{
				angle = getAngle();
			}
			angleLightOff(currentAngle);
		}
		else if (-75 < angle && angle < -45) //-60 degrees
		{
			currentAngle = 1;
			angleLightOn(currentAngle);
			while (-75 < angle && angle < -45 && timer <= speed)
			{
				angle = getAngle();
			}
			angleLightOff(currentAngle);
		}
		else if (-45 < angle && angle < -15) //-30 degrees
		{
			currentAngle = 2;
			angleLightOn(currentAngle);
			while (-45 < angle && angle < -15 && timer <= speed)
			{
				angle = getAngle();
			}
			angleLightOff(currentAngle);
		}
		else if (-15 < angle && angle < 15) //0 degrees
		{
			currentAngle = 3;
			angleLightOn(currentAngle);
			while (-15 < angle && angle < 15 && timer <= speed)
			{
				angle = getAngle();
			}
			angleLightOff(currentAngle);
		}
		else if (15 < angle && angle < 45) //30 degrees
		{
			currentAngle = 4;
			angleLightOn(currentAngle);
			while (15 < angle && angle < 45 && timer <= speed)
			{
				angle = getAngle();
			}
			angleLightOff(currentAngle);
		}
		else if (45 < angle && angle < 75) //60 degrees
		{
			currentAngle = 5;
			angleLightOn(currentAngle);
			while (45 < angle && angle < 75 && timer <= speed)
			{
				angle = getAngle();
			}
			angleLightOff(currentAngle);
		}
		else if (75 < angle && angle < 180) //90 degrees
		{
			currentAngle = 6;
			angleLightOn(currentAngle);
			while (75 < angle && angle < 180 && timer <= speed)
			{
				angle = getAngle();
			}
			angleLightOff(currentAngle);
		}
	}
	if (targetAngle == currentAngle) //Once time is finished checks if it got the correct angle
	{
		win(); // Won the level and increase level
	}
	else
	{
		lose(); // Lost the level, resets the game
	}
	startLevel(); //Start a new level
}

void startLevel() // Starts new level
{
	targetAngle = rand()%7; // Selects and flashed target LED
	for (int i = 0; i < 3; i++)
	{
		angleLightOn(targetAngle);
		delay_ms(500);
		angleLightOff(targetAngle);
		delay_ms(500);
	}
	timer = 0; // Restart timer
	runGame();
}


int main(void) {

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();


	initI2C(); //Initialize I2C
	initAccel(); //Initialize accelerometer
	init_timer(); //Initialize timer


	setup_switch(); // Setup switch
	setupLEDs(); // Setup LEDs

	waitToStart(); // Waits for button
	startLevel(); // Starts first level

	return 0 ;
}
