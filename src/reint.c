/*
 ============================================================================
 Name        : reint.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <pthread.h>
#include <malloc.h>
#include <string.h>



pthread_once_t once;
pthread_key_t key;

void creat_key()
{
	pthread_key_create(&key, NULL);
}

char* refunc(int ch)
{
	char *str;
	pthread_once(&once, creat_key);

	if((str=pthread_getspecific(key))==0)
	{
		str=malloc(255);
		pthread_setspecific(key, str);
	}

	switch(ch)
	{
	case 1:
		strcpy(str, "Oshibka n1");
		return str;
	case 2:
		strcpy(str, "Oshibka n2");
				return str;
	case 3:
		strcpy(str, "Oshibka n3");
				return str;
	default:
		strcpy(str, "OSHIBKA NE NAIDENA");
		return str;
	}

}



void *error(void *ch)
{
	int* ch1;
	ch1=(int*)ch;
	char *errorch;
	errorch = refunc(*ch1);
	printf("%s\n", errorch);
	fflush(stdout);
}

int main(void)
{
	pthread_t tid[4];
	for(int i=0; i<4;i++)
		pthread_create(&tid[i], NULL, error, &i);

	return 1;
}
