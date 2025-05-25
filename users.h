#include "structures/hashTable/hashMap.h"

#ifndef USERS_H
#define USERS_H
#define USERNAME_MAX_LEN 10
#define PASSWORD_MAX_LEN 50

//user have to be searched by username and id we are using hash map !

typedef struct User
{
    int id;
    char username[USERNAME_MAX_LEN];
    char *hashedPassword; // type will be changed there will be includet sha256 len

} User;

typedef struct UsersTable
{
    HashMap* byId;
    HashMap* byUsername;
} UsersTable;

//int loginUser(char *username, char *password);
UsersTable* initUsers();
User* createUser(char* username, char* password);
void registerUser(UsersTable *users, User* user);
User* findUserByUsername(UsersTable *users, char* username);
User* findUserById(UsersTable *users, int id);
int validateUsername(char *username);
int validatePassword(char *password);

#endif