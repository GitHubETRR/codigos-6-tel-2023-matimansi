
#include <stdio.h>
#include "create_account.h"

void create_account (pointer_to_account *beginning)
{
	pointer_to_account new = (pointer_to_account) malloc (sizeof(account_t));
	new->next = NULL;
	char *email = (char*) malloc (CHAR_EMAIL * sizeof(char));
	char *password = (char*) malloc (CHAR_PASSWORD * sizeof(char));
	char *nickname = (char*) malloc (CHAR_NICKNAME * sizeof(char));
	if (!email || !password || !nickname)
	{
		printf("ERROR in memory allocation");
		exit(1);
	}
    printf("Enter the email adress\n>>> ");
    scanf("%s", email);
    new->email = email;
    printf("Enter the password\n>>> ");
    scanf("%s", password);
    new->password = password;
    printf("Enter the nickname\n>>> ");
    scanf("%s", nickname);
    new->nickname = nickname;
    printf("Enter the level\n>>> ");
    scanf("%d", &(new->level));
	fflush(stdin);
	new->next = *beginning;
	*beginning = new;
}
