/*
 * frdm_i2c.h
 *
 *  Created on: Mar 26, 2021
 *      Author: dauma
 */

#ifndef FRDM_I2C_H_
#define FRDM_I2C_H_

void initI2C();
void clearStatusFlags();
void TCFWait();
void IICIFWait();
void SendStart();
void RepeatStart();
void SendStop();
void clearIICIF();
int RxAK();
void WriteByte (char registerAddress, char Data);
int ReadBlock(char registerAddress, signed char* array,int Length);

#endif /* FRDM_I2C_H_ */
