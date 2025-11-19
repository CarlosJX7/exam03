#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
    int c;
    int matched = 0;
    
    while ((c = fgetc(f)) != EOF && isspace(c))
        matched = 1;
    
    if (c != EOF)
        ungetc(c, f);
    
    return matched ? 1 : 0;
}

int match_char(FILE *f, char c)
{
    int ch = fgetc(f);
    
    if (ch == EOF)
        return -1;
    
    if (ch == c)
        return 1;
    
    ungetc(ch, f);
    return 0;
}

int scan_char(FILE *f, va_list ap)
{
    char *p = va_arg(ap, char *);
    int c = fgetc(f);
    
    if (c == EOF)
        return -1;
    
    *p = (char)c;
    return 1;
}

int scan_int(FILE *f, va_list ap)
{
    int *p = va_arg(ap, int *);
    int c;
    int sign = 1;
    int value = 0;
    int digits = 0;
    
    // Handle optional sign
    c = fgetc(f);
    if (c == '-')
    {
        sign = -1;
    }
    else if (c == '+')
    {
        sign = 1;
    }
    else if (isdigit(c))
    {
        value = c - '0';
        digits = 1;
    }
    else
    {
        if (c != EOF)
            ungetc(c, f);
        return -1;
    }
    
    // Read digits
    while ((c = fgetc(f)) != EOF && isdigit(c))
    {
        value = value * 10 + (c - '0');
        digits = 1;
    }
    
    if (c != EOF)
        ungetc(c, f);
    
    if (digits == 0)
        return -1;
    
    *p = value * sign;
    return 1;
}

int scan_string(FILE *f, va_list ap)
{
    char *p = va_arg(ap, char *);
    int c;
    int count = 0;
    
    // Read non-whitespace characters
    while ((c = fgetc(f)) != EOF && !isspace(c))
    {
        *p++ = (char)c;
        count++;
    }
    
    if (c != EOF)
        ungetc(c, f);
    
    if (count == 0)
        return -1;
    
    *p = '\0';  // Null-terminate the string
    return 1;
}


int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}
	
	if (ferror(f))
		return EOF;
	return nconv;
}


int ft_scanf(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	int ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return ret;
}


int main()
{
	int num;
	char str[100];
	char c;
	
	printf("Enter a number: ");
	if (ft_scanf("%d", &num) == 1)
		printf("You entered: %d\n", num);
	
	printf("Enter a string: ");
	if (ft_scanf("%s", str) == 1)
		printf("You entered: %s\n", str);
	
	printf("Enter a character: ");
	if (ft_scanf(" %c", &c) == 1)  // Note the space before %c
		printf("You entered: %c\n", c);
	
	return 0;
}