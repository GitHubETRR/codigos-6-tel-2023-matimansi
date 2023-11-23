
#include <stdio.h>
#include "Archivos/Definiciones/definiciones.h"
#include "Archivos/Funciones/recover_accounts.h"
#include "Archivos/Funciones/create_account.h"
#include "Archivos/Funciones/create_account_from_file.h"
#include "Archivos/Funciones/delete_account.h"
#include "Archivos/Funciones/print_accounts.h"
#include "Archivos/Funciones/update_database.h"
#include "Archivos/Funciones/free_up_memory.h"

int main()
{
	char character;
	pointer_to_account beginning = NULL;
	printf("\nRecovering database...\n");
	recover_accounts(&beginning);
	printf("Recovered database\n");
	printf("\n\t ---- Database <==#==> Game Accounts ----\n");
	do
	{
		printf("What do you want to do?\n");
		printf("\t- [ C ] Create account\n");
		printf("\t- [ D ] Delete account\n");
		printf("\t- [ S ] See accounts\n");
		printf("\t- [ U ] Update database\n");
		printf("\t- [ E ] Exit \n");
		printf(">>> ");
		scanf("%c", &character);
		fflush(stdin);
		if ((character == 'C') || (character == 'c'))
		{
			printf("How do you want to create a new account?\n");
			printf("\t- [ M ] Manually\n");
			printf("\t- [ F ] With a file\n");
			printf(">>> ");
			scanf("%c", &character);
			fflush(stdin);
			if ((character == 'M') || (character == 'm')) create_account (&beginning);
			if ((character == 'F') || (character == 'f')) create_account_from_file(&beginning);
		}
		if ((character == 'D') || (character == 'd')) delete_account (&beginning);
		if ((character == 'S') || (character == 's')) print_accounts(beginning);
		if ((character == 'U') || (character == 'u')) update_database(beginning);
	}while (!((character == 'E') || (character == 'e')));
	free_up_memory(&beginning);
	return 0;
}
