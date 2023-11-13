#include "main.h"

/*************************PRINT CHAR***********************/

/**
*print_char - char
*@types: list a of arguments
*@buffer: array to handle print
*@flags: calculates active flags
*@width: width
*@precision: precision specification
*@size: specifier
*Return: Number of chars printed
*/
int print_char(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
char c = va_arg(types, int);
return (handle_write_char(c, buffer, flags, width, precision, size));
}
/**************************PRINT A STRING************************/
/**
*print_string - a string
*@types: list a of arguments
*@buffer: array to handle print
*@flags: active flags
*@width: width
*@precision: specification
*@size: specifier size
*Return: Number of char printed
*/
int print_string(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
int length = 0, t;
char *str = va_arg(types, char *);

UNUSED(buffer);
UNUSED(flags);
UNUSED(width);
UNUSED(precision);
UNUSED(size);
if (str == NULL)
{
str = "(null)";
if (precision >= 6)
str = "      ";
}
while (str[length] != '\0')
length++;

if (precision >= 0 && precision < length)
length = precision;
if (width > length)
{
if (flags & F_MINUS)
{
write(1, &str[0], length);
for (t = width - length; t > 0; t--)
write (1, " ", 1);
write(1, &str[0], length);
return (width);
}
}

return (write(1, str, length));
}
/*******************PRINT PERCENT SIGN******************************/
/**
*print_percent - percent sign
*@types: list a of arguments
*@buffer: array to handle print
*@flags: active flags
*@width: width
*@precision: specification
*@size: specifier
*Return: Number of chars printed
*/
UNUSED(types);
UNUSED(buffer);
UNUSED(flags);
UNUSED(width);
UNUSED(precision);
UNUSED(size);
return (write(1, "%%", 1));
}

/******************PRINT INT**********************/
/**
*print_int - int
*@types: list a of arguments
*@buffer: array to handle print
*@flags: active flags
*@width: width
*@precision: specification
*@size: specifier
*Return: Number of chars printed
*/
int print_int(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
int t = BUFF_SIZE - 2;
int is_negative = 0;
long int n = va_arg(types, long int);
unsigned long int num;

n = convert_size_number(n, size);

if (n == 0)
buffer[t--] = '0';

buffer[BUFF_SIZE - 1] = '\0';
num = (unsigned long int)n;

if (n < 0)
{
num = (unsigned long int)((-1) * n);
is_negative = 1;
}

while (num > 0)
{
buffer[t--] = (num % 10) + '0';
num /= 10;
}

t++;

return (write_number(is_negative, t, buffer, flags, width, pricision, size));
}

/************************PRINT BINARY*************************************/
/**
*print_binary - an unsigned number
*@types: list a of arguments
*@buffer: array to handle print
*@flags: active flags
*@width: width
*@precision: specification
*@size: specifier
*Return: Number of char printed
*/
int print_binary(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
unsigned int n, m, t, sum;
unsigned int a[32];
int count;

UNUSED(buffer);
UNUSED(flags);
UNUSED(width);
UNUSED(precision);
UNUSED(size);

n = va_arg(types, unsigned int);
m = 2147483648; /* (2 ^ 31) */
a[0] = n / m;
for (t = 1; t < 32; t++)
{
m /= 2;
a[t] = (n / m) % 2;
}
for (t = 0, sum = 0, count = 0; t < 32; t++)
{
sum += a[t];
if (sum || t == 31)
{
char z = '0' + a[t];

write(1, &z, 1);
count++;
}
}
return (count);
}
