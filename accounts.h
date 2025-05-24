#ifndef ACCOUNTS_H
#define ACCOUNTS_H
#define IBAN_MAX_LEN 35
#define ID_LEN 12
// Plan is to use 2 hashMaps keeping one the same list of BankAccounts. First map with key = iban, second with key = userID

typedef struct BankAccount
{
    char iban[IBAN_MAX_LEN];
    double balance;
    int userId;

} BankAccount;

int withdraw(BankAccount account,double amount);
int deposit(BankAccount account,double amount);  //Change here

BankAccount *createBankAccount(); //Change Here
#endif