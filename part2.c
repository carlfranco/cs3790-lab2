#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

enum status { on, off};
typedef enum status status;

int pid;
status flag = off;

void turn_on ( int code) {
flag = on;
}
void turn_off ( int code) {
flag =off;
}

int  main(void)
  {
   struct sigaction newhandler, oldhandler;
   sigset_t sig;

   sigemptyset(&sig);  /* clear the signal mask */

   newhandler.sa_handler = turn_on;
   newhandler.sa_mask = sig;
   newhandler.sa_flags = 0;

   if ( sigaction(SIGUSR1,&newhandler,&oldhandler) == -1 )
     {
       printf("can't install signal handler \n");
       exit(-1);
     }

   newhandler.sa_handler = turn_off;

   if ( sigaction(SIGUSR2,&newhandler,&oldhandler) == -1 )
     {
       printf("can't install signal handler \n");
       exit(-1);
     }
    pid = fork();
    if ( 0 == pid  )
        {
          while (1) {
              if ( flag == off )
                fprintf(stderr," CHILD : I'm awake\n");
              else
                fprintf(stderr," CHILD : I'm sleeping\n");
              sleep(1);
        }
    }
     else { while (1) {
                  sleep(5);
                  kill(pid,SIGUSR1);
                  sleep(5);
                  kill(pid,SIGUSR2);
              }
           }
     return 0;
}
