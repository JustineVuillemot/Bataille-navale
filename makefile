
TARGET = executable
##########################################################"

CFLAGS = gcc -g -O2 -Wall -Werror `pkg-config --cflags MLV`
LDLIBS = `pkg-config --libs MLV`

all: executable

executable: main.c functions.c solo.c deux_joueurs.c ordinateur.c functions.h solo.h deux_joueurs.h ordinateur.h
	$(CFLAGS) main.c functions.c solo.c deux_joueurs.c ordinateur.c $(LDLIBS) -o executable

#main.o: main.c
#	$(CFLAGS) main.c $(LDLIBS) -o main

#functions.o: functions.c functions.h
#	$(CFLAGS) functions.c $(LDLIBS) -o functions

#solo.o: solo.c functions.h
#	$(CFLAGS) solo.c $(LDLIBS) -o solo

clean:
	-rm -rf *.o

