#include <stdio.h>
#include <stdlib.h>
#include "database.h"

// for users

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

// for accounts

static int accountCount = 0;

void saveAccountInFile(BankAccount *account)
{
    FILE *file = fopen("data/accounts.bin", "ab");
    CHECK_FILE(file);

    size_t accountsSaved = fwrite(account, sizeof(BankAccount), 1, file);
    if (accountsSaved != 1)
    {
        printf("Error: Cannot save account in file!");
    }

    fclose(file);
}

// void updateAccountInFile(BankAccount *account, double amount)
// {
//     FILE *file = fopen("data/accounts.bin", "ab+");
//     CHECK_FILEf(file);
    
//     while (1)
//     {
//         BankAccount *account = initBankAccount();
//         if (fread(account, sizeof(BankAccount), 1, file) != 1)
//         {
//             free(account);
//             break;
//         }
//         accountCount++;
//         // addBankAccount(accounts, account);
//     }

//     if (!feof(file))
//     {
//         printf("Error reading from file");
//         exit(1);
//     }

//     fclose(file);
// }

void readAllAccountFromFile(BankAccountsTable *accounts)
{
    FILE *file = fopen("data/accounts.bin", "rb");
    if (!file)
        return; // if it isn't created just do nothing

    while (1)
    {
        BankAccount *account = initBankAccount();
        if (fread(account, sizeof(BankAccount), 1, file) != 1)
        {
            free(account);
            break;
        }
        addBankAccount(accounts, account);
    }

    if (!feof(file))
    {
        printf("Error reading from file");
        exit(1);
    }

    fclose(file);
}

void saveTransactionsInFile(){
    
}
