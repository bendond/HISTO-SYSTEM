# FINAL BINARY Target
./bin/DP2 : ./obj/DP2.o ./obj/Utils.o
	cc ./obj/DP2.o ./obj/Utils.o -o ./bin/DP2
#
# =======================================================
#                     Dependencies
# =======================================================                     
./obj/DP2.o : ./src/DP2.c ../DP1/inc/DP.h
	cc -c ./src/DP2.c -o ./obj/DP2.o
./obj/Utils.o : ../common/src/Utils.c ../common/inc/Utils.h
	cc -c ../common/src/Utils.c -o ./obj/Utils.o
#
# =======================================================
# Other targets
# =======================================================                     
all : ./bin/DP2

clean:
	rm -f ./bin/DP*
	rm -f ./obj/*
