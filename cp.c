#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h> 
#include <sys/types.h>
#include <sys/stat.h>

/* 
the function takes 2 arguments and has no return value
first argument the source file to be copied and the second is destination file name or directory
it works by opening the source file and reading and storing its contents
then opening the destination file and writing the files
the main methods used in the library include:
    open() standard library for file IO takes on two main argument - file path and permissions - and returns file object
    close() """" frees memory allocated to a file object
    read() reads each character in a file
    write() writes characters to a file
 */
void copyPaste(const char *input,const char *destination){
    char buf;
	int fd_one, fd_two;
	fd_one = open(input, O_RDONLY); //source file object
	if (fd_one == -1)
	{
		printf("Error opening first_file\n");
		close(fd_one);
		return;
	}
	fd_two = open(destination, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); // destination file object
	while(read(fd_one, &buf, 1)) //read operation
	{
		write(fd_two, &buf, 1); // write operation
	}
	printf("Successful copied to %s\n",destination);
	close(fd_one);
	close(fd_two);
}

//main function
int main(int argc, char const *argv[])
{
    int nFiles = argc - 2; // number of files stated in the arguments
    int destinationIndex = argc-1;
    char path[1025];
    strcpy(path,(char *)argv[destinationIndex]); 
    for (int i = 0; i < nFiles; i++)
    {
        //printf("The number of files is %i\n",nFiles);
        struct stat st;
        //using the stat() to check if file is a directory
        stat( path, &st);
        if (S_ISDIR( st.st_mode )){ //if directory append file name to path
            strcat(path,"/");
            strcat(path,(char *)argv[i+1]);
            copyPaste(argv[i+1],path);
            //remove concatinated area
            char new[400]="";
            char *original = path;
            char *omit = (char *)argv[i+1];
            for (int i = 0; i < ((int)strlen(original)-(int)strlen(omit)-1); i++)
            {
                new[i]=original[i];
            }
            strcpy(path,new);
        }
        else{
            copyPaste(argv[i+1],argv[destinationIndex]);
        }   
    }    
    return 0;
}