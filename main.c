/*
*  Zos Attempt 5 v0.5
*  Author: Zac McChesney
*/
#include <system.h>
#include <multiboot.h>

char * strchr (register const char *s, int c)
{
  do {
    if (*s == c)
      {
	return (char*)s;
      }
  } while (*s++);
  return (0);
}

int strncmp(const char *s1, const char *s2, register size_t n)
{
  register unsigned char u1, u2;

  while (n-- > 0)
    {
      u1 = (unsigned char) *s1++;
      u2 = (unsigned char) *s2++;
      if (u1 != u2)
	return u1 - u2;
      if (u1 == '\0')
	return 0;
    }
  return 0;
}

char * strstr (const char *s1, const char *s2)
{
  const char *p = s1;
  const size_t len = strlen (s2);

  for (; (p = strchr (p, *s2)) != 0; p++)
    {
      if (strncmp (p, s2, len) == 0)
	return (char *)p;
    }
  return (0);
}

int strcmp(char* str1, char* str2, int compLength) //returns 0 if same, 1 if not
{
	int returnValue= 0;
	for (int i = 0; i < compLength; i++)
	{
		if (str1[i] != str2[i])
		{
			returnValue = 1;
		}
	}
	return returnValue;
}

void *memcpy(void *dest, const void *src, size_t count)
{
    const char *sp = (const char *)src;
    char *dp = (char *)dest;
    for(; count != 0; count--) *dp++ = *sp++;
    return dest;
}

void *memset(void *dest, char val, size_t count)
{
    char *temp = (char *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count)
{
    unsigned short *temp = (unsigned short *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

size_t strlen(const char *str)
{
    size_t retval;
    for(retval = 0; *str != '\0'; str++) retval++;
    return retval;
}

unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

void on_exit()
{
	exit_zfs();
	irq_uninstall_handler(0);
	irq_uninstall_handler(1);
}

void halt()
{
	on_exit();
	puts("Halting ...");
	beep();
	asm volatile ("cli");
	while ((inportb(0x64) & 0x02) != 0);
	outportb(0x60, 0xfe);
	outportb (0xB004, 0x2000);
}

void input()
{	
	puts("You said ");
	for (int i = 0; i < inputCount; i++)
	{
		putch(inputText[i]);
	}
	puts("\n");
	inputCount = 0;
}

void main(unsigned int ebx)
{
	//multiboot_info_t *mbinfo = (multiboot_info_t *) ebx;
    //unsigned int address_of_module = mbinfo->mods_addr;
	//uint32_t modcount = mbinfo->mods_count;
    gdt_install();
    idt_install();
    isrs_install();
    irq_install();
    init_video();
    keyboard_install();
    timer_install();

    __asm__ __volatile__ ("sti");
	
	puts("Zos Attempt 5 v0.5\n");
	puts("Ctrl + Alt + Del = Halt\n");
	
	puts("User>");
	acceptInput = 1;
	
    for (;;);
}
