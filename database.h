#ifndef DATABASE_H
#define DATABASE_H
#include "users.h"
#include "types.h"
#include "accounts.h"
#include "transactions.h"
#define CHECK_FILE(p)                           \
    if (!p)                                     \
    {                                           \
        printf("\nError file cannot be opened!\n"); \
        exit(1);                                \
    }
//users
void saveUserInFile(User *user);
void readAllUsersFromFile(UsersTable *users);

//accounts
void saveAccountInFile(BankAccount *account);
void updateAccountInFile(BankAccount *account);
void readAllAccountFromFile(BankAccountsTable *accounts);

//transactions
void saveTransactionInFile(Transaction *transactions);
void readAllTransactionsFromFile(Queue *queue);
void emptyTransactionFile();

#endif