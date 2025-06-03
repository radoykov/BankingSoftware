#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "accounts.h"

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

BankAccount *initBankAccount()
{
    BankAccount *newAccount = (BankAccount *)malloc(sizeof(BankAccount));
    CHECK(newAccount);

    return newAccount;
}

BankAccount *createBankAccount(uint userId)
{
    BankAccount *newAccount = initBankAccount();
    newAccount->balance = 0.0;
    newAccount->id = 0;
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
    newMap->lastUsedId = 0;

    return newMap;
}

static void *selectAccountIbanKey(void *data)
{
    return ((BankAccount *)data)->iban;
}

static void *selectAccountUserIdKey(void *data)
{
    return &((BankAccount *)data)->userId;
}

void addBankAccount(BankAccountsTable *accounts, BankAccount *account)
{
    set(accounts->byIban, account, selectAccountIbanKey, compareStrings, hashString);
    set(accounts->byUserID, account, selectAccountUserIdKey, compareUints, hashUint);
    account->id = accounts->lastUsedId + 1;
    accounts->lastUsedId++;
}

BankAccount *findAccountByIban(BankAccountsTable *accounts, char *iban)
{
    return (BankAccount *)get(accounts->byIban, iban, selectAccountIbanKey, compareStrings, hashString);
}

BankAccount *findAccountByUserID(BankAccountsTable *accounts, uint userID)
{
    return (BankAccount *)get(accounts->byUserID, &userID, selectAccountUserIdKey, compareUints, hashUint);
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

void releaseBankAccounts(BankAccountsTable *bat)
{
    for (int i = 0; i < HASH_MAP_SIZE; i++)
    {
        Node *curr = bat->byIban->array[i];
        while (curr)
        {
            Node *temp = curr;
            curr = curr->next;
            // account memory
            free(temp->data);
        }
    }
    freeHashMap(bat->byUserID);
    freeHashMap(bat->byIban);
}