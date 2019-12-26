#ifndef __MODBUS__H
#define __MODBUS__H


#define NUMBER_OF_OUTPUT_PETITREGISTERS                 5                       // Petit Modbus RTU Slave Output Register Number
                                                                                // Have to put a number of registers here
                                                                                // It has to be bigger than 0 (zero)!!
#define PETITMODBUS_TIMEOUTTIMER                        250                     // Timeout Constant for Petit Modbus RTU Slave [millisecond]

#define PETITMODBUS_READ_HOLDING_REGISTERS_ENABLED      ( 1 )                   // If you want to use make it 1, or 0
#define PETITMODBUSWRITE_SINGLE_REGISTER_ENABLED        ( 1 )                   // If you want to use make it 1, or 0
#define PETITMODBUS_WRITE_MULTIPLE_REGISTERS_ENABLED    ( 1 )                   // If you want to use make it 1, or 0

/****************************Don't Touch This**********************************/
// Buffers for Petit Modbus RTU Slave
#define PETITMODBUS_RECEIVE_BUFFER_SIZE                 (NUMBER_OF_OUTPUT_PETITREGISTERS*2 + 5) 
#define PETITMODBUS_TRANSMIT_BUFFER_SIZE                PETITMODBUS_RECEIVE_BUFFER_SIZE
#define PETITMODBUS_RXTX_BUFFER_SIZE                    PETITMODBUS_TRANSMIT_BUFFER_SIZE

// Variable for Slave Address
extern unsigned char PETITMODBUS_SLAVE_ADDRESS;                                 // Petit Modbus RTU Slave icin adres numarasi [0 to 255]

typedef struct{
            short                     ActValue;
        }PetitRegStructure;

extern PetitRegStructure    PetitRegisters[NUMBER_OF_OUTPUT_PETITREGISTERS];
extern volatile unsigned short ModbusTimerValue;

// Main Functions
extern void             InitModbus(unsigned char ModbusSlaveAddress);
extern void             ProcessModbus(void);

#include "ModbusPort.h"

#endif
