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
 * @file    Project1CSE325.c
 * @brief   Application entry point.
 */
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

//Led on for 250ms
void dot()
{
	GPIOD->PTOR |= (1<<5); //turn on
	delay_ms(250);

	GPIOD->PTOR |= (1<<5); //turn off
	delay_ms(250); //time between letters
}

//Led on for 750ms
void dash()
{
	GPIOD->PTOR |= (1<<5); //turn on
	delay_ms(750);

	GPIOD->PTOR |= (1<<5); //turn off
	delay_ms(250); //time between letters
}

//Led stays off for 500ms, since it is used after a letter the total time will be 750ms
void pause()
{
	delay_ms(500);
}

void displayMorse(char *message, int length)
{
	//Infinite Loop
	while(1)
	{
		//Iterates through the message
		for(int i = 0; i<strlen(message); i++)
		{
			char character = message[i];
			switch (character)
			{
			case 'A':
			case 'a':
				dot();
				dash();

				break;

			case 'B':
			case 'b':
				dash();
				dot();
				dot();
				dot();

				break;

			case 'C':
			case 'c':
				dash();
				dot();
				dash();
				dot();

				break;

			case 'D':
			case 'd':
				dash();
				dot();
				dot();

				break;

			case 'E':
			case 'e':
				dot();

				break;

			case 'F':
			case 'f':
				dot();
				dot();
				dash();
				dot();

				break;

			case 'G':
			case 'g':
				dash();
				dash();
				dot();

				break;

			case 'H':
			case 'h':
				dot();
				dot();
				dot();
				dot();

				break;

			case 'I':
			case 'i':
				dot();
				dot();

				break;

			case 'J':
			case 'j':
				dot();
				dash();
				dash();
				dash();

				break;

			case 'K':
			case 'k':
				dash();
				dot();
				dash();

				break;

			case 'L':
			case 'l':
				dot();
				dash();
				dot();
				dot();

				break;

			case 'M':
			case 'm':
				dash();
				dash();

				break;

			case 'N':
			case 'n':
				dash();
				dot();

				break;

			case 'O':
			case 'o':
				dash();
				dash();
				dash();

				break;

			case 'P':
			case 'p':
				dot();
				dash();
				dash();
				dot();

				break;

			case 'Q':
			case 'q':
				dash();
				dash();
				dot();
				dash();

				break;

			case 'R':
			case 'r':
				dot();
				dash();
				dot();

				break;

			case 'S':
			case 's':
				dot();
				dot();
				dot();

				break;

			case 'T':
			case 't':
				dash();

				break;

			case 'U':
			case 'u':
				dot();
				dot();
				dash();

				break;

			case 'V':
			case 'v':
				dot();
				dot();
				dot();
				dash();

				break;

			case 'W':
			case 'w':
				dot();
				dash();
				dash();

				break;

			case 'X':
			case 'x':
				dash();
				dot();
				dot();
				dash();

				break;

			case 'Y':
			case 'y':
				dash();
				dot();
				dash();
				dash();

				break;

			case 'Z':
			case 'z':
				dash();
				dash();
				dot();
				dot();

				break;

			case '1':
				dot();
				dash();
				dash();
				dash();
				dash();

				break;

			case '2':
				dot();
				dot();
				dash();
				dash();
				dash();

				break;

			case '3':
				dot();
				dot();
				dot();
				dash();
				dash();

				break;

			case '4':
				dot();
				dot();
				dot();
				dot();
				dash();

				break;

			case '5':
				dot();
				dot();
				dot();
				dot();
				dot();

				break;

			case '6':
				dash();
				dot();
				dot();
				dot();
				dot();

				break;

			case '7':
				dash();
				dash();
				dot();
				dot();
				dot();

				break;

			case '8':
				dash();
				dash();
				dash();
				dot();
				dot();

				break;

			case '9':
				dash();
				dash();
				dash();
				dash();
				dot();

				break;

			case '0':
				dash();
				dash();
				dash();
				dash();
				dash();

				break;

			case ' ':
				delay_ms(250); //Called after a 750ms pause already, so it total 1000ms

				break;
			}
			pause();//Adds 500ms pause after the 250ms in the dot/dash functions

		}

	}
}

/*
 * @brief   Main
 */
int main(void)
{

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();

	//Message to convert to Morse Code
	char *messageMorse = "Hello";

	SIM->SCGC5 |= 1<<12;

	PORTD->PCR[5] &= ~0x700;
	PORTD->PCR[5] |= 0x700 & (1 << 8);
	GPIOD->PDDR |= (1 << 5);
	GPIOD->PSOR |= (1<<5); //Light is off

	displayMorse(messageMorse,strlen(messageMorse));
	return 0 ;
}
