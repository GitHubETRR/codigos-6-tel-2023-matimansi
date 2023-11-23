
#ifndef DEFINICIONES
#define DEFINICIONES

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define CHAR_EMAIL 30
#define CHAR_PASSWORD 10
#define CHAR_NICKNAME 10

typedef struct account_t
{
	char *email;
	char *password;
	char *nickname;
	unsigned int level;
	struct account_t *next;
}account_t;

typedef account_t *pointer_to_account;

#endif