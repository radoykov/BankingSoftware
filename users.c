#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "users.h"

static void hashPassword(const char *password, char *output_hexadecimal)
{
    uint8_t hash[32];
    SHA256_CTX ctx;

    sha256_init(&ctx);
    sha256_update(&ctx, (const uint8_t *)password, strlen(password));
    sha256_final(&ctx, hash);

    for (int i = 0; i < 32; ++i)
    {
        sprintf(output_hexadecimal + (i * 2), "%02x", hash[i]);
    }
}

UsersTable *initUsers()
{
    UsersTable *users = (UsersTable *)malloc(sizeof(UsersTable));
    CHECK(users);
    users->byId = initHashMap();
    users->byUsername = initHashMap();
    return users;
}

static int generateUniqueId(HashMap *map)
{
    int id;
    // do
    // {
    id = rand() % 1000000;
    // } while (getByIntKey(map, id));
    return id;
}

User *initUser()
{
    User *newUser = (User *)malloc(sizeof(User));
    CHECK(newUser);

    return newUser;
}

User *createUser(char *username, char *password)
{
    User *newUser = initUser();
    newUser->id = 0;
    strcpy(newUser->username, username);
    hashPassword(password, newUser->hashedPassword);

    return newUser;
}

static void *selectUserIdKey(void *data)
{
    return &((User *)data)->id;
}

static void *selectUsernameKey(void *data)
{
    return ((User *)data)->username;
}

void addUser(UsersTable *users, User *user)
{
    user->id = generateUniqueId(users->byId);
    set(users->byId, user, selectUserIdKey, compareInts, hashInt);
    set(users->byUsername, user, selectUsernameKey, compareStrings, hashString);
}

User *findUserByUsername(UsersTable *users, char *username)
{
    return (User *)get(users->byUsername, username, selectUsernameKey, compareStrings, hashString);
}

User *findUserById(UsersTable *users, int id)
{
    return (User *)get(users->byId, &id, selectUserIdKey, compareInts, hashInt);
}

User *loginUser(UsersTable *users)
{
    char username[USERNAME_SIZE];
    char password[PASSWORD_SIZE];
    char hashedPass[HASH_HEXADECIMAL_SIZE];

    printf("\nEnter your username:");
    scanf("%s", username);
    if (validateUsername(username) == 0)
        return NULL;

    User *user = findUserByUsername(users, username);
    if (!user)
    {
        printf("Error: No such user exists.");
        return NULL;
    }

    printf("\nEnter your password: ");
    scanf("%s", password);
    if (validatePassword(password) == 0)
        return NULL;

    hashPassword(password, hashedPass);

    if (strcmp(user->hashedPassword, hashedPass) == 0)
    {
        printf("Login Successful.");
        return user;
    }
    else
    {
        printf("Error: Incorrect password.");
        return NULL;
    }
}

User *registerUser(UsersTable *users)
{
    char username[USERNAME_SIZE];
    char password[PASSWORD_SIZE];

    printf("\nEnter your new username: ");
    scanf("%s", username);
    if (validateUsername(username) == 0)
        return NULL;

    User *user = findUserByUsername(users, username);
    if (user)
    {
        printf("Error: Provided username already exists!\n");
        return NULL;
    }

    printf("Enter your password: ");
    scanf("%s", password);
    if (validatePassword(password) == 0)
        return NULL;

    User *newUser = createUser(username, password);
    addUser(users, newUser);
    printf("User successfuly registered!\n");
    return newUser;
}

int validateUsername(char *username)
{
    if (strlen(username) > USERNAME_MAX_LEN || strlen(username) < USERNAME_MIN_LEN)
    {
        printf("Error: Username length must be between %d and %d \n", USERNAME_MIN_LEN, USERNAME_MAX_LEN);
        return 0;
    }
    return 1;
}

int validatePassword(char *password)
{
    if (strlen(password) > PASSWORD_MAX_LEN || strlen(password) < PASSWORD_MIN_LEN)
    {
        printf("Error: Password length must be between %d and %d \n", PASSWORD_MIN_LEN, PASSWORD_MAX_LEN);
        return 0;
    }
    return 1;
}

void releaseUsers(UsersTable *ut)
{
    for (int i = 0; i < HASH_MAP_SIZE; i++)
    {
        Node *curr = ut->byUsername->array[i];
        while (curr)
        {
            Node *temp = curr;
            curr = curr->next;
            // user memory
            free(temp->data);
        }
    }
    freeHashMap(ut->byUsername);
    freeHashMap(ut->byId);
}

Session *initSession(User *user)
{
    Session *s = (Session *)malloc(sizeof(Session));
    CHECK(s);
    s->userId = user->id;
    strcpy(s->username, user->username);

    return s;
}

void deleleSession(Session *session)
{
    free(session);
}