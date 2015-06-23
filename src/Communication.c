#include "Communication.h"
#include "Signal.h"
#include <stdint.h>
#include <stdio.h>


void sendBitHigh(int pinNo)
{
 // printf("what?\n");
  setPinHigh(pinNo);
  setPinLow(CLK_PIN);
  setPinHigh(CLK_PIN);
  
}

void sendBitLow(int pinNo)
{
  setPinLow(pinNo);
  setPinLow(CLK_PIN);
  setPinHigh(CLK_PIN);
}

/**
 * @brief Perform write-to-read turn around.
 * @param pinNo is the pin to do turn around
 * @steps 1) set pin as input
 *        2) set CLK pin low
 *        3) set CLK pin high
 */
void readTurnAroundIO(int pinNo)
{
  setPinToInput(pinNo);
  setPinLow(CLK_PIN);
  setPinHigh(CLK_PIN);
}

/**
 * @brief Perform write-to-read turn around.
 * @param pinNo is the pin to do turn around
 * @steps 1) set pin as input
 *        2) set CLK pin high
 *        3) set CLK pin low
 */
void writeTurnAroundIO(int pinNo)
{
  setPinToOutput(pinNo);
  setPinLow(CLK_PIN);
  setPinHigh(CLK_PIN);
}

uint32_t readBit(int pinNo)
{
  setPinHigh(CLK_PIN);
  setPinLow(CLK_PIN);
  int dataRead = readPin(pinNo);
  return dataRead;
}

void writeData(uint8_t cmd, uint16_t address, uint8_t data)
{
  int bit, i;
  
  writeTurnAroundIO(IO_PIN);
   
  for(i = 0; i<8; i++)
  {
    bit = cmd & 1;
    
    if(bit == 1)
    {
      sendBitHigh(IO_PIN);
      //printf("Yes bit = %d\n",bit);
    } 
    else    
    {
      sendBitLow(IO_PIN);
      //printf("No bit = %d\n",bit);
    }
    cmd = cmd >>1;
    //printf("bit = %d\n",bit);
  }
  
  for(i = 0; i<16; i++)
  {
    bit = address & 1;
    
    if(bit == 1)
    {
      sendBitHigh(IO_PIN);
      //printf("*addressYes bit = %d\n",bit);
    } 
    else    
    {
      sendBitLow(IO_PIN);
      //printf("*addressNo bit = %d\n",bit);
    }
    address = address >>1;
    //printf("*addressbit = %d\n",bit);
  }
  
   for(i = 0; i<8; i++)
  {
    bit = data & 1;
    
    if(bit == 1)
    {
      sendBitHigh(IO_PIN);
      //printf("Yes bit = %d\n",bit);
    } 
    else    
    {
      sendBitLow(IO_PIN);
      //printf("No bit = %d\n",bit);
    }
    data = data >>1;
    //printf("**databit = %d\n",bit);
  }

}

uint8_t readData(uint8_t cmd, uint16_t address)
{
  int bit, i;
  
  writeTurnAroundIO(IO_PIN);
  
  for(i = 0; i<8; i++)
  {
    bit = cmd & 1;
    
    if(bit == 1)
    {
      sendBitHigh(IO_PIN);
      printf("Yes bit = %d\n",bit);
    } 
    else    
    {
      sendBitLow(IO_PIN);
      printf("No bit = %d\n",bit);
    }
    cmd = cmd >>1;
    //printf("bit = %d\n",bit);
  }
  
  for(i = 0; i<16; i++)
  {
    bit = address & 1;
    
    if(bit == 1)
    {
      sendBitHigh(IO_PIN);
      //printf("*addressYes bit = %d\n",bit);
    } 
    else    
    {
      sendBitLow(IO_PIN);
      //printf("*addressNo bit = %d\n",bit);
    }
    address = address >>1;
    //printf("*addressbit = %d\n",bit);
  }
  
  readTurnAroundIO(IO_PIN);
}