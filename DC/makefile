# FINAL BINARY Target
./bin/DC : ./obj/DC.o
	cc ./obj/DC.o -o ./bin/DC
#
# =======================================================
#                     Dependencies
# =======================================================                     
./obj/DC.o : ./src/DC.c ./inc/DC.h
	cc -c ./src/DC.c -o ./obj/DC.o
#
# =======================================================
# Other targets
# =======================================================                     
all : ./bin/DC

clean:
	rm -f ./bin/DC*
	rm -f ./obj/*
