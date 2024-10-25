
CC = gcc                   
CFLAGS = -Wall -g
TARGET = launch      
SOURCES = main.c commands/show.c commands/pwd.c commands/cdir.c commands/rdir.c commands/go.c commands/cls.c commands/rfile.c commands/mv.c commands/man.c commands/cfile.c commands/cp.c commands/disp.c


OBJECTS = $(SOURCES:.c=.o)



all: $(TARGET)
	./$(TARGET)



$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)



%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

	


clean:
	rm -f $(TARGET)




.PHONY: all clean
