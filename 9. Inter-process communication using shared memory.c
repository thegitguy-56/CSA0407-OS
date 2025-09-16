#include <windows.h>
#include <stdio.h>
#include <string.h>

#define SHARED_MEM_SIZE 256

int main() {
    HANDLE hMapFile;
    LPVOID pBuf;

    // 1. Create a named shared memory object
    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,    // Use system paging file
        NULL,                    // Default security
        PAGE_READWRITE,          // Read/write access
        0,                       // Max size high-order DWORD
        SHARED_MEM_SIZE,         // Max size low-order DWORD
        "SharedMemoryExample");  // Name of shared memory

    if (hMapFile == NULL) {
        printf("Could not create file mapping object (%lu).\n", GetLastError());
        return 1;
    }

    // 2. Map memory to this process
    pBuf = MapViewOfFile(
        hMapFile,                // Handle to map object
        FILE_MAP_ALL_ACCESS,     // Read/write access
        0, 0, SHARED_MEM_SIZE);

    if (pBuf == NULL) {
        printf("Could not map view of file (%lu).\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    // 3. Write data to shared memory
    printf("Enter message to write into shared memory: ");
    char input[SHARED_MEM_SIZE];
    fgets(input, SHARED_MEM_SIZE, stdin);

    CopyMemory(pBuf, input, strlen(input) + 1);
    printf("Data written successfully!\n");

    printf("\nRun reader.exe in another terminal to read this data.\n");
    printf("Press Enter after reader has read the data...");
    getchar();

    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);

    return 0;
}
