#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include "i8254.h"
#include "timer.h"

// Variaveis globais
static int hook_id_timer;

Timer* newTimer(){

	Timer* timer = (Timer*) malloc(sizeof(Timer));
	timer->counter = 0;
	timer->ticked = 0;
	return timer;
}

void resetTimer(Timer* timer){
	timer->ticked = 0;
}

void deleteTimer(Timer* timer){
	free(timer);
}

unsigned long getByte(unsigned long timer){
	unsigned long byte;

	 if(timer==0)
	 {
		 byte = (TIMER_RB_CMD|TIMER_RB_COUNT_|TIMER_RB_SEL(0));
		 return byte;
	 }
	 else if (timer==1)
	 {
		 byte = (TIMER_RB_CMD|TIMER_RB_COUNT_|TIMER_RB_SEL(1));
		 return byte;
	 }
	 else if (timer==2)
	{
		byte = (TIMER_RB_CMD|TIMER_RB_COUNT_|TIMER_RB_SEL(2));
		return byte;
	}

}

int timer_get_conf(unsigned long timer, unsigned char *st){
	unsigned long byte;
	unsigned long t;

	if(timer<0 || timer>2)
	{
		printf("Timer value is invalid! \n");
		return 1;
	}

		byte=getByte(timer);
		if(sys_outb(TIMER_CTRL,byte)!=OK)
		{
			printf("SYS_OUTB function failed! \n");
			return 1;
		}

		if(timer==0)
		{
			if(sys_inb(TIMER_0,&t) != OK)
			{
				printf("SYS_INB function failed! \n");
				return 1;
			}
			*st= (unsigned char) t;
			return 0;
		}

		else if(timer==1)
		{
			if(sys_inb(TIMER_1,&t) != OK)
			{
				printf("SYS_INB function failed! \n");
				return 1;
			}
			*st= (unsigned char) t;
			return 0;
		}

		else if(timer==2)
		{
			if(sys_inb(TIMER_2,&t) != OK)
			{
				printf("SYS_INB function failed! \n");
				return 1;
			}
			*st= (unsigned char) t;
			return 0;
		}


}

int timer_set_square(unsigned long timer, unsigned long freq){
		if (timer < 0 || timer > 2)
		{
			printf("Timer value is invalid!\n");
			return 1;
		}


		if(freq < 1 || freq > TIMER_FREQ)
		{
			printf("Frequency value is invalid!\n");
			return 1;
		}

		unsigned char st;
		if(timer_get_conf(timer,&st)== 1)
		{
			printf("Timer_get_conf function failed! \n");
			return 1;
		}

		st = st & MASK;
		st = st|TIMER_LSB_MSB;

		if(timer==0)
		{
			st = st|TIMER_SEL0;
		}
		else if(timer==1)
		{
			st = st|TIMER_SEL1;
		}
		else if(timer==2)
		{
			st = st|TIMER_SEL2;
		}
		else
		{
			printf("Timer value is invalid! \n");
			return 1;
		}


		if (sys_outb(TIMER_CTRL, st) != OK)
		{
			printf("SYS_OUTB failed!\n");
			return 1;
		}


		unsigned long div = TIMER_FREQ/freq;
		if (st & TIMER_BIN != TIMER_BIN)
						div = binaryToBCD(div);

		unsigned char lsb = (char) div;
		unsigned char msb = (char) (div>>8);

		if(st & TIMER_BIN != TIMER_BIN)
		{
			msb = binaryToBCD(msb);
			lsb = binaryToBCD(lsb);
		}

		if (sys_outb(TIMER_0 + timer, lsb) !=OK)
		{
			printf("SYS_OUTB2 failed!\n");
			return 1;
		}

		if(sys_outb(TIMER_0 + timer,msb)!=OK)
		{
			printf("SYS_OUTB3 failed!\n");
			return 1;
		}

		return 0;
}

int timer_subscribe_int(){

	hook_id_timer= TIMER0_IRQ;

	if (sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id_timer) == OK){
		if(sys_irqenable(&hook_id_timer)== OK)
			return BIT(TIMER0_IRQ);
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

int timer_unsubscribe_int() {

	if(sys_irqrmpolicy(&hook_id_timer) ==OK)
		if (sys_irqdisable(&hook_id_timer) == OK)
				return 0;
			else{
				printf("Sys_irqdisable failed!\n");
				return -1;
			}
		else{
			printf("Sys_irqrmpolicy failed!\n");
			return -1;
		}

	return 0;
}

void timer_handler(Timer* timer){
	timer->ticked = 1;
	timer->counter++;
}


