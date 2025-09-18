#include <stdio.h>
#include <string.h>

struct Directory {
    char fname[20]; // file name
} dir[50];

int main() {
    int n = 0, ch;
    char name[20];
    
    while (1) {
        printf("\n---- Single Level Directory ----\n");
        printf("1. Create File\n");
        printf("2. Delete File\n");
        printf("3. Search File\n");
        printf("4. Display Files\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                printf("Enter file name to create: ");
                scanf("%s", name);

                // check for duplicate file
                int exists = 0;
                for (int i = 0; i < n; i++) {
                    if (strcmp(dir[i].fname, name) == 0) {
                        exists = 1;
                        break;
                    }
                }

                if (exists)
                    printf("File '%s' already exists!\n", name);
                else {
                    strcpy(dir[n].fname, name);
                    n++;
                    printf("File '%s' created successfully.\n", name);
                }
                break;

            case 2:
                printf("Enter file name to delete: ");
                scanf("%s", name);
                int found = 0;
                for (int i = 0; i < n; i++) {
                    if (strcmp(dir[i].fname, name) == 0) {
                        found = 1;
                        // shift files to delete this entry
                        for (int j = i; j < n - 1; j++) {
                            dir[j] = dir[j + 1];
                        }
                        n--;
                        printf("File '%s' deleted successfully.\n", name);
                        break;
                    }
                }
                if (!found)
                    printf("File '%s' not found!\n", name);
                break;

            case 3:
                printf("Enter file name to search: ");
                scanf("%s", name);
                found = 0;
                for (int i = 0; i < n; i++) {
                    if (strcmp(dir[i].fname, name) == 0) {
                        found = 1;
                        printf("File '%s' found at position %d.\n", name, i + 1);
                        break;
                    }
                }
                if (!found)
                    printf("File '%s' not found!\n", name);
                break;

            case 4:
                if (n == 0)
                    printf("Directory is empty!\n");
                else {
                    printf("Files in directory:\n");
                    for (int i = 0; i < n; i++) {
                        printf("%d. %s\n", i + 1, dir[i].fname);
                    }
                }
                break;

            case 5:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
