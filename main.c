#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <time.h>
#include "users.h"
// #include "transactions.h"
#include "accounts.h"

void registration(UsersTable *users)
{
    char username[USERNAME_SIZE];
    char password[PASSWORD_SIZE];

    printf("\nEnter your new username: ");
    scanf("%s", username);
    if (validateUsername(username) == 0)
        return;

    User *user = findUserByUsername(users, username);
    if (user)
    {
        printf("Error: Provided username already exists!\n");
        return;
    }

    printf("Enter your password: ");
    scanf("%s", password);
    if (validatePassword(password) == 0)
        return;

    User *newUser = createUser(username, password);
    registerUser(users, newUser);
    printf("User successfuly registered!\n");
    // Here we may want to login the user directly.
}

int login(UsersTable *users)
{
    char username[USERNAME_SIZE];
    char password[PASSWORD_SIZE];
    char hashedPass[HASH_HEXADECIMAL_SIZE];

    printf("\nEnter your username:");
    scanf("%s", username);
    if (validateUsername(username) == 0)
        return 0;

    User *user = findUserByUsername(users, username);
    if (!user)
    {
        printf("Error: No such user exists.");
        return 0;
    }

    printf("\nEnter your password: ");
    scanf("%s", password);
    if (validatePassword(password) == 0)
        return 0;

    hashPassword(password, hashedPass);

    if (strcmp(user->hashedPassword, hashedPass) == 0)
    {
        printf("Login Successful.");
        return user->id;
    }
    else
    {
        printf("Error: Incorrect password.");
        return 0;
    }
}

int main()
{
    int session = -1;
    UsersTable *users = initUsers();

    while (1)
    {
        printf("\nChoose from this options:");
        printf("\n1.Login");
        printf("\n2.Registration");
        printf("\n3.Exit");
        int choise = 0;
        printf("\nYour choise is: ");
        scanf("%d", &choise);

        if (choise == 1)
        {
            int userId = login(users);
            if (userId)
            {
                session = userId;
            }
        }
        else if (choise == 2)
        {
            printf("\n2.Registration");
            registration(users);
        }
        else if (choise == 3)
        {
            // write here if needed
            printf("\nThe program have finished.");
            return 0;
        }
        else
        {
            printf("\nYou have selected wrong choise please try again.");
        }

    }
    return 0;
}