#include <minix/syslib.h>
#include <minix/drivers.h>


#include "rtc.h"

static int hook_id;

int rtc_subscribe()
{
	hook_id = RTC_HOOK;

	int bitmask = BIT(hook_id);
	/*The policy you should specify in sys_irqsetpolicy() is IRQ_REENABLE, so
	 that the generic interrupt handler will acknowledge the interrupt. */
	if (sys_irqsetpolicy(RTC_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id) != 0
			|| sys_irqenable(&hook_id) != 0) {
		printf("\ntimer_subscribe_int() failed \n");
		return -1;
	} else {
		return bitmask;
	}
}

int rtc_unsubscribe()
{
	if (sys_irqdisable(&hook_id) != 0) {
		printf("rtc_unsubscribe failed \n");
		return 1;
	}
	if (sys_irqrmpolicy(&hook_id) != 0) {
		printf("rtc_unsubscribe failed \n");
		return 1;
	}
	return 0;
}


unsigned long read_bcd(unsigned long date) {

	date=(((date& 0xF0) >> 4) * 10 + (date & 0x0F));
	return date;
}

void rtc_read(unsigned long reg, unsigned long* data)
{
		sys_outb(ADDR_REG, reg);
		sys_inb(DATA_REG, data);
}


rtc_time_t rtc_read_date()
{
	rtc_time_t date;

	rtc_read(YEAR,&date.year);
	rtc_read(MONTH,&date.month);
	rtc_read(DAY, &date.day);
	rtc_read(HOURS,&date.hours);
	rtc_read(MINUTES, &date.minutes);
	rtc_read(SECONDS,&date.seconds);

	rtc_time_t t;

	t.seconds = read_bcd(date.seconds);
	t.minutes = read_bcd(date.minutes);
	t.hours = read_bcd(date.hours);

	t.day = read_bcd(date.day);
	t.month = read_bcd(date.month);
	t.year = read_bcd(date.year);

	return t;
}



