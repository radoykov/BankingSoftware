#include <stdio.h>
#include <stdlib.h>
#include "database.h"

void saveUserInFile(User *user)
{
    FILE *file = fopen("data/users.bin", "ab");
    CHECK_FILE(file);

    size_t usersSaved = fwrite(user, sizeof(User), 1, file);
    if (usersSaved != 1)
    {
        printf("Error: Cannot save user in file!");
    }

    fclose(file);
}

void readAllUsersFromFile(UsersTable *users)
{
    FILE *file = fopen("data/users.bin", "rb");
    if (!file)
        return; // if it isn't created just do nothing

    while (1)
    {
        User *user = initUser();
        if (fread(user, sizeof(User), 1, file) != 1)
        {
            free(user);
            break;
        }
        addUser(users, user);
    }

    if (!feof(file))
    {
        printf("Error reading from file");
        exit(1);
    }

    fclose(file);
}