/*
* FILE        DC.c
* PROJECT     Assignment 5
* PROGRAMMER  Beunard Lecaj, Jason Schneider
* DESCRIPTION  This is the main functionality for the DC application which will count the letters
*               within the buffer and display a histogram
*/

#include "../../common/inc/Utils.h"
#include "../../DP1/inc/DP.h"

#define letMax 20

int done = 0;
int timeToRead = FALSE;
int pPid;
int ppPid;
int tTime = 0;
int finalRead = FALSE;

typedef struct
{
    int lc[letMax];
} letterCount;


/*
* FUNCTION      signalHandler
* PARAMETERS    int signal_number
* RETURN        void
* DESCRIPTION   This is the signal handler for SIGINT 
*/
void signalHandler(int signal_number)
{

    switch (signal_number) 
    {
        case SIGINT:	//when the DC recieves a SIGINT it will kill the DP1 and DP2
            finalRead = TRUE;
            kill(pPid, SIGINT);
            kill(ppPid, SIGINT);
			//done = 1;

            break;

    }
    //re init our signal handler
    signal(signal_number, signalHandler);
}


/*
* FUNCTION      displayHandler
* PARAMETERS    int signalType
* RETURN        void
* DESCRIPTION   This is the signal handler for our alarm every 2 seconds
*/
void displayHandler(int signalType)
{
    timeToRead = TRUE;
    //re init our alarm to display the content again
    tTime++;
    alarm(2);
    signal(signalType, displayHandler);

}


/*
* FUNCTION      displayHis
* PARAMETERS    letterCount *lC
* RETURN        void
* DESCRIPTION   This is the function for the display of the histogram with the letters counted in
*               letterCount Struct
*/
void displayHis(letterCount *lC)
{
    int tmp = 0;
    int h, t, u;
    int flag = 0;
    system("clear");
    for (int n = 0; n < letMax; n++)
    {
        tmp = lC->lc[n];
        char L;
        //Getting the letter for the specified int array we enter
        if (n==0)
            L = 'A';
        if (n==1)
            L = 'B';
        if (n==2)
            L = 'C';
        if (n==3)
            L = 'D';
        if (n==4)
            L = 'E';
        if (n==5)
            L = 'F';
        if (n==6)
            L = 'G';
        if (n==7)
            L = 'H';
        if (n==8)
            L = 'I';
        if (n==9)
            L = 'J';
        if (n==10)
            L = 'K';
        if (n==11)
            L = 'L';
        if (n==12)
            L = 'M';
        if (n==13)
            L = 'N';
        if (n==14)
            L = 'O';
        if (n==15)
            L = 'P';
        if (n==16)
            L = 'Q';
        if (n==17)
            L = 'R';
        if (n==18)
            L = 'S';
        if (n==19)
            L = 'T';

        //format for each letter
        printf("%c-%d ", L, tmp);

        u = tmp%10;
        t = (tmp/10)%10;
        h = (tmp/100)%10;

        //formatting the symbols per required amount in buffer
        for (int i = 0; i < h; i++)
            printf("*");

        for (int i = 0; i < t; i++)
            printf("+");
            
        for (int i = 0; i < u; i++)
            printf("-");
        printf("\n");

    }
    printf("\n\n");

    return;

}

int main(int argc, char* argv[])
{
    signal(SIGINT, signalHandler);
    //shared memory id
    int shmid = atoi(argv[1]);
    //parent PID
    pPid = atoi(argv[2]);
    //parents parent PID
    ppPid = atoi(argv[3]);
    key_t sem_key = ftok("../../.", 'A');
    int sem_id = semget (sem_key, 1, 0);
    int count[87];
    int countIndex = 0;

    //error with semaphore ID
    if(sem_id == -1)
    {
        exit(1);
    }

    letterCount *lC = malloc(sizeof(letterCount));
    HISTOGRAM *p;

    p = (HISTOGRAM *)shmat (shmid, NULL, 0);
	if (p == NULL) 
	{
	  return 3;
	}

    signal (SIGALRM, displayHandler);

    // set the watch-dog to go off in 2 seconds ...
    alarm (2);


    //logic loop for the DC
    while(done == 0)
    {

        //if it cant enter our "critical region"
        if (semop (sem_id, &acquire_operation, 1) == -1) 
        {
            exit (4);
        }
        if(timeToRead == TRUE)
        {
            for(int i=0; i < READVALUE; i++)
            {
                if (p->buffer[p->readHeader] != '\0')   //as long as not endofline
                {
                        //counter for each letter scanned
                    if (p->buffer[p->readHeader] == 'A')
                        lC->lc[0]++;
                    if (p->buffer[p->readHeader] == 'B')
                        lC->lc[1]++;
                    if (p->buffer[p->readHeader] == 'C')
                        lC->lc[2]++;
                    if (p->buffer[p->readHeader] == 'D')
                        lC->lc[3]++;
                    if (p->buffer[p->readHeader] == 'E')
                        lC->lc[4]++;
                    if (p->buffer[p->readHeader] == 'F')
                        lC->lc[5]++;
                    if (p->buffer[p->readHeader] == 'G')
                        lC->lc[6]++;
                    if (p->buffer[p->readHeader] == 'H')
                        lC->lc[7]++;
                    if (p->buffer[p->readHeader] == 'I')
                        lC->lc[8]++;
                    if (p->buffer[p->readHeader] == 'J')
                        lC->lc[9]++;
                    if (p->buffer[p->readHeader] == 'K')
                        lC->lc[10]++;
                    if (p->buffer[p->readHeader] == 'L')
                        lC->lc[11]++;
                    if (p->buffer[p->readHeader] == 'M')
                        lC->lc[12]++;
                    if (p->buffer[p->readHeader] == 'N')
                        lC->lc[13]++;
                    if (p->buffer[p->readHeader] == 'O')
                        lC->lc[14]++;
                    if (p->buffer[p->readHeader] == 'P')
                        lC->lc[15]++;
                    if (p->buffer[p->readHeader] == 'Q')
                        lC->lc[16]++;
                    if (p->buffer[p->readHeader] == 'R')
                        lC->lc[17]++;
                    if (p->buffer[p->readHeader] == 'S')
                        lC->lc[18]++;
                    if (p->buffer[p->readHeader] == 'T') {
                        lC->lc[19]++; }
                }
                p->readHeader++;
                //we've reached the end of out buffer reset to the start
                if(p->readHeader == (MAXBUFFER-1))
                {
                    p->readHeader = 0;
                }

                //we've received a sigint signal time to wrap things up
                //one last read out of the buffer
                if(finalRead == TRUE && p->readHeader != p->writeHeader)
                {
                    i = 0;
                }
                else if(finalRead == TRUE && p->readHeader == p->writeHeader)
                {
                    displayHis(lC);
                    done = TRUE;
                    break;
                }
                //we've caught up to the write header we need to stop reading
                if(p->readHeader == p->writeHeader)
                {
                    break;
                }
            }
            if ((tTime % 5 == 0) && (tTime != 0) && finalRead == FALSE)
            {
                displayHis(lC);     //display histogram every 10 seconds (5 counts of 2)
                tTime = 0;      //reset "timer"
            }
            timeToRead = FALSE;
        }
        if (semop (sem_id, &release_operation, 1) == -1) 
        {
            semctl (sem_id, 0, IPC_RMID);
            exit (6);
        }
    }
    //detach from shared memory
    shmdt (p);

    //printf("(DC) Removing the Shared-Memory resource\n");
	shmctl (shmid, IPC_RMID, 0);
	//printf ("(DC) Release the semaphores\n");
	semctl (sem_id, 0, IPC_RMID, 0);
    //end it with a Shazam!
    printf("Shazam!\n");
    return 0;
}
