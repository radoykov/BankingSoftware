#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H
//plan to use queue to keep all transactions

typedef enum Operation
{
    WITHDRAW
} Operation;

typedef struct Transaction
{
    Operation operation;
    double amount;
    char *accountFrom;
    char *accountTo;

} Transaction;

int transfer(char *iban, double amount);
int executeAllTransactions();

#endif