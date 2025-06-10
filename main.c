#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include "users.h"
#include "transactions.h"
#include "accounts.h"
#include "database.h"
#include "structures/queue/queue.h"

void showMenu(Session *session, BankAccountsTable *accounts, Queue *transaction_queue)
{
    printf("\n\nWelcome %s\n", session->username);

    while (1)
    {
        printf("\nChoose from this options:");
        printf("\n1.Withdraw");
        printf("\n2.Deposit");
        printf("\n3.Transaction");
        printf("\n4.Process all transacions");
        printf("\n5.Show current balance");
        printf("\n6.Logout");
        int choise = 0;
        printf("\nYour choise is: ");
        scanf("%d", &choise);

        // Find the account of currenlty logged user
        BankAccount *loggedUserAccount = findAccountByUserID(accounts, session->userId);
        if (!loggedUserAccount)
        {
            printf("\nYour account cannot be found.");
            break;
        }

        switch (choise) // add to show how much you have in the acccount !
        {
        case 1:
        {
            double amountToWithdraw = 0;
            printf("\nHow much do you want to withdraw: ");
            scanf("%lf", &amountToWithdraw);
            if (withdraw(loggedUserAccount, amountToWithdraw))
            {
                updateAccountInFile(loggedUserAccount);
                printf("\nSuccessfully withdrawn %.2f! Current balance: %.2f\n", amountToWithdraw, loggedUserAccount->balance);
            }

            break;
        }
        case 2:
        {
            double amountToDeposit = 0;

            printf("\nHow much do you want to deposit: ");
            scanf("%lf", &amountToDeposit);
            if (deposit(loggedUserAccount, amountToDeposit))
            {
                updateAccountInFile(loggedUserAccount);
                printf("\nSuccessfully deposited %.2f! Current balance: %.2f\n", amountToDeposit, loggedUserAccount->balance);
            }

            break;
        }
        case 3:
        {
            double amountToTransfer = 0;
            char toIban[IBAN_MAX_LEN];

            printf("\nHow much do you wish to transfer: ");
            if (scanf("%lf", &amountToTransfer) != 1 || amountToTransfer <= 0)
            {
                printf("Invalid amount.\n");
                while (getchar() != '\n')
                    ;
                break;
            }

            printf("Enter the IBAN of the receiver: ");
            scanf("%s", toIban);
            Transaction * trans = transaction(loggedUserAccount, transaction_queue, accounts, loggedUserAccount->iban, toIban, amountToTransfer);
            if (trans)
            {
                printf("\nTransfer added to your list. Enter 'Process all transacions' to proceed.\n");
                saveTransactionInFile(trans);
            }
            break;
        }
        case 4:
            executeAllTransactions(transaction_queue, accounts);
            break;
        case 5:
            printf("Current balance: %.2f\n", loggedUserAccount->balance);
            break;
        case 6:
            printf("You succeesfully logged out.");
            deleleSession(session);
            return;

        default:
            printf("\nYou have selected wrong choice please try again.");
            break;
        }
    }
}

int main()
{
    srand(time(NULL));
    Session *session = NULL;
    
    UsersTable *users = initUsers();
    readAllUsersFromFile(users);
    
    BankAccountsTable *accounts = initBankAccounts();
    readAllAccountFromFile(accounts);
    
    Queue *transaction_queue = initQueue();
    readAllTransactionsFromFile(transaction_queue);

    while (1)
    {
        printf("\nChoose from this options:");
        printf("\n1.Login");
        printf("\n2.Registration");
        printf("\n3.Exit");
        int choise = 0;
        printf("\nYour choise is: ");
        scanf("%d", &choise);

        if (choise == 1)
        {
            User *loggedUser = loginUser(users);
            if (loggedUser)
            {
                session = initSession(loggedUser);
                showMenu(session, accounts, transaction_queue);
            }
        }
        else if (choise == 2)
        {
            printf("\n2.Registration");
            User *regUser = registerUser(users);
            if (regUser)
            {
                saveUserInFile(regUser);
                BankAccount *newAccount = createBankAccount(regUser->id);

                addBankAccount(accounts, newAccount);
                saveAccountInFile(newAccount);
                // Here we may want to login the user directly.
            }
        }
        else if (choise == 3)
        {
            releaseUsers(users);
            releaseBankAccounts(accounts);
            releaseQueue(transaction_queue);
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