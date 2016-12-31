# Makefile for lab4

COMPILER_TYPE= gnu

CC= gcc

PROG= lab5 
SRCS= lab5.c timer.c keyboard.c test5.c video_gr.c read_xpm.c vbe.c
CCFLAGS= -Wall

DPADD+= ${LIBDRIVER} ${LIBSYS}
LDADD+= -llm -ldriver -lsys

LDFLAGS+= -L .

MAN=

.include <bsd.prog.mk>
.include <bsd.gcc.mk>
