#include <windows.h>
#include <stdio.h>

#define PIPE_NAME "\\\\.\\pipe\\MessageQueueExample"

int main() {
    HANDLE hPipe;
    char message[256];

    // Create a named pipe
    hPipe = CreateNamedPipe(
        PIPE_NAME,
        PIPE_ACCESS_OUTBOUND,
        PIPE_TYPE_MESSAGE | PIPE_WAIT,
        1, 256, 256, 0, NULL);

    if (hPipe == INVALID_HANDLE_VALUE) {
        printf("Error creating pipe (%lu)\n", GetLastError());
        return 1;
    }

    printf("Waiting for receiver to connect...\n");
    ConnectNamedPipe(hPipe, NULL); // Wait for receiver

    printf("Enter message to send: ");
    fgets(message, 256, stdin);

    WriteFile(hPipe, message, strlen(message) + 1, NULL, NULL);

    printf("Message sent!\n");

    CloseHandle(hPipe);
    return 0;
}
