#include <stdio.h>
#define NAME_MAX_LEN 50
#define IBAN_MAX_LEN 34

typedef enum Operation
{
    WITHDRAW
} Operation;

typedef struct User
{
    int id;
    char username[NAME_MAX_LEN];
    char *hashedPassword; // type will be changed there will be includet sha256 len

} User;

int loginUser(char* username, char*password);
int registerUser(char* username, char*password);

typedef struct Account
{
    char iban[IBAN_MAX_LEN];
    double balance;
    int userId;

} Account;

int withdraw(double amount);
int deposit(double amount);


typedef struct Transaction
{
    Operation operation; 
    double amount;
    char *accountFrom;
    char *accountTo;

} Transaction;

int transfer(char* iban, double amount);
int executeAllTransactions();

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