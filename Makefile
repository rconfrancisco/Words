#

# define the C compiler to use
CC = g++

# define any compile-time flags
CFLAGS = -Wall -g -fpermissive -std=c++11

# define the executable file 
TARGET = Word

all: $(TARGET)

Word: Word.C
	$(CC) $(CFLAGS) -o Word Word.C

clean:
	$(RM) *.o *~ $(TARGET)

