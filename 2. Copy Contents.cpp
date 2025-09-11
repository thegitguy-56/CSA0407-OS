#include <stdio.h>
#include <fcntl.h>      // for open()
#include <unistd.h>     // for read(), write(), close()
#include <stdlib.h>     // for exit()

#define BUFFER_SIZE 1024

int main() {
    int sourceFD, destFD;
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;

    // Open source file for reading
    sourceFD = open("source.txt", O_RDONLY);
    if (sourceFD < 0) {
        perror("Error opening source file");
        exit(1);
    }

    // Open (or create) destination file for writing
    destFD = open("destination.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (destFD < 0) {
        perror("Error opening/creating destination file");
        close(sourceFD);
        exit(1);
    }

    // Read from source and write to destination
    while ((bytesRead = read(sourceFD, buffer, BUFFER_SIZE)) > 0) {
        if (write(destFD, buffer, bytesRead) != bytesRead) {
            perror("Error writing to destination file");
            close(sourceFD);
            close(destFD);
            exit(1);
        }
    }

    if (bytesRead < 0) {
        perror("Error reading from source file");
    }

    printf("File copied successfully!\n");

    // Close files
    close(sourceFD);
    close(destFD);

    return 0;
}
