DIROBJ := obj/
DIREXE := exec/
DIRHEA := include/
DIRSRC := src/
DIRBOOKS:= books/

CFLAGS := -I$(DIRHEA) -c -pthread -std=c++11
CC := g++

all : dirs LineaResultado SSOOIIGLE main

dirs:
	mkdir -p $(DIROBJ) $(DIREXE)

LineaResultado:
	$(CC) -o $(DIROBJ)LineaResultado.o $(DIRSRC)LineaResultado.cpp $(CFLAGS)

SSOOIIGLE: 
	$(CC) -o $(DIROBJ)SSOOIIGLE.o $(DIRSRC)SSOOIIGLE.cpp $(CFLAGS)

main:
	$(CC) -o $(DIREXE)SSOOIIGLE $(DIROBJ)SSOOIIGLE.o $(DIROBJ)LineaResultado.o -pthread -std=c++11

run-example1:
	./$(DIREXE)SSOOIIGLE $(DIRBOOKS)17\ LEYES\ DEL\ TRABAJO\ EN\ EQUIPO.txt último 67

run-example2:
	./$(DIREXE)SSOOIIGLE $(DIRBOOKS)VIVE\ TU\ SUEÑO\ -\ JOHN\ MAXWELL.txt sra 9

clean : 
	rm -rf *~ core $(DIROBJ) $(DIREXE) $(DIRHEA)*~ $(DIRSRC)*~ $(DIRBOOKS)*~


	
