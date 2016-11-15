#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_


#include "i8254.h"

//keyboard

#define NUMBER_TRIES						6

#define DELAY_US 							20000

#define SHIFT_LEFT(arg,n)      (arg << n)

#define BREAK_CODE_BIT						BIT(7)

#define IRQ_KBD                    			1

#define STAT_REG			    			0x64
#define OUT_BUF 							0x60

#define TWO_BYTE_SCANCODE        			0xE0
#define ESC                     			0x81

// LEDS 
#define KBD_SWITCH_LED                      0xED


//RESPONSES
#define	ACK									0xFA
#define RESEND								0xFE
#define ERROR								0xFC
#define RESET 								0xFF

//PORTS
#define KBD_CMD_REG							0x60
#define KBC_CMD_REG							0x64


//STATUS REGISTER
#define OUTPUT_BUFFER_FULL					BIT(0)
#define INPUT_BUFFER_FULL					BIT(1)
#define SYSTEM_FLAG                         BIT(2)
#define A2									BIT(3)
#define INHIBIT_FLAG						BIT(4)
#define TIMEOUT 							BIT(6)
#define PARITY	   							BIT(7)


//mouse
#define PACKET_SIZE    						3
#define IRQ_MOUSE                           12
#define DEVIATION 							4

#define READ_CMD_BYTE                       0x20
#define WRITE_CMD_BYTE                      0x60
#define DIS_MOUSE                           0xA7
#define EN_MOUSE  							0xA8
#define CHECK_MOUSE_INTER					0xA9
#define MOUSE_CMD_REG						0xD4

//MOUSE COMMANDS


#define RESET 								0xFF
#define SET_DEFAULTS 						0xF6
#define DISABLE								0xF5
#define ENABLE 								0xF4
#define SET_SAMPLE_RATE 					0xF3
#define SET_REMOTE_MODE 					0xF0
#define READ_DATA 							0xEB
#define SET_STREAM_MODE 					0xEA
#define STATUS_REQUEST 						0xE9
#define SET_RESOLUTION 						0xE8


//responses
#define ACK 								0xFA
#define NACK 								0xFE
#define ERROR 								0xFC

#endif
