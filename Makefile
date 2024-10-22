
CC = gcc                   
CFLAGS = -Wall -g
TARGET = launch      
SOURCES = main.c commands/show.c commands/pwd.c commands/cdir.c commands/rdir.c

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
