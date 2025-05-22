#ifndef ACCOUNTS_H
#define ACCOUNTS_H
#define IBAN_MAX_LEN 34
// Plan is to use 2 hashMaps keeping one the same list of BankAccounts. First map with key = iban, second with key = userID

typedef struct BankAccount
{
    char iban[IBAN_MAX_LEN];
    double balance;
    int userId;

} BankAccount;

int withdraw(double amount);
int deposit(double amount);

BankAccount *createBankAccount(char *iban, double balance, int userId);
#endif