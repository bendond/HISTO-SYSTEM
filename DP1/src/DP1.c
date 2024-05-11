/*
* FILE        DP1.c
* PROJECT     Assignment 5
* PROGRAMMER  Jason Schneider
* DESCRIPTION  Starting point for the "HISTO-SYSTEM". DP1 is responsible for creating all the IPC resources that will be used
				by this system. It will fork to start the DP2. After the DP2 is forked it will begin its logic loop of writing a "burst" of characters to
				the buffer.
*/

#include "../inc/DP.h"
#include "../../common/inc/Utils.h"

int done = 0;
static int shmid;
HISTOGRAM *p;

/*
* FUNCTION      signalHandler
* PARAMETERS    int signal_number
* RETURN        void
* DESCRIPTION   Signal handler that will handle the SIGINT that is sent from the DC process
*/
void signalHandler(int signal_number)
{
    switch (signal_number) 
    {
        case SIGINT:	//signal 2
			//detach from shared memory
			shmdt (p);
			//done = 1;
			exit(0);
            break;

    }
    //re init our signal handler
    signal(signal_number, signalHandler);
}


/*
* FUNCTION      getWriteValue
* PARAMETERS    int writeIndex
*				int readIndex
* RETURN        int
* DESCRIPTION   Gets the max number of writes the DP1 can do in its "burst" without over taking the readIndex
*/
int getWriteValue(int writeIndex, int readIndex)
{
	int retVal = 0;
	for(int i = 0; i < DP1MAX; i++)
	{
		//while our write index hasnt caught up to the read index
		if(writeIndex != readIndex)
		{
			retVal++;
			writeIndex++;
			// wrap the buffer if its reached the end
			if(writeIndex == (MAXBUFFER - 1))
			{
				writeIndex = 0;
			}
		}
		else if(writeIndex == readIndex) // we've reached the readheader
		{
			break;
		}
	}
	return retVal;
}

 

int main()
{
	
	key_t shmem_key;
	int forkReturn = 0;
	key_t sem_key;
	int sem_id;
	//setup our signal handler for SIGINT
	signal(SIGINT, signalHandler);
	srand(time(NULL));

	//get the keys for our shared memory and semaphore
	shmem_key = ftok (".", 'M');
	sem_key = ftok("../../.", 'A');


	//cant get the key exit
	if (shmem_key == -1 || sem_key == -1) 
	{ 
	  //printf ("(DP1) Cannot allocate key\n");
	  return 1;
	}
	
	//get and init semaphore
	sem_id = semget (sem_key, 1, IPC_CREAT | 0666);
	//couldnt get the semaphore exit
	if (sem_id == -1)
	{
	  exit (1);
	}
		//printf("(DP1) SEMID %d\n", sem_id);
	//cant init semaphore
	if (semctl (sem_id, 0, SETALL, init_values) == -1) 
	{
	  exit (1);
	}


	/*
	 * if shared mem exists, use it, otherwise allocate the block of memory
	 */

	if ((shmid = shmget (shmem_key, sizeof (HISTOGRAM), 0)) == -1) 
	{
		//shared memory did not exist, create it
		shmid = shmget (shmem_key, sizeof (HISTOGRAM), IPC_CREAT | 0660);
		if (shmid == -1) 
		{
		  return 2;
		}
	}



	//printf ("(DP1) Our Shared-Memory ID is %d\n", shmid);
	//printf ("(DP1) My PID is %d\n", getpid());


	//Attach DP1 to shared memory

	p = (HISTOGRAM *)shmat (shmid, NULL, 0);

	//attach failed
	if (p == NULL) 
	{
	  return 3;
	}

	//init our variables
	for (int x = 0; x < MAXBUFFER; x++) 
	{
		p->buffer[x] = 0;
	}
	p->readHeader = 0;
	p->writeHeader = 0;

	//fork our DP2 passing it the shared memory ID
	switch (fork()) 
	{
	  case FORK_FAILURE:
	  {//fork failed
	    exit (3);
	    break;
	  }
	  case IS_CHILD:
	  {
		char argBuf[MAXBUFFER];
		sprintf(argBuf, "%d", shmid);
	    execl("../../DP2/bin/DP2", "DP2", argBuf, (char*)NULL);
		//if we get here there was an error in the execl
	    exit (2);
	    break;
	  }
	}

	//main logic loop
	while(done != 1)
	{

		//enter our "critical region" to safely write characters to the buffer
		if (semop (sem_id, &acquire_operation, 1) == -1) 
		{
			exit (4);
		}
		//default wrtie amount is 20
		int maxWrites = getWriteValue(p->writeHeader, p->readHeader);

		//write as many (up to 20) characters to the buffer as we can
		for(int i = 0; i <= maxWrites; i++)
		{

			//get a random character and write it to the buffer
			char random = getRandomCharacter();
			p->buffer[p->writeHeader] = random;
			p->writeHeader++;

			//we've reached the end time to circle around
			if(p->writeHeader == (MAXBUFFER-1))
			{
				//printf("(DP1)wrapping\n");
				p->writeHeader = 0;
			}
			//we've caught up to the reader time to sleep
			if(p->writeHeader == p->readHeader)
			{
				break;
			}
		}

		if (semop (sem_id, &release_operation, 1) == -1) 
		{
			printf ("(DP1)Can't exit critical region\n");
			semctl (sem_id, 0, IPC_RMID);
			exit (6);
		}

		sleep(2);
	}
	shmdt (p);
	return 0;
}