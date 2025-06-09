#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "transactions.h"
#include "database.h"

Transaction *createTransaction(const char *fromIban, const char *toIban, double amount){
  Transaction *newTransaction = (Transaction*)malloc(sizeof(Transaction));
  CHECK(newTransaction);

  newTransaction->amount = amount;
  

  strncpy(newTransaction->accountFrom,fromIban,IBAN_MAX_LEN);
  newTransaction->accountFrom[IBAN_MAX_LEN - 1] ='\0';
  strncpy(newTransaction->accountTo,toIban,IBAN_MAX_LEN);
  newTransaction->accountTo[IBAN_MAX_LEN - 1] = '\0';

  return newTransaction;
}



int transaction(BankAccount *account,Queue *queue,BankAccountsTable *map,const char *fromIban,const char *toIban,double ammount){
 if(!fromIban || !toIban){
    printf("\nError: Invalid Iban.");
    return -1;
 }
 BankAccount *from = findAccountByIban(map,(char *)fromIban);
 BankAccount *to = findAccountByIban(map,(char *)toIban);
 //I don't check the from Iban because the user has already logged in so it must exist.
 if(!to){
   printf("\nError: Receiver account not found.");
   return -1;
 }
 Transaction *current_transaction = createTransaction(fromIban,toIban,ammount);
 if(!current_transaction){
    printf("\nError:Failed to create transaction");
    return -1;
 }  

 enqueue(queue,current_transaction);
 return 1;
}

int executeAllTransactions(Queue *queue,BankAccountsTable *map){
  if(!queue || !map){
    printf("Error: No queue or Accounts list.");
    return 0;
  }

  int executed = 0;
  while (!isEmpty(queue)){
    Transaction *t = dequeue(queue);
    if(!t){
      continue;
    }  
    BankAccount *from = findAccountByIban(map,t->accountFrom);
    BankAccount *to = findAccountByIban(map,t->accountTo);

    if(!from || !to){
      printf("Skipping transfer: Invalid accounts.");
      free(t);
      continue;
    }
    if(from->balance < t->amount){
      printf("Skipping transfer from %s to %s: Insufficient funds",t->accountFrom,t->accountTo);
      free(t);
      continue;
    }
    from->balance = from->balance - t->amount;
    to->balance = to->balance + t->amount;
    saveTransactionsInFile(t);
    printf("Transfer executed %.2lf sent from %s to %s",t->amount,t->accountFrom,t->accountTo);
    free(t);
    executed++;
  }
  printf("Number of successfully executed transfers: %d",executed);
  return executed;
  }