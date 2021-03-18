#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

const int BUF_SIZE = 8192;

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("usage: cat [file ...]");
    }
    
    char *buf = (char *) calloc(BUF_SIZE, sizeof(char)); 
    for (int it = 1; it < argc; it++) {
        int fd = open(argv[it], O_RDONLY);
        if (fd != -1) {
            while (read(fd, buf, BUF_SIZE) > 0) {
                printf("%s", buf);
            }
            close(fd);
        } else {
            printf("cat: %s: No such file or directory", argv[it]);
        }
    }
    return 0;
}
