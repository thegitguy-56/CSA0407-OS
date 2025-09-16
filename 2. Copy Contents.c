#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    FILE *source, *destination;
    char buffer[BUFFER_SIZE];
    size_t bytesRead;

    source = fopen("source.txt", "rb");  // Open source file in binary read mode
    if (source == NULL) {
        perror("Error opening source file");
        exit(1);
    }

    destination = fopen("destination.txt", "wb");  // Open or create destination file in binary write mode
    if (destination == NULL) {
        perror("Error opening destination file");
        fclose(source);
        exit(1);
    }

    // Copy data
    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, source)) > 0) {
        fwrite(buffer, 1, bytesRead, destination);
    }

    printf("File copied successfully!\n");

    fclose(source);
    fclose(destination);

    return 0;
}
