#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "transactions.h"
#include "users.h"
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
















int main()
{
    while (1)
    {
        printf("\nChoose from this options:");
        printf("\n1.Login");
        printf("\n2.Registration");
        printf("\n3.Exit");
        int choise = 0;
        printf("\nYour choise is: ");
        scanf("%d", choise);

        if (choise == 1)
        {
        }
        else if (choise == 2)
        {
        }
        else if (choise == 3)
        {
            // write here if needed
            printf("\nThe program have finished.");
            return 0;
        }
        else
        {
            printf("\nYou have selected wrong choise please try again.");
        }
    }

    return 0;
}