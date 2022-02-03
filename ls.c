#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>

/*
function used to traverse files in a given path
takes 2 parameters: a string fn which is the path and an integer indent which is used to space the output
returns an integer0 if function is completed succesfuly
main methods used in the function:
  opendir() - from <dirent.h> used to open a directory so that it's accesible for read operations
  readdir() - reads the contents of a directory to a dirent structure
  scandir() - reads folder contents storing the results in an array structure
*/

int traverse(const char *fn, int indent) {
  DIR *dir; //createa directory stream object named dir
  struct dirent *entry;
  int count;
  char path[1025];
  struct stat info;

  for (count=0; count<indent; count++) printf("  ");
  printf("%s\n", fn);
  //Open dir
  if ((dir = opendir(fn)) == NULL){
    printf("tuls: cannot open directory \n");
    return 1;
  }
  //read dir
  else {
    while ((entry = readdir(dir)) != NULL) {
      if (entry->d_name[0] != '.') {
        strcpy(path, fn);
        strcat(path, "/");
        strcat(path, entry->d_name);
        if (stat(path, &info) != 0)
          fprintf(stderr, "stat() error on %s: %s\n", path,
                  strerror(errno));
        else if (S_ISDIR(info.st_mode))
               traverse(path, indent+1);
      }
    }
    struct dirent **namelist;
      int n;
      n=scandir(fn,&namelist,NULL,alphasort);
      if (n == -1) {
        printf("This %s \n",fn);
        perror("scandir");
        return -1;
        exit(EXIT_FAILURE);
    }
    //Scan directory
      while (n--)
      {
          for (count=0; count<indent+1; count++) printf("  ");
          printf("%s\n",namelist[n]->d_name);
          free(namelist[n]);
      }
    closedir(dir);
  }
  return 0;
}


int main(int argc, char const *argv[])
{   
  int value = 0;
  if (argc == 1) //if no path is given use current directory as path
    {
      traverse(".", 0);
    }else
    {
      value = traverse(argv[1], 0);
    }
  return value;
}