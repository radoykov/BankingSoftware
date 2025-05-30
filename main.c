#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <time.h>
#include "users.h"
// #include "transactions.h"
#include "accounts.h"
#include "database.h"

void showMenu(Session *session)
{
    printf("\nWelcome %s", session->username);

    printf("\nChoose from this options:");
    printf("\n1.Withdraw");
    printf("\n2.Deposit");
    printf("\n3.Transaction");
    printf("\n4.Prosess all transacions");
    printf("\n5.Logout");
    int choise = 0;
    printf("\nYour choise is: ");
    scanf("%d", &choise);
    while (1)
    {
        switch (choise)
        {
        case 1:
            /* code */
            break;
        case 2:
            /* code */
            break;
        case 3:
            /* code */
            break;
        case 4:
            /* code */
            break;
        case 5:
            printf("You succeesfully logged out.");
            session = NULL;
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
                showMenu(session);
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