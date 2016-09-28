SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all: FINAL.o

FINAL.o: $(OBJS) irq.o
	i686-elf-ld -i -nostdlib -o FINAL.o $(OBJS) irq.o

%.o: %.c
	i686-elf-gcc -c -std=gnu99 -I../include -Wall $(CCFLAGS) -o $@ $<

irq.o:
	i686-elf-as irq.s -o irq.o

clean:
	rm *.o
