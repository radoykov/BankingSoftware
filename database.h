#ifndef DATABASE_H
#define DATABASE_H
#include "users.h"
#include "types.h"
#include "accounts.h"
#include "transactions.h"
#define CHECK_FILE(p)                           \
    if (!p)                                     \
    {                                           \
        printf("Error file cannot be opened."); \
        exit(1);                                \
    }

void saveUserInFile(User *user);
void readAllUsersFromFile(UsersTable *users);

void saveAccountInFile(BankAccount *account);
void updateAccountInFile(BankAccount *account);
void readAllAccountFromFile(BankAccountsTable *accounts);
void saveTransactionInFile(Transaction *transactions);
void readAllTransactionsFromFile();

//Plase for transactions

#endif