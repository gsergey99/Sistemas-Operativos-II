DIROBJ := obj/
DIREXE := exec/
DIRHEA := include/
DIRSRC := src/

CFLAGS := -I$(DIRHEA) -c -pthread -std=c++11
CC := g++

all : dirs Food_DrinkMsg SemCounter TicketMsg PayMsg ventas_online main

dirs:
	mkdir -p $(DIROBJ) $(DIREXE)

Food_DrinkMsg:
	$(CC) -o $(DIROBJ)Food_DrinkMsg.o $(DIRSRC)Food_DrinkMsg.cpp $(CFLAGS)

SemCounter: 
	$(CC) -o $(DIROBJ)SemCounter.o $(DIRSRC)SemCounter.cpp $(CFLAGS)

TicketMsg: 
	$(CC) -o $(DIROBJ)TicketMsg.o $(DIRSRC)TicketMsg.cpp $(CFLAGS)

PayMsg: 
	$(CC) -o $(DIROBJ)PayMsg.o $(DIRSRC)PayMsg.cpp $(CFLAGS)

ventas_online: 
	$(CC) -o $(DIROBJ)ventas_online.o $(DIRSRC)ventas_online.cpp $(CFLAGS)

main:
	$(CC) -o $(DIREXE)ventas_online $(DIROBJ)ventas_online.o $(DIROBJ)Food_DrinkMsg.o $(DIROBJ)TicketMsg.o $(DIROBJ)SemCounter.o $(DIROBJ)PayMsg.o -pthread -std=c++11

run-example1:
	./$(DIREXE)ventas_online 7

run-example2:
	./$(DIREXE)ventas_online 30

run-error:
	./$(DIREXE)ventas_online error

clean : 
	rm -rf *~ core $(DIROBJ) $(DIREXE) $(DIRHEA)*~ $(DIRSRC)*~ 


	
