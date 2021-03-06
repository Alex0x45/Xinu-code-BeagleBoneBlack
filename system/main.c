/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>
int32 cpudelay;
volatile uint32	gcounter = 400000000;
process	counterproc() {

	while(gcounter > 0) {
		gcounter--;
	}
	return OK;
}

process	main(void)
{
	/* Start the network */

	//ethinit(&devtab[ETHER0]);
/*
	uint32	*macaddr = 0x44e10630;
	kprintf("mac addr: %x %x\n", *macaddr, *(macaddr+1));
	int32 i;
*/
/*	for(i = 0; i < 6; i++) {
		NetData.ethucast[i] = i;
		NetData.ethbcast[i] = 0xff;
	}*/

	//kprintf("reading packet from ETHER0\n");
	//struct netpacket pkt;
	//read(ETHER0, &pkt, 1518);

	//resume(create(counterproc, 8192, 19, "counter proc", 0, NULL));
	//sleep(10);
	//kprintf("Counter value: %d\n", gcounter);

	//DELAY(5000000);
	//netstart();

	kprintf("SPI1 %d, NDEVS %d\n", SPI1, NDEVS);
	kprintf("SPI device CSR: %x\n", devtab[SPI0].dvcsr);

	struct	spi_transfer msg;
	byte	tx[10];
	byte	rx[10];

	msg.txbuf = tx;
	msg.rxbuf = rx;
	msg.length = 5;
	tx[0] = 0xaf;
	tx[1] = 0x8f;
	memset(&tx[2], 0, 8);
	memset(rx, 0, 10);

	control(SPI0, SPI_CTRL_TRANSFER, (int32)&msg, 0);

	int	i;
	for(i = 0; i < 5; i++) {
		kprintf("%x\n", rx[i]);
	}

	kprintf("\n...creating a shell\n");
	recvclr();
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));

	/* Wait for shell to exit and recreate it */

	while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}
	return OK;
}
