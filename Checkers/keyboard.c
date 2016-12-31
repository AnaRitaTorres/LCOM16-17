#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include "keyboard.h"
#include "i8042.h"

static int hook_id_kbd;
int HAS_2_BYTE = 0;
unsigned short status;

int keyboard_subscribe_int(){

	hook_id_kbd = IRQ_KBD;
	if (sys_irqsetpolicy(IRQ_KBD,IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id_kbd) == OK){
		if(sys_irqenable(&hook_id_kbd) == OK)
			return BIT(IRQ_KBD);
		else{
			printf("Sys_irqenable failed!\n");
			return -1;
		}

	}
	else{
		printf("Sys_irqserpolicy failed!\n");
		return -1;
	}
}


int keyboard_unsubscribe_int(){

	if(sys_irqrmpolicy(&hook_id_kbd) == OK)
		if (sys_irqdisable(&hook_id_kbd) == OK)
			return 0;
		else{
			printf("Sys_irqdisable failed!\n");
			return -1;
		}

	else{
		printf("Sys_irqrmpolicy failed!\n");
		return -1;
	}
}

unsigned long keyboard_read_resp(){

	unsigned long stat;
	unsigned int i=0;
	unsigned long data;
	while (1)
	{
		if(sys_inb(STAT_REG, &stat)!=OK)
		{
			printf("sys_inb function failed!\n");
			return -1;
		}
		if(stat & OUTPUT_BUFFER_FULL)
		{
			if(sys_inb(OUT_BUF, &data)!=OK)
			{
				printf("sys_inb function failed!\n");
				return -1;
			}

			if ((stat &(PARITY|TIMEOUT)) == 0){
				return data;
			}
			else if (data == ERROR)
                return data;
			else if (data == RESEND)
                return data;
			else
				return -1;

		}
		tickdelay(micros_to_ticks(DELAY_US));
		i++;
	}


}

int keyboard_get_resp(){

	unsigned int i=0;
	unsigned long data;
	do {
			data =keyboard_read_resp();
			if (data == -1) {
				printf("keyboard_read_resp function failed\n");
				return 1;
			}
			else
				return data;

			i++;
		} while (data != ACK && i < NUMBER_TRIES);

	if(i >= NUMBER_TRIES)
	{
		printf("Way too many tries! \n");
		return 1;
	}

}





