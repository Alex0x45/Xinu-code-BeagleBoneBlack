/* userfunc.c - usermain and functions called from it */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  usermain  -  Entry point for user defined code called in main
 *------------------------------------------------------------------------
 */

#ifndef LIMIT
#define	LIMIT 200
#endif

void	sendchar(char ch)
{
	int	i;
	for(i=0; i < LIMIT; i++) 
	{
		putc(CONSOLE, ch);
	}
}

int	usermain(void)
{
	printf("\n\nUser main BEGIN\n\n");
	resume( create(sendchar, 1024, 20, "send A", 1, 'A'));
	resume( create(sendchar, 1024, 20, "send B", 1, 'B'));
	printf("\n\nUser main END\n\n");
	return 0;
}
