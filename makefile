CC = cc
RM = rm
CFLAGS = -Wall -ansi -lm -std=gnu99
LIBS = -lrt

OBJ = shm_write.o shm_read.o shm_write shm_read
.SUFFIXES: 
.SUFFIXES: .c .o .h

all: shm_write shm_read

# explicit
shm_write: shm_write.o
	$(CC) $(CFLAGS) -o shm_write shm_write.o $(LIBS)
shm_read: shm_read.o
	$(CC) $(CFLAGS) -o shm_read shm_read.o $(LIBS)
# implicit

shm_write.o: shm_write.c
	$(CC) -c -g $(CFLAGS) shm_write.c
shm_read.o: shm_read.c
	$(CC) -c -g $(CFLAGS) shm_read.c
# clean up
clean:
	$(RM) -f $(OBJ)
#	$(RM) -f $(OBJ) shm_write.o shm_write shm_read.o shm_read

