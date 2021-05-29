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
 * @file    Project2.c
 * @brief   Application entry point.
 */
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL46Z4.h"
#include "fsl_debug_console.h"

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

void setup_switches()
{
	//Setup SW1
	PORTA->PCR[4] &= ~0x703; // Clear MUX, PE/PS
	PORTA->PCR[4] |= 0x703 & ((1 << 8) | 0x02); // Set MUX to HPIO, set pull down
	GPIOA->PDDR &= ~(1 << 4); // Input

	//Setup SW2
	PORTA->PCR[5] &= ~0x703; // Clear MUX, PE/PS
	PORTA->PCR[5] |= 0x703 & ((1 << 8) | 0x02); // Set MUX to HPIO, set pull down
	GPIOA->PDDR &= ~(1 << 5); // Input

	//Setup SW3
	PORTA->PCR[12] &= ~0x703; // Clear MUX, PE/PS
	PORTA->PCR[12] |= 0x703 & ((1 << 8) | 0x02); // Set MUX to HPIO, set pull down
	GPIOA->PDDR &= ~(1 << 12); // Input

	//Setup SW4
	PORTA->PCR[13] &= ~0x703; // Clear MUX, PE/PS
	PORTA->PCR[13] |= 0x703 & ((1 << 8) | 0x02); // Set MUX to HPIO, set pull down
	GPIOA->PDDR &= ~(1 << 13); // Input
}

void setup_lights()
{
	//Setup LED1
	PORTC->PCR[0] &= ~0x700; // Clear MUX
	PORTC->PCR[0] |= 0x700 & (1 << 8); // Set to GPIO
	GPIOC->PDDR |= (1 << 0);  // Output

	//Setup LED2
	PORTC->PCR[4] &= ~0x700; // Clear MUX
	PORTC->PCR[4] |= 0x700 & (1 << 8); // Set to GPIO
	GPIOC->PDDR |= (1 << 4);  // Output

	//Setup LED3
	PORTC->PCR[6] &= ~0x700; // Clear MUX
	PORTC->PCR[6] |= 0x700 & (1 << 8); // Set to GPIO
	GPIOC->PDDR |= (1 << 6);  // Output

	//Setup LED4
	PORTC->PCR[7] &= ~0x700; // Clear MUX
	PORTC->PCR[7] |= 0x700 & (1 << 8); // Set to GPIO
	GPIOC->PDDR |= (1 << 7);  // Output

}

// Waits for a button to be pressed, returns the button number
int getButton()
{
	while(1)
	{
		delay_ms(15); //Debouncing
		if(GPIOA->PDIR & (1<<4)) // Switch 1 pressed
		{
			while (GPIOA->PDIR & (1<<4)) // Switch 1 stays pressed
			{
				GPIOC->PDOR |= (1<<0); // Turn on Led 1
			}
			GPIOC->PDOR &= ~(1<<0); // Turn off Led 1
			return 1;
		}else if (GPIOA->PDIR & (1<<5)) // Switch 2 pressed
		{
			while (GPIOA->PDIR & (1<<5)) // Switch 2 stays pressed
			{
				GPIOC->PDOR |= (1<<4); // Turn on Led 2
			}
			GPIOC->PDOR &= ~(1<<4); // Turn off Led 2
			return 2;
		}else if (GPIOA->PDIR & (1<<12)) // Switch 3 pressed
		{
			while (GPIOA->PDIR & (1<<12)) // Switch 3 stays pressed
			{
				GPIOC->PDOR |= (1<<6); // Turn on Led 3
			}
			GPIOC->PDOR &= ~(1<<6); // Turn off Led 3
			return 3;
		}else if (GPIOA->PDIR & (1<<13)) // Switch 4 pressed
		{
			while (GPIOA->PDIR & (1<<13)) // Switch 4 stays pressed
			{
				GPIOC->PDOR |= (1<<7); // Turn on Led 4
			}
			GPIOC->PDOR &= ~(1<<7); // Turn off Led 4
			return 4;
		}
		else // No buttons pressed, all Leds are off
		{
			GPIOC->PDOR &= ~(1<<0);
			GPIOC->PDOR &= ~(1<<4);
			GPIOC->PDOR &= ~(1<<6);
			GPIOC->PDOR &= ~(1<<7);
		}
	}
	return 0;
}

// Led 1 used on the sequence
void led1()
{
	GPIOC->PDOR |= (1<<0); // Turn on Led 1
	delay_ms(500);
	GPIOC->PDOR &= ~(1<<0); // Turn off Led 1
	delay_ms(500);
}

// Led 2 used on the sequence
void led2()
{
	GPIOC->PDOR |= (1<<4); // Turn on Led 2
	delay_ms(500);
	GPIOC->PDOR &= ~(1<<4); // Turn off Led 2
	delay_ms(500);
}

// Led 3 used on the sequence
void led3()
{
	GPIOC->PDOR |= (1<<6); // Turn on Led 3
	delay_ms(500);
	GPIOC->PDOR &= ~(1<<6); // Turn off Led 3
	delay_ms(500);
}

// Led 4 used on the sequence
void led4()
{
	GPIOC->PDOR |= (1<<7); // Turn on Led 4
	delay_ms(500);
	GPIOC->PDOR &= ~(1<<7); // Turn off Led 4
	delay_ms(500);
}

// All lights flash 5 times
void lose()
{
	for (int i = 1; i<=5;i++)
	{
		GPIOC->PDOR |= (1<<0); // Turn on Led 1
		GPIOC->PDOR |= (1<<4); // Turn on Led 2
		GPIOC->PDOR |= (1<<6); // Turn on Led 3
		GPIOC->PDOR |= (1<<7); // Turn on Led 4
		delay_ms(500);
		GPIOC->PDOR &= ~(1<<0); // Turn off Led 1
		GPIOC->PDOR &= ~(1<<4); // Turn off Led 2
		GPIOC->PDOR &= ~(1<<6); // Turn off Led 3
		GPIOC->PDOR &= ~(1<<7); // Turn off Led 4
		delay_ms(500);
	}
}

// Win light sequence
void win()
{
	GPIOC->PDOR |= (1<<0); // Turn on Led 1
	delay_ms(500);
	GPIOC->PDOR &= ~(1<<0); // Turn off Led 1

	GPIOC->PDOR |= (1<<4); // Turn on Led 2
	delay_ms(500);
	GPIOC->PDOR &= ~(1<<4); // Turn off Led 2

	GPIOC->PDOR |= (1<<6); // Turn on Led 3
	delay_ms(500);
	GPIOC->PDOR &= ~(1<<6); // Turn off Led 3

	GPIOC->PDOR |= (1<<7); // Turn on Led 4
	delay_ms(500);
	GPIOC->PDOR &= ~(1<<7); // Turn off Led 4
	delay_ms(500);

	GPIOC->PDOR |= (1<<0); // Turn on Led 1
	GPIOC->PDOR |= (1<<4); // Turn on Led 2
	GPIOC->PDOR |= (1<<6); // Turn on Led 3
	GPIOC->PDOR |= (1<<7); // Turn on Led 4
	delay_ms(500);
	GPIOC->PDOR &= ~(1<<0); // Turn off Led 1
	GPIOC->PDOR &= ~(1<<4); // Turn off Led 2
	GPIOC->PDOR &= ~(1<<6); // Turn off Led 3
	GPIOC->PDOR &= ~(1<<7); // Turn off Led 4
	delay_ms(500);
}

void game()
{
	while (1)
	{
		srand(time(NULL));
		int pattern[5];
		for (int j=1;j<=5;j++)
		{
			pattern[j] = rand()%4 + 1;
		}
		for(int i = 1; i <=5;i++)
		{
			for (int j=1;j<=i;j++)
			{
				if (pattern[j] == 1)
				{
					led1();
				}
				else if (pattern[j] == 2)
				{
					led2();
				}
				else if (pattern[j] == 3)
				{
					led3();
				}
				else if (pattern[j] == 4)
				{
					led4();
				}
			}
			for (int k=1;k<=i;k++)
			{
				int button = getButton();
				if (pattern[k] != button)
				{
					lose();
					goto end;
				}
			}
			delay_ms(500);
		}
		win();

		end:;
	}
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

	//Turn on port A and port C
	SIM->SCGC5 |= (1<<11) | (1<<9);

	setup_switches();
	setup_lights();

	game();
	return 0 ;
}
