
#include <stdio.h>
#include "recover_accounts.h"

void recover_accounts (pointer_to_account *beginning)
{
	FILE *file = fopen("Archivos/Base de Datos/Recursos/base_de_datos.txt", "r");
	if (!file)
	{
		printf("ERROR when opening the file");
		exit (1);
	}
	while (true)
	{
		pointer_to_account new = (pointer_to_account) malloc (sizeof(account_t));
		char *email = (char *) malloc (CHAR_EMAIL * sizeof(char));
		char *password = (char *) malloc (CHAR_PASSWORD * sizeof(char));
		char *nickname = (char *) malloc (CHAR_NICKNAME * sizeof(char));
		if (!email || !password || !nickname)
		{
            printf("ERROR in memory allocation");
            exit(1);
        }
		new->next = NULL;
		if (fscanf(file, "%s", email) != 1) break;
		fscanf(file, "%s", password);
		fscanf(file, "%s", nickname);
		fscanf(file, "%d", &(new->level));
		new->email = email;
		new->password = password;
		new->nickname = nickname;
		new->next = *beginning;
		*beginning = new;
		if(feof(file)) break;
	}
	fclose(file);
}
