
#include <stdio.h>
#include "delete_account.h"

void delete_account (pointer_to_account *beginning)
{
    char email[CHAR_EMAIL];
    pointer_to_account current = *beginning, previous = NULL;
    printf("Enter the email of the account you want to delete\n>>> ");
    scanf("%s", email);
	fflush(stdin);
	while (current != NULL)
    {
        if (strcmp(current->email, email) == 0)
        {
            if (previous != NULL) previous->next = current->next;	// salta la cuenta que va a eliminar para apuntar a la que sigue
            else *beginning = current->next;
            free(current->email);
            free(current->password);
            free(current->nickname);
            free(current);
            printf("Account with email %s deleted successfully\n", email);
            return;
        }
        previous = current;
        current = current->next;
    }
    printf("Account with email %s not found\n", email);
}
