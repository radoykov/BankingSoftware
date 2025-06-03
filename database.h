#ifndef DATABASE_H
#define DATABASE_H
#include "users.h"
#include "accounts.h"
#include "transactions.h"
#define CHECK_FILE(p)                           \
    if (!p)                                     \
    {                                           \
        printf("Error file cannot be opened."); \
        exit(1);                                \
    }

// 1. Plan is to keep here all methods which write hashmaps and queues to files and vice versa.
// readAllUsersFromDb(filename, pointer to hashmap)

// 2. Also need methods for updating single structure into a file.
// updateBankAccountInDb(filename, BankAccount* account)

// Filenames can be constants here.

// files - users, accounts, transactions

void saveUserInFile(User *user);
void readAllUsersFromFile(UsersTable *users);

void saveAccountInFile(BankAccount *account);
// void updateAccountInFile(BankAccount *account, double amount);
void readAllAccountFromFile(BankAccountsTable *accounts);
void saveTransactionInFile(Transaction *transactions);
void readAllTransactionsFromFile();

#endif