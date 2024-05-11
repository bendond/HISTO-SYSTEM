# FINAL BINARY Target
./bin/DP1 : ./obj/DP1.o ./obj/Utils.o
	cc ./obj/DP1.o ./obj/Utils.o -o ./bin/DP1
#
# =======================================================
#                     Dependencies
# =======================================================                     
./obj/DP1.o : ./src/DP1.c ./inc/DP.h
	cc -c ./src/DP1.c -o ./obj/DP1.o
./obj/Utils.o : ../common/src/Utils.c ../common/inc/Utils.h
	cc -c ../common/src/Utils.c -o ./obj/Utils.o
#
# =======================================================
# Other targets
# =======================================================                     
all : ./bin/DP1

clean:
	rm -f ./bin/DP*
	rm -f ./obj/DP.*
	rm -f ./src/DP.c~
