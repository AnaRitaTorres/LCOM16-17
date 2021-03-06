#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include <stdio.h>

#include "pixmap.h"

static int proc_args(int argc, char *argv[]);
static unsigned long parse_ulong(char *str, int base);
static long parse_long(char *str, int base);
static void print_usage(char *argv[]);

int main(int argc, char **argv) {

  sef_startup();
  if ( argc == 1 ) {
      print_usage(argv);
      return 0;
  } else {
      proc_args(argc, argv);
  }
  return 0;

}

static void print_usage(char *argv[]) {
	printf("Usage: one of the following:\n"
			"\t service run %s -args \"init <mode> <delay> \" \n"
			"\t service run %s -args \"square <x> <y> <size> <color>\" \n"
			"\t service run %s -args \"line <xi> <yi> <xf> <yf> <color>\" \n"
			"\t service run %s -args \"xpm <xi> <yi> <*xpm>\" \n"
			"\t service run %s -args \"move <xi> <yi> <*xpm> <hor> <delta> <time>\" \n"
			"\t service run %s -args \"controller \" \n",
			argv[0], argv[0], argv[0],argv[0],argv[0],argv[0]);
}

static int proc_args(int argc, char *argv[]) {
	char ** xpm;
	unsigned short mode,delay,x,y,size,xi,yi,xf,yf,hor,time;
	unsigned long color;
	short delta;

	if (strncmp(argv[1], "init", strlen("init")) == 0) {
		if( argc != 4 ) {
			printf("init: wrong no. of arguments for video_test_init() \n");
			return 1;
		}
		if( (mode = parse_ulong(argv[2], 16)) == ULONG_MAX )
			return 1;
		if( (delay = parse_ulong(argv[3], 10)) == ULONG_MAX )
			return 1;
		printf("video::test_init(%x, %d)\n", mode,delay);
		if ((char*) test_init(mode,delay) == NULL){
			printf("Video_test_init() function failed!\n");
			return 1;
		}
		return 0;
	} else if (strncmp(argv[1], "square", strlen("square")) == 0) {
		if( argc != 6 ) {
			printf("square: wrong no. of arguments for video_test_square() \n");
			return 1;
		}
		if( (x = parse_ulong(argv[2], 10)) == ULONG_MAX )
			return 1;
		if( (y = parse_ulong(argv[3], 10)) == ULONG_MAX )
			return 1;
		if( (size = parse_ulong(argv[4], 10)) == ULONG_MAX )
			return 1;
		if( (color = parse_ulong(argv[5], 10)) == ULONG_MAX )
			return 1;
	  printf("video::test_square (%d,%d,%d,%d)\n", x,y,size,color);
	  if (test_square(x,y,size,color))
	  {
		  printf("Video_test_square() function failed! \n");
		  return 1;
	  }
	  return 0;
  } else if (strncmp(argv[1], "line", strlen("line")) == 0) {
	  if( argc != 7 ) {
		  printf("line: wrong no. of arguments for video_test_line() \n");
		  return 1;
	  }
	  if( (xi = parse_ulong(argv[2], 10)) == ULONG_MAX )
		  return 1;
	  if( (yi = parse_ulong(argv[3], 10)) == ULONG_MAX )
		  return 1;
	  if( (xf = parse_ulong(argv[4], 10)) == ULONG_MAX )
		  return 1;
	  if( (yf = parse_ulong(argv[5], 10)) == ULONG_MAX )
		  return 1;
	  if( (color = parse_ulong(argv[6], 10)) == ULONG_MAX )
		  return 1;
	  printf("video::test_line(%d, %d, %d, %d, %d)\n",xi, yi, xf, yf, color);
	  if (test_line(xi,yi,xf,yf,color))
	  {
		  printf("Video_test_line() function failed!\n");
		  return 1;
	  }
	  return 0;
  }else if (strncmp(argv[1], "xpm", strlen("xpm")) == 0) {
	  if( argc != 5 ) {
		  printf("xpm: wrong no. of arguments for test of video_test_xpm() \n");
		  return 1;
	  }
	  if( (xi = parse_ulong(argv[2], 10)) == ULONG_MAX )
		  return 1;
	  if( (yi = parse_ulong(argv[3], 10)) == ULONG_MAX )
		  return 1;

	  if(strncmp(argv[4], "pic1", strlen("pic1")) == 0)
	  {
		  xpm = pic1;
	  }
	  else if (strncmp(argv[4], "pic2", strlen("pic2")) == 0)
	  {
		  xpm = pic2;
	  }
	  else if (strncmp(argv[4], "cross", strlen("cross")) == 0)
	  {
		  xpm = cross;
	  }
	  else if (strncmp(argv[4], "pic3", strlen("pic3")) == 0)
	  {
		  xpm = pic3;
	  }
	  else if (strncmp(argv[4], "penguin", strlen("penguin")) == 0)
	  {
		  xpm = penguin;
	  }
	  printf("video::test_xpm(%d, %d, %s)\n",xi, yi,argv[4]);
	  if (test_xpm(xi,yi,xpm))
	  {
		  printf("Video_test_xpm() function failed!\n");
		  return 1;
	  }
	  return 0;
  } else if (strncmp(argv[1], "move", strlen("move")) == 0) {
	  if( argc != 8 ) {
		  printf("move: wrong no. of arguments for test of video_test_move() \n");
		  return 1;
	  }
	  if( (xi = parse_ulong(argv[2], 10)) == ULONG_MAX )
		  return 1;
	  if( (yi = parse_ulong(argv[3], 10)) == ULONG_MAX )
		  return 1;
	  if(strncmp(argv[4], "pic1", strlen("pic1")) == 0)
	  {
		  xpm = pic1;
	  }
	  else if (strncmp(argv[4], "pic2", strlen("pic2")) == 0)
	  {
		  xpm = pic2;
	  }
	  else if (strncmp(argv[4], "cross", strlen("cross")) == 0)
	  {
		  xpm = cross;
	  }
	  else if (strncmp(argv[4], "pic3", strlen("pic3")) == 0)
	  {
		  xpm = pic3;
	  }
	  else if (strncmp(argv[4], "penguin", strlen("penguin")) == 0)
	  {
		  xpm = penguin;
	  }
	  if( (hor = parse_ulong(argv[5], 10)) == ULONG_MAX )
		  return 1;
	  if( (delta = parse_ulong(argv[6], 10)) == ULONG_MAX )
		  return 1;
	  if( (time = parse_ulong(argv[7], 10)) == ULONG_MAX )
		  return 1;
	  printf("video::test_move(%d, %d, %s,%d,%d,%d)\n",xi, yi,argv[4],hor,delta,time );
	  if (test_move(xi,yi,xpm,hor,delta,time))
	  {
		  printf("Video_test_move() function failed!\n");
		  return 1;
	  }
	  return 0;
  }
  else if (strncmp(argv[1], "controller", strlen("controller")) == 0) {
	  if( argc != 2 ) {
  		  printf("controller: wrong no. of arguments for test of video_test_controller() \n");
  		  return 1;
  	  }
  	  printf("Video_test_controller()\n");
  	  if (test_controller())
  	  {
  		  printf("Video_test_controller() function failed!\n");
  		  return 1;
  	  }
  	  return 0;
    } else {
	  printf("Function invalid \"%s\" to test\n", argv[1]);
	  return 1;
  }
}

static unsigned long parse_ulong(char *str, int base) {
  char *endptr;
  unsigned long val;

  val = strtoul(str, &endptr, base);

  if ((errno == ERANGE && val == ULONG_MAX )
	  || (errno != 0 && val == 0)) {
	  perror("strtol");
	  return ULONG_MAX;
  }

  if (endptr == str) {
	  printf("PC's video card in graphics mode: parse_ulong: no digits were found in %s \n", str);
	  return ULONG_MAX;
  }

  /* Successful conversion */
  return val;
}

static long parse_long(char *str, int base) {
  char *endptr;
  unsigned long val;

  val = strtol(str, &endptr, base);

  if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
	  || (errno != 0 && val == 0)) {
	  perror("strtol");
	  return LONG_MAX;
  }

  if (endptr == str) {
	  printf("video: parse_ulong: no digits were found in %s \n", str);
	  return LONG_MAX;
  }

  /* Successful conversion */
  return val;
}
