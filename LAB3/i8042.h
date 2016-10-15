#ifndef _I8042_H
#define _I8042_H

#include "i8254.h"

#define NUMBER_TRIES			5
// SCAN

#define DELAY_US 20000

#define SHIFT_LEFT(arg,n)      (arg << n)
#define BREAK_CODE(scancode)   (scancode & BIT(7))
#define BREAK_CODE_BIT			BIT(7)

#define IRQ_KBD                    1
#define STATUS_REGISTER		    0x64
#define OUT_BUF 				0x60
#define 2_BYTE_SCANCODE        	0xE0
#define ESC_BREAK_CODE          0x81
#define STOP					  -1

#define KBD_HOOK_NOTIFICATION	   1


#define false					   0
#define true					   1




// LEDS 


#define KBD_SWITCH_LED			0xED
//RESPONSES
#define	ACK						0xFA
#define RESEND					0xFE
#define ERROR					0xFC
//PORTS
#define KBD_CMD_REG				0x60
#define KBC_CMD_REG				0x64

#define IBF					    BIT(1)
#define OBF						BIT(0)
#define PAR_ERR					BIT(7)
#define TIMEOUT 				BIT(6)






#endif
