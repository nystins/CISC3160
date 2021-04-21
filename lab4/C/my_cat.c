#include <stdio.h>
#include <stdlib.h>

int main (int argc, char * argv[]) 
{
    //Command Line Argument
    if (argc == 1){
        printf ("No file name was provided\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        FILE * my_file;
        char * char_arr = malloc (400 * sizeof(char));
        //looping through the text files
        for (int i = 1; i < argc; i++)
        {
            my_file = fopen(argv[i], "r");
            if(my_file == NULL){
                printf("Could not find text file(s)");
                exit(EXIT_FAILURE);
            }
            else{
                int counter = 1; //counter, for text file number 
                printf("Text_File %d\n", i);
                counter++;
                while(fgets(char_arr, 400, my_file) != NULL) 
                {
                    printf("%s",char_arr);

                }
            }

            fclose(my_file); //close file 
        }

                free(char_arr);
    }
    return EXIT_SUCCESS;
}
