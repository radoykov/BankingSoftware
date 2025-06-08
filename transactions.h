#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H
#include "structures/queue/queue.h"
#include "accounts.h"
#define IBAN_MAX_LEN 35

typedef struct Transaction
{
    double amount;
    char accountFrom[IBAN_MAX_LEN];
    char accountTo[IBAN_MAX_LEN];

} Transaction;


Transaction *createTransaction(const char *fromIban, const char *toIban, double amount);
int transaction(BankAccount* account,Queue* queue,BankAccountsTable *map,const char *fromIban,const char *toIban,double ammount);
int executeAllTransactions(Queue *queue,BankAccountsTable *map);

#endif