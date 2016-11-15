#ifndef __MOUSE_H
#define __MOUSE_H

#include <minix/syslib.h>
#include <minix/drivers.h>
#include "i8254.h"
#include "i8042.h"
#include "timer.h"


typedef enum {INIT, DRAW, COMP} state_t;
typedef enum {RDOW, RUP, MOVE} ev_type_t;

typedef struct{
        ev_type_t type;
}ev_t;

int mouse_subscribe_int();

int mouse_unsubscribe_int();

int mouse_write_cmd_kbd(unsigned long command);

int mouse_write_cmd_kbc(unsigned long command);

unsigned long mouse_read_resp();

unsigned long read_from_buffer();

int mouse_set_stream_mode();

int mouse_dis_stream_mode();

int mouse_write_config(unsigned long cmd);

unsigned int bit(int bit, unsigned long byte);

void mouse_set_package();

int mouse_get_packet();

void mouse_set_config();

int mouse_get_config();

int handle_mouse(int length);

int check_line(ev_t *evt, int length);

#endif
