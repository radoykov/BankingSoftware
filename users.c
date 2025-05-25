#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "users.h"

UsersTable *initUsers()
{
    UsersTable *users = (UsersTable *)malloc(sizeof(UsersTable));
    CHECK(users);
    users->byId = initHashMap();
    users->byUsername = initHashMap();
    return users;
}

int generateUniqueId(HashMap *map)
{
    int id;
    do
    {
        id = rand() % 1000000;
    } while (getByIntKey(map, id));
    return id;
}

User *createUser(char *username, char *password)
{
    User *newUser = (User *)malloc(sizeof(User));
    CHECK(newUser);
    newUser->id = 0;
    strcpy(newUser->username, username);
    newUser->hashedPassword = NULL; // TODO: Use hash function here.
    return newUser;
}

void registerUser(UsersTable *users, User *user)
{
    user->id = generateUniqueId(users->byId);
    setByIntKey(users->byId, user->id, user);
    setByStringKey(users->byUsername, user->username, user);
}

User *findUserByUsername(UsersTable *users, char *username)
{
    return (User *)getByStringKey(users->byUsername, username);
}

User *findUserById(UsersTable *users, int id)
{
    return (User *)getByIntKey(users->byId, id);
}

int validateUsername(char *username)
{
    if (strlen(username) > USERNAME_MAX_LEN)
    {
        printf("Error: Username must be less than %d symbols\n", USERNAME_MAX_LEN);
        return 0;
    }
    return 1;
}

int validatePassword(char *password)
{
    if (strlen(password) > PASSWORD_MAX_LEN)
    {
        printf("Error: Username must be less than %d symbols\n", PASSWORD_MAX_LEN);
        return 0;
    }
    return 1;
}