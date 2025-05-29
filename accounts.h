#ifndef ACCOUNTS_H
#define ACCOUNTS_H

#include "structures/hashTable/hashMap.h"
#define IBAN_MAX_LEN 35
#define ID_LEN 12
// Plan is to use 2 hashMaps keeping one the same list of BankAccounts. First map with key = iban, second with key = userID

typedef struct BankAccount
{
    char iban[IBAN_MAX_LEN];
    double balance;
    int userId;

} BankAccount;

typedef struct BankAccountsMap{

    HashMap *byIban;
    HashMap *byUserID;

}BankAccountsMap;

int withdraw(BankAccount account,double amount);
int deposit(BankAccount account,double amount);  //Change here

BankAccount *createBankAccount(int userId); //Change Here

BankAccountsMap *initBankAccountsTable();
void addBankAccount(BankAccountsMap *map,BankAccount *account);
BankAccount *findByIban(BankAccountsMap *map, const char *iban);
BankAccount *findByUserID(BankAccountsMap *map,int userID);

#endif