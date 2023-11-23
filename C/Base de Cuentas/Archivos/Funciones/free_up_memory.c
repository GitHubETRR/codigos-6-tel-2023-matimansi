
#include <stdio.h>
#include "free_up_memory.h"

void free_up_memory (pointer_to_account *beginning)
{
	pointer_to_account current;
	printf("Releasing memory...\n");
	while (*beginning != NULL)
	{
		current = *beginning;
		*beginning = (*beginning)->next;
		free(current->email);
		free(current->password);
		free(current->nickname);
		free(current);
	}
	printf("Memory released");
}
