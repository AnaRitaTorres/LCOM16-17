#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_


#include "i8254.h"

#define NUMBER_TRIES						6

#define DELAY_US 							20000

#define SHIFT_LEFT(arg,n)      				(arg << n)
#define BREAK_CODE(scancode)   				(scancode & BIT(7))
#define BREAK_CODE_BIT						BIT(7)

#define IRQ_KBD                    			1


#define STAT_REG			    			0x64
#define OUT_BUF 							0x60

#define TWO_BYTE_SCANCODE        			0xE0
#define ESC                     			0x81

// LEDS 
#define KBD_SWITCH_LED						0xED

//RESPONSES
#define	ACK									0xFA
#define RESEND								0xFE
#define ERROR								0xFC

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




#endif
