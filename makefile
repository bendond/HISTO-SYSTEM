# FINAL BINARY Target for all
./bin/DP2 : ./DP2/obj/DP2.o ./DP2/obj/Utils.o
	cc ./DP2/obj/DP2.o ./DP2/obj/Utils.o -o ./DP2/bin/DP2
./bin/DP1 : ./DP1/obj/DP1.o ./DP1/obj/Utils.o
	cc ./DP1/obj/DP1.o ./DP1/obj/Utils.o -o ./DP1/bin/DP1
./bin/DC : ./DC/obj/DC.o
	cc ./DC/obj/DC.o -o ./DC/bin/DC
#
# =======================================================
#                     Dependencies
# =======================================================                     
./DP2/obj/DP2.o : ./DP2/src/DP2.c ./DP1/inc/DP.h
	cc -c ./DP2/src/DP2.c -o ./DP2/obj/DP2.o
./DP2/obj/Utils.o : ./common/src/Utils.c ./common/inc/Utils.h
	cc -c ./common/src/Utils.c -o ./DP2/obj/Utils.o
	
./DP1/obj/DP1.o : ./DP1/src/DP1.c ./DP1/inc/DP.h
	cc -c ./DP1/src/DP1.c -o ./DP1/obj/DP1.o
./DP1/obj/Utils.o : ./common/src/Utils.c ./common/inc/Utils.h
	cc -c ./common/src/Utils.c -o ./DP1/obj/Utils.o
	
./DC/obj/DC.o : ./DC/src/DC.c ./DC/inc/DC.h
	cc -c ./DC/src/DC.c -o ./DC/obj/DC.o
#
# =======================================================
# Other targets
# =======================================================                     
all : ./bin/DP2 ./bin/DP1 ./bin/DC

clean:
	rm -f ./DP2/bin/DP*
	rm -f ./DP2/obj/*
	rm -f ./DP1/bin/DP*
	rm -f ./DP1/obj/*
	rm -f ./DC/bin/DC*
	rm -f ./DC/obj/*
