
# the compiler: gcc for C program
CC=gcc

# compiler flags:
CFLAGS=-pipe -Wall -O3 -fomit-frame-pointer -march=ivybridge -fopenmp

# directory containing hearder files
INCLUDES=-I/usr/local/apr/include/apr-1

# library paths:
LFLAGS=-L/usr/local/apr/lib -fopenmp

# library to link into executable
LIBS=-lapr-1 

# C source file
SRCS=binary-trees.c

# C object file
# chance .c in SRSC by .o
OBJS=$(SRCS:.c=.o)

# executable file
MAIN=binary-trees

.PHONY: depend clean

all:	$(MAIN)
	@echo File compiled

$(MAIN): $(OBJS)
	$(CC) $(OBJS) -o $(MAIN)  $(LFLAGS) $(LIBS)

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRCS)

clean:
	$(RM) *.o *~ $(MAIN)
