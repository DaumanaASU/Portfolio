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
 * @file    Project3.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL46Z4.h"
#include "fsl_debug_console.h"

int lightNumber = 0;
int speed = 500;
int level = 1;
int currentLight = 5;

void delay_ms(unsigned short delay_t)
{
	SIM->SCGC6 |= (1 << 24); // Clock Enable TPM0
	SIM->SOPT2 |= (0x2 << 24); // Set TPMSRC to OSCERCLK
	TPM0->CONF |= (0x1 << 17); // Stop on Overflow
	TPM0->SC = (0x1 << 7) | (0x07); // Reset Timer Overflow Flag, Set Prescaler 128
	TPM0->MOD = delay_t * 61 + delay_t/2; //

	TPM0->SC |= 0x01 << 3; // Start the clock!

	while(!(TPM0->SC & 0x80)){} // Wait until Overflow Flag
	return;
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

void startLevel() // Starts new level
{
	lightNumber = rand()%4; // Selects and flashed target LED
	for (int i = 0; i < 5; i++)
	{
		turnOnLed(lightNumber);
		delay_ms(500);
		turnOffLed(lightNumber);
		delay_ms(500);
	}
}

void win()
{
	for (int i =0; i < 3; i++) // Win sequence
	{
		turnOnLed(lightNumber);
		delay_ms(500);
		turnOffLed(lightNumber);
		delay_ms(500);
	}
	speed = 0.75*speed; // Speeds up the game
	delay_ms(1500);
	printf("Completed level: %d\n", level); // Prints level completed
	level = level + 1; // Increases level
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
	printf("\nFailed level: %d\n\n",level);
	speed = 500; // Resets Speed
	level = 1; // Resets level
	delay_ms(1750);
}

void PIT_IRQHandler(void)
{
	if(PIT->CHANNEL[0].TFLG){ // Timer 0 Triggered
		PIT->CHANNEL[0].TFLG = 1; // Reset
		for (int i = 0; i < 4; i++) // Lights up LEDs from 1 to 4
		{
			turnOnLed(i);
			currentLight = i;
			delay_ms(speed);
			turnOffLed(i);
		}
		for (int i = 2; i > 0; i--) // Lights up LEDs 3 and 2
		{
			turnOnLed(i);
			currentLight = i;
			delay_ms(speed);
			turnOffLed(i);
		}

	}
}

void init_pits()
{
	SIM->SCGC6 |= (1<<23);
	PIT->MCR = 0x00;
	PIT->CHANNEL[0].LDVAL = (24000*speed); // setup timer 0

	NVIC_SetPriority(22,3);
	NVIC_EnableIRQ(22);
	PIT->CHANNEL[0].TCTRL = 0x3; // enable Timer 0 interrupts and start timer.
}

void PORTA_IRQHandler(void)
{
	delay_ms(20); // Debounce
	while (GPIOA->PDIR & (1<<4)) {}
	delay_ms(20); // Debounce

	PORTA->PCR[4] |= (1 << 24); // Clear Interrupt Flag!

	PIT->CHANNEL[0].TFLG = 1; // Reset
	PIT->CHANNEL[0].TCTRL = 0; // Disable Timer
	if (currentLight == lightNumber) // If correct button is pressed
	{
		win();
	}
	else if (currentLight < 4)// If the button is not correct
	{
		lose();
	}

	startLevel(); // Start new level
	PIT->CHANNEL[0].TCTRL = 0x3; //Enable and start timer
}

void setup_SW1_interrupt()
{
	SIM->SCGC5 |= (1<<9); // Enable clock
	//Setup Switch
	PORTA->PCR[4] &= ~0xF0703; // Clear MUX, PE/PS
	PORTA->PCR[4] |= 0xF0703 & ((0x9 << 16) | (1 << 8) | 0x2); // Set MUX to HPIO, set pull down
	GPIOA->PDDR &= ~(1 << 4); // Input

	//Enable IRQ
	NVIC_EnableIRQ(30);
}

/*
 * @brief   Application entry point.
 */
int main(void) {

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();

	// Board Setup Functions
	setupLEDs();
	//startLevel();
	init_pits();
	setup_SW1_interrupt();
	//win();
	//lose();

	while(1) {} // Nothing forever
	return 0 ;
}
