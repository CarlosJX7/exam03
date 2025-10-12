#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int filter(char *cadena, char *word) 
{
	int i = 0;
	int j = 0;
	int ret = 0;
	while (cadena[i])
	{
		if (cadena[i] != word[j])
		{
			j = 0;
		}
		if (cadena[i] == word[j])
		{
			if (j == strlen(word) - 1)
			{
				ret = 1;
				printf("Econtrada la palabra: >%s<\n", word);
				j = 0;
			}
			j++;
		}
		i++;
	}
	return ret;
}

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		printf("Error en los argumentos\n");
		return 1;
	}
	char *cadena = argv[1];
	char *word = argv[2];
	if (!filter(cadena, word))
	{
		printf("No se ha encontrado la palabra: >%s<\n", word);
	}

	return 0;
}