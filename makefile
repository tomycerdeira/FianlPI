COMPILER=gcc -Wall -pedantic -std=c99 -fsanitize=address -g
OUTPUT_FILE=nacidos
DEBUG_COMPILER=-g -DDEBUG=1
FILES=main.c lectura.c paisADT.c querys.c

all:
	$(COMPILER) $(FILES) -o $(OUTPUT_FILE)

debug: COMPILER+=$(DEBUG_COMPILER)
debug: all

ns:COPILER = gcc -pedantic -std=c99 -Wall
ns: all

clean:
	rm -r *.o
