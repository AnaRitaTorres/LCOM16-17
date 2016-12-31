COMPILER_TYPE= gnu

CC=gcc

PROG=	checkers

SRCS+=	main.c mouse.c vbe.c video_gr.c timer.c board.c checker.c 

SRCS+=	keyboard.c sprite.c read_xpm.c primitives.c

SRCS+= 	rtc.c

CCFLAGS= -Wall

DPADD+=	${LIBDRIVER} ${LIBSYS}

LDADD+= -llm -ldriver -lsys

LDFLAGS+= -L .

MAN=

.include <bsd.prog.mk>

.include <bsd.gcc.mk>