#include <minix/syslib.h>
#include <minix/drivers.h>
#include "i8254.h"

int counter;
int hook_id_timer;

/*
 * Converts binary number to BCD
 */
unsigned long binaryToBCD(unsigned long n)
{
  unsigned long final=0;

  while(n > 0)
  {
      final <<= 4;
      final |= n % 10;
      n /= 10;
  }

  return final;
}


int timer_set_square(unsigned long timer, unsigned long freq)
{
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

int timer_subscribe_int( )
{
	hook_id_timer= TIMER0_IRQ;

	if (sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id_timer) == OK){
		if(sys_irqenable(&hook_id_timer)== OK)
			return 0;
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

int timer_unsubscribe_int()
{

	if( sys_irqrmpolicy(&hook_id_timer)==OK)
	{
		return 0;
	}

	else
	{
		printf("Sys_irqrmpolicy failed!\n");
		return -1;
	}

}

void timer_int_handler()
{
	counter++;
}


/*
 * Defines the selection byte for each timer
 */
unsigned long getByte(unsigned long timer)
{
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

int timer_get_conf(unsigned long timer, unsigned char *st)
{
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

int timer_display_conf(unsigned char conf)
{
	  //output
	  printf("Output: %d \n", ((conf & BIT(7))>>7));

	  //null count
	  printf("Null Count: %d \n", ((conf & BIT(6))>>6));
	  //type of access
	  printf("Type of Access:");
	  if((((conf & BIT(5))>>5)==0) && (((conf & BIT(4))>>4)==1))
		  printf("LSB\n");
	  else if((((conf & BIT(5))>>5)==1) && (((conf & BIT(4))>>4)==0))
		  printf("MSB\n");
	  else
		  printf("LSB followed by MSB\n");

	  //operating mode
	  printf("Operating Mode:");
	  if((((conf & BIT(1))>>1)==0) && (((conf & BIT(2))>>2)==0) && (((conf & BIT(3))>>3)==0))
		  printf("0\n");
	  else if((((conf & BIT(1))>>1)==1) && (((conf & BIT(2))>>2)==0) && (((conf & BIT(3))>>3)==0))
		  printf("1\n");
	  else if ((((conf & BIT(1))>>1)==0) && (((conf & BIT(2))>>2)==1) && (((conf & BIT(3))>>3)==0 || (((conf & BIT(3))>>3)==1)))
		  printf("2\n");
	  else if ((((conf & BIT(1))>>1)==1) && (((conf & BIT(2))>>2)==1) && (((conf & BIT(3))>>3)==0 || (((conf & BIT(3))>>3)==1)))
		  printf("3\n");
	  else if ((((conf & BIT(1))>>1)==0) && (((conf & BIT(2))>>2)==0) && (((conf & BIT(3))>>3)==1))
		  printf("4\n");
	  else
		  printf("5\n");


	  //bcd
	  printf("Counting Mode:");
	  if(conf & BIT(0)==1)
		  printf("BCD(4 decades)\n");
	  else
		  printf("Binary(16 bits)\n");


	  return 0;
}

int timer_test_square(unsigned long freq)
{


		if(timer_set_square(0,freq)!=0)
		{
			printf("Timer_set_square function failed!\n");
			return 1;
		}

		else return 0;
}

int timer_test_int(unsigned long time)
{
	int ipc_status;
	message msg;
	int freq =60;
	int r;
	int irq_set;
	int bit_hook_id;
	counter = 0;

	timer_set_square(0, freq);

	bit_hook_id = timer_subscribe_int();
	if(bit_hook_id  == -1)
	{
		printf("Timer_subscribe_int function failed! \n");
		return 1;
	}
	irq_set = BIT(bit_hook_id);

	while(counter < time*freq) {
			if ( (r=driver_receive(ANY, &msg, &ipc_status)) !=0 ) {
				printf("driver_receive failed with: %d", r);
				continue;
			}
			if (is_ipc_notify(ipc_status)) {
				switch (_ENDPOINT_P(msg.m_source)) {
				case HARDWARE:
					if (msg.NOTIFY_ARG & irq_set) {

						timer_int_handler();

						if (counter % freq == 0){
							printf("Second: %d\n",counter/freq);
						}
					}
					break;
				default:
					break;
				}
			} else {

			}
		}


	if(timer_unsubscribe_int() == 0)
		return 0;
	else
	{
		printf("Timer_unsubscribe_int function failed! \n");
		return 1;
	}

}

int timer_test_config(unsigned long timer)
{
	unsigned char st;

	if(timer<0 || timer>2){//checks if timer is valid
		printf("Timer value is invalid! \n");
		return 1;
	}

	if (timer_get_conf(timer, &st)==0)
	{
		if(timer_display_conf(st)==0)
			return 0;
		else
		{
			printf("Timer_display_conf function failed!\n");
			return 1;
		}
	}
	else
	{
		printf("Timer_get_conf function failed!\n");
		return 1;
	}

}
