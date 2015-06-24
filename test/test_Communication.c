#include "unity.h"
#include "Communication.h"
#include <stdint.h>
#include <stdio.h>
#include "mock_Signal.h"

void setUp(void){}

void tearDown(void){}

void test_sendBitHigh_given_xxx_should_xxx()
{
 // printf("hello\n");

  setPinHigh_Expect(IO_PIN);
  setPinLow_Expect(CLK_PIN);
  setPinHigh_Expect(CLK_PIN);
  sendBitHigh(IO_PIN);
}

void test_sendBitLow_given_xxx_should_xxx()
{
  setPinLow_Expect(IO_PIN);
  setPinLow_Expect(CLK_PIN);
  setPinHigh_Expect(CLK_PIN);
  sendBitLow(IO_PIN);
}

void test_readTurnAroundIO()
{
  setPinToInput_Expect(IO_PIN);
  setPinLow_Expect(CLK_PIN);
  setPinHigh_Expect(CLK_PIN);

  readTurnAroundIO(IO_PIN);
}

void test_writeTurnAroundIO()
{
  setPinToOutput_Expect(IO_PIN);
  setPinLow_Expect(CLK_PIN);
  setPinHigh_Expect(CLK_PIN);

  writeTurnAroundIO(IO_PIN);
}

void test_readBit_given_xxx_should_xxx()
{
  int dataRead = 0;
  setPinHigh_Expect(CLK_PIN);
  setPinLow_Expect(CLK_PIN);
  readPin_ExpectAndReturn(IO_PIN, dataRead);
  
  TEST_ASSERT_EQUAL(dataRead,readBit(IO_PIN));
}


void test_writeData_given_0xCD_and_addr_0xDEAD_and_data_0xC0_should_sent_out_0xCDDEADC0()
{
  int i, bit;
  // printf("%x\n", 57005);
  // printf("%x\n", 0x2&1);
  //printf("%d\n",11001101);
  uint8_t cmd = 0xCD, 
          cmdTemp = cmd,
          data = 0xC0,
          dataTemp = data;
  uint16_t address = 0xdead,
           addressTemp = address;
  
  setPinToOutput_Expect(IO_PIN);
  setPinLow_Expect(CLK_PIN);
  setPinHigh_Expect(CLK_PIN);
  //writeTurnAroundIO(IO_PIN);

  for(i = 0; i<8; i++)
  {
     bit = cmdTemp & 1;
    
    if(bit == 1)
    {
      //sendBitHigh(IO_PIN)
      setPinHigh_Expect(IO_PIN);
      setPinLow_Expect(CLK_PIN);
      setPinHigh_Expect(CLK_PIN);
    }
    else
    {
      //sendBitLow(IO_PIN);
      
      //printf("Very Easy\n");
      setPinLow_Expect(IO_PIN);
      setPinLow_Expect(CLK_PIN);
      setPinHigh_Expect(CLK_PIN);
    }
    cmdTemp = cmdTemp >>1;
  }
  
  for(i = 0; i<16; i++)
  {
     bit = addressTemp & 1;
    
    if(bit == 1)
    {
      //sendBitHigh(IO_PIN)
      setPinHigh_Expect(IO_PIN);
      setPinLow_Expect(CLK_PIN);
      setPinHigh_Expect(CLK_PIN);
    }
    else
    {
      //sendBitLow(IO_PIN);
      
      //printf("**Very Easy\n");
      setPinLow_Expect(IO_PIN);
      setPinLow_Expect(CLK_PIN);
      setPinHigh_Expect(CLK_PIN);
    }
    addressTemp = addressTemp >>1;
  }
  
  for(i = 0; i<8; i++)
  {
     bit = dataTemp & 1;
    
    if(bit == 1)
    {
      //sendBitHigh(IO_PIN)
      setPinHigh_Expect(IO_PIN);
      setPinLow_Expect(CLK_PIN);
      setPinHigh_Expect(CLK_PIN);
    }
    else
    {
      //sendBitLow(IO_PIN);
      
      //printf("Very Easy\n");
      setPinLow_Expect(IO_PIN);
      setPinLow_Expect(CLK_PIN);
      setPinHigh_Expect(CLK_PIN);
    }
    dataTemp = dataTemp >>1;
  }
	writeData(cmd, address, data);
}

void test_readData_given_0xCDAB_and_addr_0xFACE_should_sent_0xABFACE_and_turnaround_and_receive_0xBE()
{
  int i, bit, dataRead = 0xBE, dataReadTemp = dataRead;
  uint8_t cmd = 0xAB, 
          cmdTemp = cmd;
  uint16_t address = 0xFACE,
           addressTemp = address;
           
  setPinToOutput_Expect(IO_PIN);
  setPinLow_Expect(CLK_PIN);
  setPinHigh_Expect(CLK_PIN);
  //writeTurnAroundIO(IO_PIN);         
 
  for(i = 0; i<8; i++)
  {
     bit = cmdTemp & 1;
    
    if(bit == 1)
    {
      //sendBitHigh(IO_PIN)
      setPinHigh_Expect(IO_PIN);
      setPinLow_Expect(CLK_PIN);
      setPinHigh_Expect(CLK_PIN);
    }
    else
    {
      //sendBitLow(IO_PIN);
      
      //printf("Very Easy\n");
      setPinLow_Expect(IO_PIN);
      setPinLow_Expect(CLK_PIN);
      setPinHigh_Expect(CLK_PIN);
    }
    cmdTemp = cmdTemp >>1;
  }
  
  for(i = 0; i<16; i++)
  {
     bit = addressTemp & 1;
    
    if(bit == 1)
    {
      //sendBitHigh(IO_PIN)
      setPinHigh_Expect(IO_PIN);
      setPinLow_Expect(CLK_PIN);
      setPinHigh_Expect(CLK_PIN);
    }
    else
    {
      //sendBitLow(IO_PIN);
      
      //printf("**Very Easy\n");
      setPinLow_Expect(IO_PIN);
      setPinLow_Expect(CLK_PIN);
      setPinHigh_Expect(CLK_PIN);
    }
    addressTemp = addressTemp >>1;
  }


	setPinToInput_Expect(IO_PIN);
  setPinLow_Expect(CLK_PIN);
  setPinHigh_Expect(CLK_PIN);
  //readTurnAroundIO(IO_PIN);  
  
  for(i = 0; i<8; i++)
  {
    bit = dataReadTemp & 1;
    setPinHigh_Expect(CLK_PIN);
    setPinLow_Expect(CLK_PIN);
    readPin_ExpectAndReturn(IO_PIN, bit); 
    dataReadTemp = dataReadTemp >>1;
  }
  
  dataRead = 0; 
  dataRead = readData(cmd, address); //jia jia de read
  TEST_ASSERT_EQUAL(0xBE,dataRead);
  printf("success\n");
}