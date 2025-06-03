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
        if (user->id > users->lastUsedId)
        {
            users->lastUsedId = user->id;
        }
    }

    if (!feof(file))
    {
        printf("Error reading from file");
        exit(1);
    }

    fclose(file);
}

// for accounts

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

void updateAccountInFile(BankAccount *account)
{
    FILE *file = fopen("data/accounts.bin", "rb+");
    CHECK_FILE(file);

    // implementing binary search for searching the Account in file.O(logn)
    fseek(file, 0, SEEK_END); 
    uint size = ftell(file) / sizeof(BankAccount);
    uint left = 0;
    uint right = size - 1;
    BankAccount *currAccount = initBankAccount();

    while (left <= right)
    {

        uint middle = left + (right - left) / 2;

        fseek(file, middle * sizeof(BankAccount), SEEK_SET);
        fread(currAccount, sizeof(BankAccount), 1, file);

        if (account->id == currAccount->id)
        {
            fseek(file, -(long)sizeof(BankAccount), SEEK_CUR);
            fwrite(account, sizeof(BankAccount), 1, file);
            fclose(file);

            return;
        }
        if (account->id < currAccount->id)
        {
            right = middle - 1;
        }
        else
        {
            left = middle + 1;
        }
    }
    printf("\nAccount cannot be found in the file.");
    fclose(file);
}

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
        if (account->id > accounts->lastUsedId)
        {
            accounts->lastUsedId = account->id;
        }
    }

    if (!feof(file))
    {
        printf("Error reading from file");
        exit(1);
    }

    fclose(file);
}