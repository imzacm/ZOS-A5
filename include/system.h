/*
*  Zos Attempt 5 v0.5
*  Author: Zac McChesney
*/
#ifndef __SYSTEM_H
#define __SYSTEM_H
#endif

typedef unsigned long int uint32_t;

typedef int size_t;

/* This defines what the stack looks like after an ISR was running */
struct regs
{
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;    
};

/* MAIN.C */
extern void *memcpy(void *dest, const void *src, size_t count);
extern void *memset(void *dest, char val, size_t count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count);
extern size_t strlen(const char *str);
extern unsigned char inportb (unsigned short _port);
extern void outportb (unsigned short _port, unsigned char _data);
extern int strcmp(char* str1, char* str2, int compLength);
extern void halt();

extern char * strchr (register const char *s, int c);
extern int strncmp(const char *s1, const char *s2, register size_t n);
extern char * strstr (const char *s1, const char *s2);

extern void input();
char exitLoop;
extern char * OSname;

/* CONSOLE.C */
extern void init_video(void);
extern void puts(unsigned char *text);
extern void putch(unsigned char c);
extern void cls();

/* GDT.C */
extern void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);
extern void gdt_install();

/* IDT.C */
extern void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
extern void idt_install();

/* ISRS.C */
extern void isrs_install();

/* IRQ.C */
extern void irq_install_handler(int irq, void (*handler)(struct regs *r));
extern void irq_uninstall_handler(int irq);
extern void irq_install();

/* TIMER.C */
extern void timer_wait(int ticks);
extern void timer_install();
extern char secs[2];
extern char mins[2];
extern char hours[2];

/* KEYBOARD.C */
extern void keyboard_install();
extern char shift;
extern unsigned char kbduk[128];
extern unsigned char scancode;

/* ZFS.C */
struct zfs {
	char* name;
	char type;
	char* contents;
	int id;
};
extern void init_zfs();
extern void exit_zfs();
extern void add_file(char* name, char type, char* contents);
extern void del_file(int id);
extern void ren_file(int id, char* name);
extern void list_files();

/* BEEP.C */
extern void beep();

/* SHELL.C */
extern int acceptInput;
extern void shell();
extern char inputText[1024];
extern int inputCount;

/* SCRN.C */
extern char Rows[25][80];
extern void splashScreen(char toPlace);

/* COMMANDS.C */
extern void command_help();
