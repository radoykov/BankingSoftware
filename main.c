#include <stdio.h>
#include "transactions.h"
#include "users.h"
#include "accounts.h"

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