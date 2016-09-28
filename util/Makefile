SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all: FINAL.o

FINAL.o: $(OBJS)
	i686-elf-ld -i -nostdlib -o FINAL.o $(OBJS)

%.o: %.c
	i686-elf-gcc -c -std=gnu99 -I../include -Wall $(CCFLAGS) -o $@ $<

clean:
	rm *.o
