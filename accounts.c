#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "accounts.h"

// int generateIDNumber()
// {
//     int newID = 0;
//     int min = 0, max = 9;

//     for (int i = 0; i < 12; i++)
//     {
//         int random_number = 0;
//         random_number = rand() % (max - min + 1) + min;
//         if (i == 0 && random_number == 0)
//         {
//             random_number = rand() % 9 + 1; // making sure that the ID doesnt begin with 0
//         }
//         newID = newID * 10 + random_number;
//     }
//     return newID;
// }

static void generateIban(char newIban[IBAN_MAX_LEN])
{
    for (int i = 0; i < IBAN_MAX_LEN - 1; i++)
    {
        int type = rand() % 2; // digit or letter
        if (type == 0)
        {
            newIban[i] = '0' + rand() % 10;
        }
        else
        {
            newIban[i] = 'A' + rand() % 26;
        }
    }
    newIban[IBAN_MAX_LEN - 1] = '\0';
}

BankAccount *createBankAccount(int userId)
{
    BankAccount *newAccount = (BankAccount *)malloc(sizeof(BankAccount));
    CHECK(newAccount);
    newAccount->balance = 0.0;
    newAccount->userId = userId;
    generateIban(newAccount->iban);
    return newAccount;
}

BankAccountsTable *initBankAccounts()
{
    BankAccountsTable *newMap = (BankAccountsTable *)malloc(sizeof(BankAccountsTable));
    CHECK(newMap);
    newMap->byIban = initHashMap();
    newMap->byUserID = initHashMap();
    return newMap;
}

void addBankAccount(BankAccountsTable *map, BankAccount *account)
{
    
    setByStringKey(map->byIban, account->iban, account);
    setByIntKey(map->byUserID, account->userId, account);
}

BankAccount *findAccountByIban(BankAccountsTable *map, char *iban)
{
    return (BankAccount *)getByStringKey(map->byIban, iban);
}

BankAccount *findAccountByUserID(BankAccountsTable *map, int userID)
{
    return (BankAccount *)getByIntKey(map->byUserID, userID);
}

int withdraw(BankAccount *account, double amount)
{
    if (account->balance == 0 || (account->balance - amount) < 0)
    {
        printf("Error: Withdrawal unsuccessful due to insufficient funds in account.");
        return 0;
    }
    else if (amount <= 0)
    {
        printf("Error: Withdrawal unsuccessful due to withdrawal amount being invalid.");
        return 0;
    }

    account->balance = account->balance - amount;

    return 1;
}

int deposit(BankAccount *account, double amount)
{
    if (amount <= 0)
    {
        printf("Error: Deposit unsuccessful due to deposit amount being invalid");
        return 0;
    }

    account->balance += amount;

    return 1;
}

void releaseBankAccounts(BankAccountsTable * bat)
{
    for (int i = 0; i < HASH_MAP_SIZE; i++)
    {
        Node *curr = bat->byIban->array[i];
        while (curr)
        {
            Node *temp = curr;
            curr = curr->next;
            // account memory
            free(temp->val);
        }
    }
    freeHashMap(bat->byUserID);
    freeHashMap(bat->byIban);
}