#include "terminal.h"

void ctrlChandler()
{
    printf("\n\nCTRL-C pressed, exit...\n\n");
    
    exit(EXIT_SUCCESS);
}

int main (void)
{
    unsigned char buf[OSBUFFER];
    char mode[]= {'8','N','1', 0}, cport_in[10];
    int n, bdrate=BAUD;
    char *rvfgets;

    while (1)
    {
        printf("0/1/2/3/4 /dev/ttyUSBx ? > ");
        rvfgets = fgets(cport_in, 10, stdin);
        if (rvfgets == NULL)
        {
            printf("\nfgets error\n");
            continue;
        }

        if (cport_in[0] == '0')
        {
            cport_nr = 16;
            break;
        }
        else if (cport_in[0] == '1')
        {
            cport_nr = 17;
            break;
        }
        else if (cport_in[0] == '2')
        {
            cport_nr = 18;
            break;
        }
        else if (cport_in[0] == '3')
        {
            cport_nr = 19;
            break;
        }
        else if (cport_in[0] == '4')
        {
            cport_nr = 20;
            break;
        }
        else
        {
            printf("only 0 to 4 possible, please correct\n");
            continue;
        }
    }

    memset (&buf, 0, sizeof (buf));
   
    if (signal(SIGINT, ctrlChandler) == SIG_ERR)
    {
        perror("ERROR while setting signal handler CTRL-C");
        return -1;
    }

    if(RS232_OpenComport(cport_nr, bdrate, mode))
    {
        perror("can not open com port");
        return -1;
    }

    RS232_flushRXTX(cport_nr);

    while(1)
    {
      
        usleep(100000);

        memset (&buf, 0, sizeof (buf));

        n = RS232_PollComport(cport_nr, buf, (OSBUFFER-1));

        RS232_flushRX(cport_nr);

        if(n > 1)
        {
            printf("%s", (char *)buf);
        }
        else
        {
            continue;
        }
    }

    return 0;
}
