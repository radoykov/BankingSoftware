#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <time.h>
#include "users.h"
// #include "transactions.h"
#include "accounts.h"
#include "database.h"

void showMenu(Session *session, BankAccountsTable *accounts)
{
    printf("\nWelcome %s", session->username);

    printf("\nChoose from this options:");
    printf("\n1.Withdraw");
    printf("\n2.Deposit");
    printf("\n3.Transaction");
    printf("\n4.Prosess all transacions");
    printf("\n5.Logout");
    while (1)
    {
        int choise = 0;
        printf("\nYour choise is: ");
        scanf("%d", &choise);
        //printf("\nsesid %d", session->userId);
        // Find the account of currenlty logged user
        BankAccount *loggedUserAccount = findAccountByUserID(accounts, session->userId);
        if (!loggedUserAccount)
        {
            printf("\nYour account cannot be found.");
            break;
        }

        switch (choise)
        {
        case 1:
            double amountToWithdraw = 0;
            printf("\nHow much do you want to withdraw: ");
            scanf("%lf", &amountToWithdraw);
            if (withdraw(loggedUserAccount, amountToWithdraw))
                printf("\nSuccessfully withdrawn %lf!", amountToWithdraw);
            break;
        case 2:
            double amountToDeposit = 0;
            printf("\nHow much do you want to deposit: ");
            scanf("%lf", &amountToDeposit);
            if (deposit(loggedUserAccount, amountToDeposit))
                printf("\nSuccessfully deposited %lf!", amountToDeposit);
            break;
        case 3:
            /* code */
            // Have access to loggedUserAccount here as well the userId (from the session)
            break;
        case 4:
            /* code */
            // Have access to loggedUserAccount here as well the userId (from the session)
            break;
        case 5:
            printf("You succeesfully logged out.");
            deleleSession(session);
            return;

        default:
            printf("\nYou have selected wrong choise please try again.");
            break;
        }
    }
}

int main()
{
    Session *session = NULL;
    UsersTable *users = initUsers();
    readAllUsersFromFile(users);
    BankAccountsTable *accounts = initBankAccounts();
    readAllAccountFromFile(accounts);

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
                showMenu(session, accounts);
            }
        }
        else if (choise == 2)
        {
            printf("\n2.Registration");
            User *regUser = registerUser(users);
            if (regUser)
            {
                //printf("\nUserIdReg:%d", regUser->id);
                saveUserInFile(regUser);
                BankAccount *newAccount = createBankAccount(regUser->id);
                //printf("\nBAReg:%d", newAccount->userId);

                addBankAccount(accounts, newAccount);
                //printf("\nKey:%d", accounts->byUserID->array[regUser->id % 11]->key);
                saveAccountInFile(newAccount);
                // Here we may want to login the user directly.
            }
        }
        else if (choise == 3)
        {
            // write here if needed
            releaseUsers(users);
            releaseBankAccounts(accounts);
            deleleSession(session);
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