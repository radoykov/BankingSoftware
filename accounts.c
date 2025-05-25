#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "accounts.h"

int generateIDNumber(){
    int newID = 0;
    int min = 0, max = 9;
    
    for(int i = 0; i < 12; i++){
        int random_number = 0;
        random_number = rand() % (max - min + 1) + min;
        if(i == 0 && random_number == 0){
        random_number = rand() % 9 + 1; //making sure that the ID doesnt begin with 0
        }
        newID = newID * 10 + random_number;
    }
    return newID;
}

void generateIban(char newIban[IBAN_MAX_LEN]){
    for(int i; i < IBAN_MAX_LEN - 1; i++){ 
        int type = rand() % 2; // digit or letter
        if(type == 0){
            newIban[i] = '0' + rand() % 10;
        }
        else{
            newIban = 'A' + rand() % 26;
        }
    }
    newIban[IBAN_MAX_LEN - 1] = '\0';
}

BankAccount *createBankAccount(){
 BankAccount *newAccount = (BankAccount*)malloc(sizeof(BankAccount));
 newAccount->balance = 0.0;
 newAccount->userId = generateIDNumber();
 generateIban(newAccount->iban);
 return newAccount;
}

int withdraw(BankAccount account,double amount){
 if(account.balance == 0 || (account.balance - amount) < 0){
    printf("Error: Withdrawal unsuccessful due to insufficient funds in account.");
 }
 else if(amount <= 0){
    printf("Error: Withdrawal unsuccessful due to withdrawal amount being invalid.");
 }
 else{
  account.balance = account.balance - amount;
 }
}

int deposit(BankAccount account,double amount){
 if(amount <= 0){
    printf("Error: Deposit unsuccessful due to deposit amount being invalid");
 }
 else{
    account.balance += amount;
 }


}