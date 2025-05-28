#ifndef USERS_H
#define USERS_H

#include "structures/hashTable/hashMap.h"
#include "sha256.h"
#define USERNAME_MAX_LEN 10
#define USERNAME_SIZE 100
#define PASSWORD_MAX_LEN 50
#define PASSWORD_SIZE 100

//user have to be searched by username and id we are using hash map !

typedef struct User
{
    int id;
    char username[USERNAME_MAX_LEN];
    char hashedPassword[HASH_HEXADECIMAL_SIZE]; // type will be changed there will be includet sha256 len

} User;

typedef struct UsersTable
{
    HashMap* byId;
    HashMap* byUsername;
} UsersTable;

//int loginUser(char *username, char *password);
void hashPassword(const char *password, char *output_hexadecimal);
UsersTable* initUsers();
User* createUser(char* username, char* password);
void registerUser(UsersTable *users, User* user);
User* findUserByUsername(UsersTable *users, char* username);
User* findUserById(UsersTable *users, int id);
int validateUsername(char *username);
int validatePassword(char *password);
void release(UsersTable *ut);

#endif