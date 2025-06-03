#ifndef ACCOUNTS_H
#define ACCOUNTS_H
#include "types.h"
#include "structures/hashTable/hashMap.h"
#define IBAN_MAX_LEN 35
#define ID_LEN 12

typedef struct BankAccount
{
    uint id;
    char iban[IBAN_MAX_LEN];
    double balance;
    uint userId;

} BankAccount;

typedef struct BankAccountsTable
{
    HashMap *byIban;
    HashMap *byUserID;
    uint count;

} BankAccountsTable;

int withdraw(BankAccount *account, double amount);
int deposit(BankAccount *account, double amount); 

BankAccount *initBankAccount();
BankAccount *createBankAccount(uint userId); 

BankAccountsTable *initBankAccounts();
void addBankAccount(BankAccountsTable *map, BankAccount *account);
BankAccount *findAccountByIban(BankAccountsTable *map, char *iban);
BankAccount *findAccountByUserID(BankAccountsTable *map, uint userID);
void releaseBankAccounts(BankAccountsTable * bat);

static void *selectAccountIbanKey(void *data);
static void *selectAccountUserIdKey(void *data);
static void generateIban(char newIban[IBAN_MAX_LEN]);

#endif