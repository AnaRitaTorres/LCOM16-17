#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include <minix/syslib.h>
#include <minix/drivers.h>
#include "i8042.h"
#include "i8254.h"
#include "timer.h"

int keyboard_subscribe_int();
int keyboard_unsubscribe_int();
int keyboard_scan_c();
int keyboard_scanning(unsigned long scan_code);
int keyboard_leds(unsigned int led);
int keyboard_write_cmd(unsigned long command);
unsigned long keyboard_read_resp(unsigned long data);
int keyboard_get_resp(unsigned long command, unsigned long data);
void keyboard_print_led(unsigned short status);

#endif
