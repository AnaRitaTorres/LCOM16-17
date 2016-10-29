#include <minix/drivers.h>

//#include "timer.h"
static int proc_args(int argc, char *argv[]);
static unsigned long parse_ulong(char *str, int base);
static long parse_long(char *str, int base);
static void print_usage(char *argv[]);

int main(int argc, char **argv) {


	sef_startup();
	sys_enable_iop(SELF);

	if ( argc == 1 ) {
		print_usage(argv);
		return 0;
	} else {
		return proc_args(argc, argv);
	}
	return 0;

}

static void print_usage(char *argv[]) {
	printf("Usage: one of the following:\n"
			"\t service run %s -args \"scan <ass>\" \n"
			"\t service run %s -args \"leds <leds>\" \n"
			"\t service run %s -args \"timed_scan <n>\" \n",
			argv[0], argv[0], argv[0]);
}

static int proc_args(int argc, char *argv[]) {

	unsigned long ass,n;
	unsigned short *leds;

	if (strncmp(argv[1], "scan", strlen("scan")) == 0) {
		if( argc != 3 ) {
			printf("scan: wrong no. of arguments for kbd_test_scan()\n");
			return 1;
		}
		if( (ass = parse_ulong(argv[2], 10)) == ULONG_MAX )
			return 1;
		
			printf("keyboard::kbd_test_scan(%d)\n", ass);
		if( (ass != 0 && ass != 1) )
		{
			printf("Value of 'ass' is invalid. Must be 1 or 0\n");
			return 1;
		}
		if (kbd_test_scan( (unsigned short) ass) ){
			printf("kbd_test_scan function failed\n");
			return 1;
		}
		return 0;
	} else if (strncmp(argv[1], "leds", strlen("leds")) == 0) {
		if( argc <= 2 ) {
			printf("leds: wrong no. of arguments for kbd_test_leds()\n");
			return 1;
		}

		n = atoi(argv[2]);
		if (argc - 3 != n)
		{
			printf("Size of array is invalid.\n");
			return 1;
		}

		if ((leds = malloc(n * sizeof(unsigned short))) == NULL){
			return 1;
		}

		unsigned int i;
		for (i = 0; i < n; ++i){
			unsigned long e;
			if( (e = parse_ulong(argv[i+3], 10)) == ULONG_MAX )
			{
				return 1;
			}

			if( (e < 0 || e > 2) )
			{
				printf("'leds' value is invalid\n");
				return 1;
			}

			leds[i] = (unsigned short) e;
		}
		printf("keyboard::kbd_test_leds(%d, leds)\n",n);
		if (kbd_test_leds( (unsigned short) n, leds)==1){
			printf("kbd_test_leds function failed\n");
			return 1;
		}
		return 0;
	} else if (strncmp(argv[1], "timed_scan", strlen("timed_scan")) == 0) {
		if( argc != 3 ) {
			printf("timed_scan: wrong no. of arguments for kbd_test_timed_scan() \n");
			return 1;
		}
		if( (n = parse_ulong(argv[2], 10)) == ULONG_MAX )
			return 1;
		printf("keyboard::kbd_test_timed_scan(%d)\n", n);
		if (kbd_test_timed_scan(n))
		{
			printf("kbd_test_timed_scan function failed\n");
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
	/* Convert string to unsigned long */
	val = strtoul(str, &endptr, base);

	/* Check for conversion errors */
	if ((errno == ERANGE && val == ULONG_MAX )
			|| (errno != 0 && val == 0)) {
		perror("strtol");
		return ULONG_MAX;
	}
	
	if (endptr == str) {
		printf("keyboard: parse_ulong: no digits were found in %s \n", str);
		return ULONG_MAX;
	}

	/* Successful conversion */
	return val;
}

static long parse_long(char *str, int base) {
	char *endptr;
	long val;
	/* Convert string to  long */
	val = strtol(str, &endptr, base);
	
	/* Check for conversion errors */
	if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
			|| (errno != 0 && val == 0)) {
		perror("strtol");
		return LONG_MAX;
	}

	if (endptr == str) {
		printf("keyboard: parse_long: no digits were found in %s \n", str);
		return LONG_MAX;
	}

	/* Successful conversion */
	return val;
}
