#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *filter(char *input, char *word) {
	size_t word_len = strlen(word);
	char *stars = malloc(word_len + 1);
	memset(stars, '*', word_len);
	stars[word_len] = '\0';
	size_t input_len = strlen(input);
	char *result = malloc(input_len + 1);
	char *dest = result;
	char *src = input;
	while (*src) {
		if (strncmp(src, word, word_len) == 0) {
			strcpy(dest, stars);
			dest += word_len;
			src += word_len;
		} else {
			*dest++ = *src++;
		}
	}
	*dest = '\0';
	free(stars);
	return result;
}

int main(int argc, char **argv) {
	if (argc > 2) {
		char *result = filter(argv[1], argv[2]);
		printf("%s\n", result);
		free(result);
	}
	return 0;
}