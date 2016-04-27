#! /bin/bash
export PREFIX="$HOME/opt/cross/bin"
export TARGET=i686-elf
export cc="$PREFIX/$TARGET"
nasm -f elf -o start.o start.asm
$cc-gcc -Wall -Wno-pointer-sign -Wno-main -Wno-sign-compare -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o main.o main.c
$cc-gcc -Wall -Wno-pointer-sign -Wno-sign-compare -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o scrn.o scrn.c
$cc-gcc -Wall -Wno-int-conversion -Wno-pointer-sign -Wno-sign-compare -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o gdt.o gdt.c
$cc-gcc -Wall -Wno-int-conversion -Wno-pointer-sign -Wno-sign-compare -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o idt.o idt.c
$cc-gcc -Wall -Wno-pointer-sign -Wno-sign-compare -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o isrs.o isrs.c
$cc-gcc -Wall -Wno-pointer-sign -Wno-sign-compare -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o irq.o irq.c
$cc-gcc -Wall -Wno-int-conversion -Wno-pointer-sign -Wno-sign-compare -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o timer.o timer.c
$cc-gcc -Wall -Wno-overflow -Wno-multichar -Wno-pointer-sign -Wno-sign-compare -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o kb.o kb.c
$cc-gcc -Wall -Wno-int-conversion -Wno-overflow -Wno-multichar -Wno-pointer-sign -Wno-sign-compare -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o zfs.o zfs.c
$cc-gcc -Wall -Wno-pointer-sign -Wno-sign-compare -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o beep.o beep.c
$cc-gcc -Wall -Wno-pointer-sign -Wno-sign-compare -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o shell.o shell.c
$cc-ld -T link.ld -o kernel.bin start.o main.o scrn.o gdt.o idt.o isrs.o irq.o timer.o kb.o zfs.o beep.o shell.o

#makeImage
mkdir floppy
sudo mount OS.img -o loop floppy
sudo rm -rf floppy/kernel.bin
sudo cp kernel.bin floppy/kernel.bin
sudo umount floppy
rm -rf floppy

rm -rf *.o program
