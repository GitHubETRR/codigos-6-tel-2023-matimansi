
#include <stdio.h>
#include "update_database.h"

void update_database (pointer_to_account begininng)
{
	int number = 1;
	time_t current_time = time(NULL);
    struct tm *date_hour = localtime(&current_time);
	pointer_to_account aux = begininng;
	FILE *user = fopen("Archivos/Base de Datos/Usuario/base_de_datos.txt", "w");
	FILE *file = fopen("Archivos/Base de Datos/Recursos/base_de_datos.txt", "w");
	if (!file)
	{
		printf("ERROR when opening the file");
		exit (1);
	}
	fprintf(user, "%02d/%02d/%04d %02d:%02d:%02d\n\n",
            date_hour->tm_mday, date_hour->tm_mon + 1, date_hour->tm_year + 1900,
            date_hour->tm_hour, date_hour->tm_min, date_hour->tm_sec);
	while (aux != NULL)
	{
		fputs("----------------------------------------\n", user);
		fprintf(user, "Account Number: %d\n", number);
		fprintf(user, "\t- Email %s\n", aux->email);
		fprintf(user, "\t- Password %s\n", aux->password);
		fprintf(user, "\t- Nickname %s\n", aux->nickname);
		fprintf(user, "\t- Level %d\n", aux->level);
		fprintf(file, "%s\n", aux->email);
		fprintf(file, "%s\n", aux->password);
		fprintf(file, "%s\n", aux->nickname);
		fprintf(file, "%d\n", aux->level);
		aux = aux->next;
		number++;
	}
	fputs("----------------------------------------\n", user);
	fclose(user);
	fclose(file);
	printf("Database was updated successfully\n");
}
