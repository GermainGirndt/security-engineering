#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
        if (argc != 2) {
               fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
               exit(EXIT_FAILURE);
        }

        off_t offsetCamera = 0x7e;
        off_t offsetTime = 0xf9;
        int cameraLength = 14;
        int timeLength = 28;

        int file = open(argv[1], O_RDONLY);
        if (file == -1) {
                perror("open");
                exit(EXIT_FAILURE);
        }
        char buffer[1000];
        if (lseek(file, offsetCamera, SEEK_SET) == -1) {
                perror("lseek");
                close(file);
                exit(EXIT_FAILURE);
        }
        if (read(file, buffer, cameraLength) == -1) {
                perror("read");
                close(file);
                exit(EXIT_FAILURE);
        }
        printf("%s\n", buffer);
        if (lseek(file, offsetTime, SEEK_SET) == -1) {
                perror("lseek");
                close(file);
                exit(EXIT_FAILURE);
        }
        if (read(file, buffer, timeLength) == -1) {
                perror("read");
                close(file);
                exit(EXIT_FAILURE);
        }
        printf("%s\n", buffer);
        close(file);
}
