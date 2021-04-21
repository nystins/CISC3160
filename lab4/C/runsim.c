#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int maxAllowedNumber = 1000; //maximum number of children allowed
int bufSize = 1000; //maximum size of a char array

char** parseInput(char *str);

int main(int argc, char *argv[])
{
   pid_t  pid, wid;
   int status;
   int nRunnableNumber; //max number of processes to run at a time
   int nRunningNumber = 0; //the number of currently running
   char *buffer = malloc(bufSize);
   char **temp = NULL;
   FILE *fp;
   int  fileLines = 0;
   char fileText[100][bufSize];

   if (buffer == NULL) {
     //falied in memeory allocation
      printf("can not allocate the memory!\n");
      exit(EXIT_FAILURE);
   }
   if (argc == 1){
     //if there is no the argument, exit the program
      printf("no argument!\n");
      exit(EXIT_FAILURE);
   }

   //get pr_limit from second argument
   int pr_limit = atoi(argv[1]);

   if (pr_limit >= 1 && pr_limit < maxAllowedNumber) {
     //pr_limit is valid
     nRunnableNumber = pr_limit;
   } else {
     //wrong value of pr_limit
     printf("limit number is wrong!\n");
     exit(EXIT_FAILURE);
   }

    if (argv[2] != NULL && strcmp(argv[2], "<") == 0) {
      if (argv[3] == NULL) {
        printf("no input text file!\n");
        exit(EXIT_FAILURE);
      }else {
        //open the text.txt file
        fp = fopen(argv[3], "r");
        while (fgets(buffer,150, fp)) {
          //read the lines from file
          strcpy(fileText[fileLines], buffer);
          fileLines ++; //increase the number of fileLines
        }
        //close the file
        fclose(fp);
      }
    }

    int i = fileLines;
    while(1) {
      if (i > 0) {
        strcpy(buffer, fileText[i]);
        i --;
      }
      else {
        if (fileLines > 0)
          break;
        fgets(buffer, bufSize - 1, stdin);
      }
      buffer[strcspn(buffer, "\r\n")] = 0; //remove the break line
      if (feof(stdin))
        break;
      
      if (nRunnableNumber == nRunningNumber) {
        wid=waitpid(-1,&status,0);
        if (WIFEXITED(status)) {
            printf("Process with pid %d: Normal termination with exit status=%d\n", wid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Process with pid %d: killed by signal %d\n", wid, WTERMSIG(status));
        } else if (WIFSTOPPED(status)) {
            printf("Process with pid %d: stopped by signal %d\n", wid, WSTOPSIG(status));
        } else if (WIFCONTINUED(status)) {
            printf("Process with pid %d: continued\n", wid);
        }

        nRunningNumber --;
      }
      //create a new process
      pid = fork();
      if (pid == -1) {
        //failed to create the process
        perror("fork");
        exit(EXIT_FAILURE);
      }

      //increase the number of current runnung process
      nRunningNumber ++;

      if (pid == 0) { /* Code executed by child */
        printf("Process with pid %ld succesfully forked\n", (long) getpid());
        // printf("buffer: %s, %d, %d\n", buffer, (int)strlen(buffer), buffer[strlen(buffer) - 1]);
        if (temp != NULL) {
          free(temp);
          temp = NULL;
        }
        temp = parseInput(buffer);
        execv(temp[0], temp);
        exit(0);
      }     
   };

  while ((wid=waitpid(-1,&status,0)) > 0) {
    if (WIFEXITED(status)) {
        printf("Process with pid %d: Normal termination with exit status=%d\n", wid, WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("Process with pid %d: killed by signal %d\n", wid, WTERMSIG(status));
    } else if (WIFSTOPPED(status)) {
        printf("Process with pid %d: stopped by signal %d\n", wid, WSTOPSIG(status));
    } else if (WIFCONTINUED(status)) {
        printf("Process with pid %d: continued\n", wid);
    }
        nRunningNumber --;
  }  
  exit(EXIT_SUCCESS);
   //return 0;
}


char** parseInput(char *str)
{
    //char    str[]= "ls -l";
    char ** res  = NULL;
    char *  p    = strtok (str, " ");
    int n_spaces = 0;
    
    
    /* split string and append tokens to 'res' */
    
    while (p) {
      res = realloc (res, sizeof (char*) * ++n_spaces);
    
      if (res == NULL)
        exit (-1); /* memory allocation failed */
    
      res[n_spaces-1] = p;
    
      p = strtok (NULL, " ");
    }
    
    /* realloc one extra element for the last NULL */
    res = realloc (res, sizeof (char*) * (n_spaces+1));
    res[n_spaces] = NULL;
    
    return res;
}
