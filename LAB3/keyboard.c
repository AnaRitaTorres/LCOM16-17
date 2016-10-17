#include "keyboard.h"

static int hook_id_kbd;
int HAS_2_BYTE = 0;
int keyboard_subscribe_int(){
	hook_id_kbd = IRQ_KBD;
	if (sys_irqsetpolicy(IRQ_KBD, IRQ_REENABLE|IRQ_EXCLUSIVE, &hook_id_kbd) == OK)
			return IRQ_KBD;
	else
	{
		printf("Sys_irqserpolicy failed!\n");
		return -1;
	}
}


int keyboard_unsubscribe_int(){

	if( sys_irqrmpolicy(&hook_id_kbd) ==OK)
		return 0;
	else
	{
		printf("Sys_irqrmpolicy failed!\n");
		return -1;
	}
}


int keyboard_int_handler(){
	unsigned long scan_code;
	unsigned long st;

	unsigned int c = 0;

	while(c < NUMBER_TRIES){
		if(sys_inb(STAT_REG, &st) != OK){   // verify is buffer is full
			printf("sys_inb(STAT_REG, st) function failed! \n");
			return 1;
		}
		if(st & OUTPUT_BUFFER_FULL){ //if bit(1) is set cannot write
			if(sys_inb(OUT_BUF, &scan_code) != OK)
			{
				printf("sys_inb(OUTPUT_BUFFER_FULL, scancode) function failed! \n");
				return 1;
			}
			if(((st & PARITY)|| (st & TIMEOUT)) == 1)
			{
				printf("Invalid data! \n");
				return 1;
			}

		}

		tickdelay(micros_to_ticks(DELAY_US));
		c++;
	}

	if(scan_code == TWO_BYTE_SCANCODE){
		HAS_2_BYTE = 1;
		return 0;
	}

	if(HAS_2_BYTE == 1)
	{
		scan_code = scan_code | (TWO_BYTE_SCANCODE << 8);
		HAS_2_BYTE = 0;
	}

	if(scan_code & BREAK_CODE_BIT ){

		printf("Breakcode: 0x%X \n", scan_code);
		if(scan_code == ESC)
		{
			return -1;
		}
	}
	else
		printf("Makecode: 0x%X \n", scan_code);

	return 0;
}
