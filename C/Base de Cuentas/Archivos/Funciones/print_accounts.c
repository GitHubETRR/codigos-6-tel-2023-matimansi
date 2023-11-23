
#include <stdio.h>
#include "print_accounts.h"

void print_accounts (pointer_to_account beginning)
{
	pointer_to_account aux=beginning;
	unsigned int contador = 1;
	while (aux != NULL)
	{
		printf("\t---- Account number %d ----\n", contador);
		printf("Email: %s\n", aux->email);
		printf("Password: %s\n", aux->password);
		printf("Nickname: %s\n", aux->nickname);
		printf("Level: %d\n\n", aux->level);
		aux = aux->next;
		contador++;
	}
}
