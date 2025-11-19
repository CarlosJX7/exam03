#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef enum s_bool
{
	false,
	true
}	t_bool;

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
				printf("Encontrada la palabra: >%s<\n", word);
				j = 0;
			}
			j++;
		}
		i++;
	}
	return ret;
}

int ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
	{
		i++;
	}
	return i;
}
t_bool is_word(char *cadena, char *word, int i)
{

	while (cadena[i])
	{
		if (cadena[i] != word[i])
			break;
		i++;
	}
	if (i == ft_strlen(word))
		return true;
	return false;
}

t_bool filter_v2(char *cadena, char *word)
{
	int i;
	t_bool flag;
	int len;

	flag = false;
	len = 0;
	i = 0;
	while (cadena[i])
	{
		flag = is_word(cadena, word, i);
		if (flag)
			printf("Se ha encontrado la palabra en %d\n", i);
		printf("c = %c\n", cadena[i]);
		i++;		
	}
	return true;
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
	filter_v2(cadena, word);

	/*
	if (!filter(cadena, word))
	{
		printf("No se ha encontrado la palabra: >%s<\n", word);
	}
	*/

	return 0;
}