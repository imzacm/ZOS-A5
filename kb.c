/*
*  Zos Attempt 5 v0.5
*  Author: Zac McChesney
*/
#include <system.h>

unsigned char kbduk[128] =
{
    0,
	'`',
	'1',
	'2',
	'3',
	'4',
	'5',
	'6',
	'7',
	'8',
	'9',
	'0',
	'-',
	'=',
	'\b',	/* Backspace */
    '\t',			/* Tab */
    'q',
	'w',
	'e',
	'r',	/* 19 */
    't',
	'y',
	'u',
	'i',
	'o',
	'p',
	'[',
	']',
	'\n',		/* Enter key */
    0,			/* 29   - Control */
    'a',
	's',
	'd',
	'f',
	'g',
	'h',
	'j',
	'k',
	'l',
	';',	/* 39 */
    '\'',
	'#',
	0,		/* Left shift */
	'\\',
	'z',
	'x',
	'c',
	'v',
	'b',
	'n',			/* 49 */
	'm',
	',',
	'.',
	'/',
	0,					/* Right shift */
	'*',
	0,	/* Alt */
	' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
	'-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
	'+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

unsigned char kbdukShift[128] =
{
    0,
	'¬',
	'!',
	'"',
	'£',
	'$',
	'%',
	'^',
	'&',
	'*',
	'(',
	')',
	'_',
	'+',
	'\b',	/* Backspace */
    '\t',			/* Tab */
    'Q',
	'W',
	'E',
	'R',	/* 19 */
    'T',
	'Y',
	'U',
	'I',
	'O',
	'P',
	'{',
	'}',
	'\n',		/* Enter key */
    0,			/* 29   - Control */
    'A',
	'S',
	'D',
	'F',
	'G',
	'H',
	'J',
	'K',
	'L',
	':',	/* 39 */
    '@',
	'~',
	0,		/* Left shift */
	'|',
	'Z',
	'X',
	'C',
	'V',
	'B',
	'N',			/* 49 */
	'M',
	'<',
	'>',
	'?',
	0,					/* Right shift */
	'*',
	0,	/* Alt */
	' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
	'-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
	'+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

char shift = 0;
char ctrl = 0;
char alt = 0;
char del = 0;
char end = 0;
unsigned char scancode;

/* Handles the keyboard interrupt */
void keyboard_handler(struct regs *r)
{
    /* Read from the keyboard's data buffer */
    scancode = inportb(0x60);

    /* If the top bit of the byte we read from the keyboard is
    *  set, that means that a key has just been released */
    if (scancode & 0x80)
    {
        /* You can use this one to see if the user released the
        *  shift, alt, or control keys... */
		if (scancode == 42 && scancode == 54)
		{
			shift = 0;
		}
		if (scancode == 29)
		{
			ctrl = 0;
		}
		if (scancode == 56)
		{
			alt = 0;
		}
		if (scancode == 79)
		{
			end = 0;
		}
		if (scancode == 83)
		{
			del = 0;
		}
    }
    else
    {
        /* Here, a key was just pressed. Please note that if you
        *  hold a key down, you will get repeated key press
        *  interrupts. */

        /* Just to show you how this works, we simply translate
        *  the keyboard scancode into an ASCII value, and then
        *  display it to the screen. You can get creative and
        *  use some flags to see if a shift is pressed and use a
        *  different layout, or you can add another 128 entries
        *  to the above layout to correspond to 'shift' being
        *  held. If shift is held using the larger lookup table,
        *  you would add 128 to the scancode when you look for it */
		if (scancode == 42 || scancode == 54)
		{
			shift = 1;
		}
		if (scancode == 29)
		{
			ctrl = 1;
		}
		if (scancode == 56)
		{
			alt = 1;
		}
		if (scancode == 79)
		{
			end = 1;
		}
		if (scancode == 83)
		{
			del = 1;
		}
		if (ctrl == 1 && alt == 1 && del == 1)
		{
			halt();
		}
		if (scancode == 82)
		{
			shell();
		}
		if (acceptInput == 1)
		{
			if (scancode == 28)
			{
				acceptInput = 0;
				inputCount = 0;
			}
			else
			{
				if (shift == 1)
				{
					putch(kbdukShift[scancode]);
					inputText[inputCount] = kbdukShift[scancode];
				}
				if (shift == 0)
				{
					putch(kbduk[scancode]);
					inputText[inputCount] = kbduk[scancode];
				}	
			}
		}	
    }
}

/* Installs the keyboard handler into IRQ1 */
void keyboard_install()
{
    irq_install_handler(1, keyboard_handler);
}
