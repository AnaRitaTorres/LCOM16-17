#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include <minix/syslib.h>
#include <minix/drivers.h>
#include "i8042.h"
#include "i8254.h"
#include "timer.h"


int keyboard_subscribe_int();
int keyboard_unsubscribe_int();
int keyboard_int_handler();

#endif
