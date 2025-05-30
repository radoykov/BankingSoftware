#ifndef ACCOUNTS_H
#define ACCOUNTS_H

#include "structures/hashTable/hashMap.h"
#define IBAN_MAX_LEN 35
#define ID_LEN 12

typedef struct BankAccount
{
    char iban[IBAN_MAX_LEN];
    double balance;
    int userId;

} BankAccount;

typedef struct BankAccountsTable
{
    HashMap *byIban;
    HashMap *byUserID;

} BankAccountsTable;

int withdraw(BankAccount account, double amount);
int deposit(BankAccount account, double amount); 

BankAccount *createBankAccount(int userId); 

BankAccountsTable *initBankAccounts();
void addBankAccount(BankAccountsTable *map, BankAccount *account);
BankAccount *findByIban(BankAccountsTable *map, char *iban);
BankAccount *findByUserID(BankAccountsTable *map, int userID);
void releaseBankAccounts(BankAccountsTable * bat);

static void generateIban(char newIban[IBAN_MAX_LEN]);

#endif