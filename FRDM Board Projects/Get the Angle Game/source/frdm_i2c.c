/*
 * frdm_i2c.c
 *
 *  Created on: Mar 26, 2021
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

void initI2C() {
    // Enable Clock Gating for I2C module and Port
    SIM->SCGC4 |= (1 << 6);
    SIM->SCGC5 |= (1 << 13);

    // Setup Pin Mode for I2C
    PORTE->PCR[24] |= (0x5 << 8);
    PORTE->PCR[25] |= (0x5 << 8);

    // Write 0 to all I2C registers
    I2C0->A1 = 0;
    I2C0->F = 0;
    I2C0->C1 = 0;
    I2C0->S = 0;
    I2C0->D = 0;
    I2C0->C2 = 0;
    I2C0->FLT = 0;
    I2C0->RA = 0;
    I2C0->SMB = 0;
    I2C0->A2 = 0;
    I2C0->SLTH = 0;
    I2C0->SLTL = 0;

    // Write 0x50 to FLT register (clears all bits)
    I2C0->FLT = 0x50;

    // Clear status flags
    clearStatusFlags();

    // Set I2C Divider Register (Choose a clock frequency less than 100 KHz
    I2C0->F = 0x2E;

    // Set bit to enable I2C Module
    I2C0->C1 |= (0x1 << 7);
}

void clearStatusFlags() {
    // Clear STOPF and Undocumented STARTF bit 4 in Filter Register
    I2C0->FLT |= 0x50;
    // Clear ARBL and IICIF bits in Status Register
    I2C0->S |= 0x12;
}

void TCFWait() {
    // Wait for TCF bit to Set in Status Register
    while (!(I2C0->S & 0x80)) {}
}

void IICIFWait() {
    // Wait for IICIF bit to Set in Status Register
    while (!(I2C0->S & 0x02)) {}
}


void SendStart() {
    // Set MST and TX bits in Control 1 Register
    I2C0->C1 |= ((1 << 5) | (1 << 4));
}

void RepeatStart() {
    // Set MST, TX and RSTA bits in Control 1 Register
    I2C0->C1 |= ((1 << 5) | (1 << 4) | (1 << 2));
    // Wait 6 cycles
    for (int i = 0; i < 6; i++)
    {
    	__asm volatile ("nop");
    }
}

void SendStop() {
    // Clear MST, TX and TXAK bits in Control 1 Register
	I2C0->C1 &= ~((1<<5) | (1<<4) | (1<<3));
    // Wait for BUSY bit to go low in Status Register
	while (I2C0->S & (1<<5)){}
}

void clearIICIF() {
    // Clear IICIF bit in Status Register
	I2C0->S |= 0x02;
}

int RxAK() {
    // Return 1 if byte has been ACK'd. (See RXAK in Status Register)
	if (!(I2C0->S & 0x01))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


void WriteByte (char registerAddress, char data)
{
    clearStatusFlags();
    TCFWait();
    SendStart();

    // TODO: Write Device Address, R/W = 0 to Data Register
    I2C0->D = (0x1D << 1);


    IICIFWait();

    if (!RxAK()){
        printf("NO RESPONSE - Address");
        SendStop();
        return;
    }

    clearIICIF();

    // TODO: Write Register address to Data Register
    I2C0->D = registerAddress;

    IICIFWait();
    if (!RxAK()){
        printf("NO RESPONSE - Register");
        SendStop();
        return;
    }

    TCFWait();
    clearIICIF();

    // Write Data byte to Data Register
    I2C0->D = data;


    IICIFWait();
    if (!RxAK()){
        printf("Incorrect ACK - Data");
    }

    clearIICIF();
    SendStop();
}

int ReadBlock(char registerAddress, signed char* array, int length)
{
    unsigned char dummy = 0;
    clearStatusFlags();
    TCFWait();
    SendStart();

    dummy++;  // Do something to suppress the warning.

    //TODO: Write Device Address, R/W = 0 to Data Register
    I2C0->D = (0x1D << 1);

    IICIFWait();

    if (!RxAK()){
        printf("NO RESPONSE - Address");
        SendStop();
        return 0;
    }

    clearIICIF();

    // Write Register address to Data Register
    I2C0->D = registerAddress;

    IICIFWait();
    if (!RxAK()){
        printf("NO RESPONSE - Register");
        SendStop();
        return 0;
    }

    clearIICIF();
    RepeatStart();

    // Write device address again, R/W = 1 to Data Register
    I2C0->D = ((0x1D << 1) | 1);

    IICIFWait();
    if (!RxAK()){
        printf("NO RESPONSE - Restart");
        SendStop();
        return 0;
    }

    TCFWait();
    clearIICIF();

    // Switch to RX by clearing TX and TXAK bits in Control 1 register
    I2C0->C1 &= ~((1 << 4) | (1 << 3));

    if(length == 1){
        // Set TXAK to NACK in Control 1 - No more data!
    	I2C0->C1 |= (1<<3);
    }

    dummy = I2C0->D; // Dummy Read

    for(int index=0; index<length; index++){
        IICIFWait();
        clearIICIF();

        if(index == length-2){
            // Set TXAK to NACK in Control 1 - No more data!
        	I2C0->C1 |= (1<<3);
        }

        if(index == length-1){
            SendStop();
        }
        // Read Byte from Data Register into Array
        array[index]=I2C0->D;
        //printf("Who am I: %x",array[index]);
    }
    return 1;
}


