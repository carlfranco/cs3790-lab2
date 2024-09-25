#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void gone(int code )
{
  printf("\n interrupted code = %d\n",code );
  exit(-1);
}

int main() {

   struct sigaction newhandler, oldhandler;
   sigset_t sig;

   sigemptyset(&sig);  /* clear the signal mask */

   newhandler.sa_handler = gone;
   newhandler.sa_mask = sig;
   newhandler.sa_flags = 0;

   if ( sigaction(SIGQUIT,&newhandler,&oldhandler) == -1 )
     {
       printf("can't install signal handler \n");
       exit(-1);
     }

   while ( 1 ) {
         fprintf(stderr,"I'm awake!\n");
         sleep(1);
    }
   return 0;
  }
