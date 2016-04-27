/*
*  Zos Attempt 5 v0.5
*  Author: Zac McChesney
*/
#include <system.h>

/* This will keep track of how many ticks that the system
*  has been running for */
int timer_ticks = 0;

char secs[2] = {'0', '0'};
char mins[2] = {'0', '0'};
char hours[2] = {'0', '0'};

void increaseTime()
{
	secs[0]++;
		if (secs[0] == '9')
		{
			secs[1]++;
			secs[0] = '0';
		}
		if (secs[1] == '6')
		{
			mins[0]++;
			secs[1] = '0';
		}
		if (mins[0] == '9')
		{
			mins[1]++;
			mins[0] = '0';
		}
		if (mins[1] == '6')
		{
			hours[0]++;
			mins[1] = '0';
		}
		if (hours[0] == '9')
		{
			hours[1]++;
			hours[0] = '0';
		}
}

/* Handles the timer. In this case, it's very simple: We
*  increment the 'timer_ticks' variable every time the
*  timer fires. By default, the timer fires 18.222 times
*  per second. Why 18.222Hz? Some engineer at IBM must've
*  been smoking something funky */
void timer_handler(struct regs *r)
{
    /* Increment our 'tick count' */
    timer_ticks++;

    /* Every 18 clocks (approximately 1 second), we will
    *  display a message on the screen */
    if (timer_ticks % 18 == 0)
    {
		increaseTime();
		char hms[8] = {hours[1], hours[0], ':', mins[1], mins[0], ':', secs[1], secs[0]};
		//cleartime();
		puttime(hms);
    }
}

/* This will continuously loop until the given time has
*  been reached */
void timer_wait(int ticks)
{
    unsigned long eticks;

    eticks = timer_ticks + ticks;
    while(timer_ticks < eticks);
}

/* Sets up the system clock by installing the timer handler
*  into IRQ0 */
void timer_install()
{
    /* Installs 'timer_handler' to IRQ0 */
    irq_install_handler(0, timer_handler);
}
