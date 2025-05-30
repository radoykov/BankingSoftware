#ifndef DATABASE_H
#define DATABASE_H
#include "users.h"
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

#endif