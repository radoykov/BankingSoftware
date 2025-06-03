#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H
// plan to use queue to keep all transactions
#include "structures/queue/queue.h"
#define IBAN_MAX_LEN 35
typedef enum Operation
{
    WITHDRAW
} Operation;

typedef struct Transaction
{
    Operation operation;
    double amount;
    char accountFrom[IBAN_MAX_LEN];
    char accountTo[IBAN_MAX_LEN];

} Transaction;

int transfer(char *iban, double amount);
int executeAllTransactions();

#endif