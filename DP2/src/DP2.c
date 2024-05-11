/*
* FILE        DP2.c
* PROJECT     Assignment 5
* PROGRAMMER  Jason Schneider
* DESCRIPTION  This is the main functionality for the DP2. It launched by the DP1 and given the shared memory id as an arugment.
                After the DP2 attached to shared memeory it will fork and launch the DC, giving arguments of the shared memory ID, 
                the PID of the DP2 process and the pid of the DP1 process. After the DC is forked it will begin its main logic loop
*/
#include "../../DP1/inc/DP.h"
#include "../../common/inc/Utils.h"

int done = 0;
int shmid;
HISTOGRAM *p;

/*
* FUNCTION      signalHandler
* PARAMETERS    int signal_number
* RETURN        void
* DESCRIPTION   This function handles the SIGINT that it will receive from the DC
*/
void signalHandler(int signal_number)
{

    switch (signal_number) 
    {
        case SIGINT:	//signal 2

            //detach from shared mem
            shmdt (p);
            // handle the SIGINT signal
            break;
    }
    //re init our signal handler
    signal(signal_number, signalHandler);
}

int main(int argc, char *argv[])
{
    signal(SIGCHLD, signalHandler);
    signal(SIGINT, signalHandler);
    char pid[100];// = getpid();
    char parentPid[100];// = getppid();

    shmid = atoi(argv[1]);
    key_t sem_key = ftok("../../.", 'A');
    int sem_id = semget (sem_key, 1, 0);

    //error getting semaphore ID
    if(sem_id == -1)
    {
        //printf("(DP2) Error getting semaphore ID: %s \n", strerror(errno));
        exit(1);
    }


    //printf("(DP2) SEMID %d\n", sem_id);
    sprintf(pid, "%d", getpid());
    sprintf(parentPid, "%d", getppid());
    //printf("(DP2)shared memory id is %s and my pid is %s\n", argv[1], pid);
    srand(time(NULL));
    p = (HISTOGRAM *)shmat (shmid, NULL, 0);


    //error attaching to shared memory
	if (p == NULL) 
	{
	  return 3;
	}

    //fork and start our DC process, passing it the arguments of shared memory ID, and parents PIDs
    switch(fork())
    {
        case FORK_FAILURE:
	        exit (3);
        break;
        case IS_CHILD:
            execl("../../DC/bin/DC", "DC", argv[1], pid, parentPid, (char*)NULL);
		    //if we get here there was an error in the execl so lets use errno to see what it was
	        //printf ("(DP2)Error in execl %s\n", strerror(errno));
            break;
    }


    //logic loop for the DP2
    while(done != 1)
    {

        //enter our "critial region"
        if (semop (sem_id, &acquire_operation, 1) == -1) 
        {
            printf ("(DP2)Can't start critical region\n");
            break;
        }

        //we've reached our readHeader stop writing
        if(p->writeHeader != p->readHeader)
        {
            //we've reached the end of our buffer, we need to go back to the start
            if(p->writeHeader == (MAXBUFFER-1))
            {
               // printf("(DP2)wrapping\n");
                p->writeHeader = 0;
            }

            //get a random character and write it into the buffer
            char randomCharacter = getRandomCharacter();
            p->buffer[p->writeHeader] = randomCharacter;
            p->writeHeader++;
            
        }

        //leave our "critial region"
        if (semop (sem_id, &release_operation, 1) == -1) 
        {
            break;
        }

        //sleep for 1/20th of a second
        usleep(DP2Sleep);
    }
    shmdt (p);


    return 0;
}