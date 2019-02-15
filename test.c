#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int   main(void)
{
  pid_t pid;
  char *pedo[2];
  int i;
  int status;

  pedo[0] = "/usr/bin/false";
  pedo[1] = NULL;
  if ((pid = fork()) == 0)
  {

    if (execve(pedo[0], pedo, NULL) == -1)
      exit(-1);
    exit (0);
  }
  else
  {
    signal(SIGTSTP, SIG_IGN);
    //waitpid(pid, &status, WUNTRACED);
    int waitstatus;
    //wait(&waitstatus);
    waitpid(pid, &waitstatus, WUNTRACED);
    i = WEXITSTATUS(waitstatus);
    printf("%d\n", i);
    printf("%d\n", pid);
    if (i == 0)
    {
        printf("EXITO");
    }
    else {
     printf("FFAIL"); 
    }
  }
  return (0);
}
