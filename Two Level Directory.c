#include <stdio.h>
#include <string.h>

struct File {
    char fname[20];
};

struct UserDirectory {
    char uname[20];
    struct File files[20];
    int fileCount;
};

int main() {
    struct UserDirectory users[10];
    int userCount = 0;
    int choice;

    while (1) {
        printf("\n---- Two Level Directory ----\n");
        printf("1. Create User Directory\n");
        printf("2. Create File\n");
        printf("3. Delete File\n");
        printf("4. Search File\n");
        printf("5. Display User Directory\n");
        printf("6. Display All Users and Files\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 7) {
            printf("Exiting...\n");
            break;
        }

        char uname[20], fname[20];
        int foundUser = -1;

        switch (choice) {
            case 1:
                printf("Enter user name: ");
                scanf("%s", uname);

                // Check if user already exists
                for (int i = 0; i < userCount; i++) {
                    if (strcmp(users[i].uname, uname) == 0) {
                        foundUser = i;
                        break;
                    }
                }

                if (foundUser != -1)
                    printf("User '%s' already exists!\n", uname);
                else {
                    strcpy(users[userCount].uname, uname);
                    users[userCount].fileCount = 0;
                    userCount++;
                    printf("User directory '%s' created successfully.\n", uname);
                }
                break;

            case 2:
                printf("Enter user name: ");
                scanf("%s", uname);

                for (int i = 0; i < userCount; i++) {
                    if (strcmp(users[i].uname, uname) == 0) {
                        foundUser = i;
                        break;
                    }
                }

                if (foundUser == -1)
                    printf("User '%s' not found! Create user directory first.\n", uname);
                else {
                    printf("Enter file name to create: ");
                    scanf("%s", fname);

                    // Check if file already exists
                    int exists = 0;
                    for (int j = 0; j < users[foundUser].fileCount; j++) {
                        if (strcmp(users[foundUser].files[j].fname, fname) == 0) {
                            exists = 1;
                            break;
                        }
                    }

                    if (exists)
                        printf("File '%s' already exists for user '%s'!\n", fname, uname);
                    else {
                        strcpy(users[foundUser].files[users[foundUser].fileCount].fname, fname);
                        users[foundUser].fileCount++;
                        printf("File '%s' created successfully for user '%s'.\n", fname, uname);
                    }
                }
                break;

            case 3:
                printf("Enter user name: ");
                scanf("%s", uname);
                for (int i = 0; i < userCount; i++) {
                    if (strcmp(users[i].uname, uname) == 0) {
                        foundUser = i;
                        break;
                    }
                }

                if (foundUser == -1)
                    printf("User '%s' not found!\n", uname);
                else {
                    printf("Enter file name to delete: ");
                    scanf("%s", fname);

                    int foundFile = -1;
                    for (int j = 0; j < users[foundUser].fileCount; j++) {
                        if (strcmp(users[foundUser].files[j].fname, fname) == 0) {
                            foundFile = j;
                            break;
                        }
                    }

                    if (foundFile == -1)
                        printf("File '%s' not found for user '%s'.\n", fname, uname);
                    else {
                        for (int j = foundFile; j < users[foundUser].fileCount - 1; j++) {
                            users[foundUser].files[j] = users[foundUser].files[j + 1];
                        }
                        users[foundUser].fileCount--;
                        printf("File '%s' deleted successfully for user '%s'.\n", fname, uname);
                    }
                }
                break;

            case 4:
                printf("Enter user name: ");
                scanf("%s", uname);
                for (int i = 0; i < userCount; i++) {
                    if (strcmp(users[i].uname, uname) == 0) {
                        foundUser = i;
                        break;
                    }
                }

                if (foundUser == -1)
                    printf("User '%s' not found!\n", uname);
                else {
                    printf("Enter file name to search: ");
                    scanf("%s", fname);

                    int foundFile = 0;
                    for (int j = 0; j < users[foundUser].fileCount; j++) {
                        if (strcmp(users[foundUser].files[j].fname, fname) == 0) {
                            foundFile = 1;
                            break;
                        }
                    }

                    if (foundFile)
                        printf("File '%s' found in user '%s' directory.\n", fname, uname);
                    else
                        printf("File '%s' not found in user '%s' directory.\n", fname, uname);
                }
                break;

            case 5:
                printf("Enter user name: ");
                scanf("%s", uname);
                for (int i = 0; i < userCount; i++) {
                    if (strcmp(users[i].uname, uname) == 0) {
                        foundUser = i;
                        break;
                    }
                }

                if (foundUser == -1)
                    printf("User '%s' not found!\n", uname);
                else {
                    printf("Files for user '%s':\n", uname);
                    if (users[foundUser].fileCount == 0)
                        printf("No files.\n");
                    else {
                        for (int j = 0; j < users[foundUser].fileCount; j++) {
                            printf("%d. %s\n", j + 1, users[foundUser].files[j].fname);
                        }
                    }
                }
                break;

            case 6:
                if (userCount == 0)
                    printf("No users created yet.\n");
                else {
                    printf("\nAll Users and Their Files:\n");
                    for (int i = 0; i < userCount; i++) {
                        printf("User: %s\n", users[i].uname);
                        if (users[i].fileCount == 0)
                            printf("  No files.\n");
                        else {
                            for (int j = 0; j < users[i].fileCount; j++) {
                                printf("  %d. %s\n", j + 1, users[i].files[j].fname);
                            }
                        }
                    }
                }
                break;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
