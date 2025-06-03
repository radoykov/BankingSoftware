#ifndef USERS_H
#define USERS_H
#include "types.h"
#include "structures/hashTable/hashMap.h"
#include "sha256.h"
#define USERNAME_MAX_LEN 10
#define USERNAME_SIZE 100
#define PASSWORD_MAX_LEN 50
#define PASSWORD_SIZE 100
#define PASSWORD_MIN_LEN 3
#define USERNAME_MIN_LEN 3

typedef struct Session
{
    uint userId;
    char username[USERNAME_MAX_LEN];

} Session;

typedef struct User
{
    uint id;
    char username[USERNAME_MAX_LEN];
    char hashedPassword[HASH_HEXADECIMAL_SIZE];

} User;

typedef struct UsersTable
{
    HashMap *byId;
    HashMap *byUsername;
    uint lastUsedId;

} UsersTable;

User *loginUser(UsersTable *users);
User *registerUser(UsersTable *users);
User *initUser();
UsersTable *initUsers();
User *createUser(char *username, char *password);
void addUser(UsersTable *users, User *user);
User *findUserByUsername(UsersTable *users, char *username);
User *findUserById(UsersTable *users, uint id);

static void hashPassword(const char *password, char *output_hexadecimal);
static int generateUniqueId(HashMap *map);
int validateUsername(char *username);
int validatePassword(char *password);

void releaseUsers(UsersTable *ut);

static void* selectUserIdKey(void* data);
static void* selectUsernameKey(void* data);

// Session menagement
Session *initSession(User *user);
void deleleSession(Session *session);

#endif