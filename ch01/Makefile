
CC = gcc
#CFLAGS = -lglut -lGLU -lGL -lm
CFLAGS = -lglut -lGL
FILE = chapter.1

run : $(FILE)
	./$(FILE)

$(FILE) : $(FILE).c
	$(CC) $< -o $@ $(CFLAGS)


clean :
	rm $(FILE)


