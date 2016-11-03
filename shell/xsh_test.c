/* xsh_test.c - xsh_test */

#include <xinu.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * xhs_test - test concurrent processes
 *------------------------------------------------------------------------
 */

#ifndef LIMIT
#define	LIMIT 120
#endif

void	sendchar(char ch)
{
	int	i;
	for(i=0; i < LIMIT; i++) 
	{
		putc(CONSOLE, ch);
	}
}

shellcmd xsh_test(int nargs, char *args[])
{
	printf("\n\nTest BEGIN\n\n");
	resume( create(sendchar, 1024, 20, "send A", 1, 'A'));
	resume( create(sendchar, 1024, 20, "send B", 1, 'B'));
	printf("\n\nTest END\n\n");
	return 0;
}
