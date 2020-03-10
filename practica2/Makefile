DIROBJ := obj/
DIREXE := exec/
DIRHEA := include/
DIRSRC := src/

CFLAGS := -I$(DIRHEA) -c -Wall -ansi
LDLIBS := -lpthread -lrt
CC := g++

all : dirs main

dirs:
	mkdir -p $(DIROBJ) $(DIREXE)

main: $(DIROBJ)main.o 
	$(CC) -o $(DIREXE)$@ $^ $(LDLIBS)


$(DIROBJ)%.o: $(DIRSRC)%.cpp
	$(CC) $(CFLAGS) $^ -o $@

run:
	./$(DIREXE)main

solution:
	./$(DIREXE)manager 2 3 4

clean : 
	rm -rf *~ core $(DIROBJ) $(DIREXE) $(DIRHEA)*~ $(DIRSRC)*~
	rm -rf 0*
	rm -rf 55*
	rm -rf 75*

	
