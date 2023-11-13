#include "main.h"

/******************* WRITE HANDLE ********************/
/**
*handler_write_char - a string
*by Bassey and Daniel
*@c: char
*@buffer: Buffer array
*@flags: active flags
*@width: width
*@precision: precision specifier
*@size: Size specificier
*
*Return: Number of chars printed
*/
int handle_write_char(char c, char buffer[],
int flags, int width, int precision, int size)
{
/* char is stored at left and paddind at buffer's right */
int t = 0;
char padd = ' ';

UNUSED(precision);
UNUSED(size);

if (flags & F_ZERO)
padd = '0';

buffer[t++] = c;
buffer[t] = '\0';

if (width > 1)
{
buffer[BUFF_SIZE - 1] = '\0';
for (t = 0; t < width - 1; t++)
buffer[BUFF_SIZE - t - 2] = padd;

if (flags & F_MINUS)
return (write(1, &buffer[0], 1) +
write(1, &buffer[BUFF_SIZE - t - 1], width - 1));
else
return (write(1, &buffer[BUFF_SIZE - t - 1], width - 1) +
write(1, &buffer[0], 1));
}
return (write(1, &buffer[0], 1));
}
}

/******************************** WRITE NUMBER *****************************/
/**
*write_number - a string
*@is_negative: list a of arguments
*@ind: char
*@buffer: Buffer array
*@flags: active flags
*@width: width
*@precision: precision specifier
*@size: size specifier
*
*Return: Number of chars printed.
*/
int write_number(int is_negative, int ind, char buffer[],
int flags, int width, int precision, int size)
{
int length = BUFF_SIZE - ind - 1;
char padd = ' ', extra_ch = 0;

UNUSED(size);

if ((flags & F_ZERO) && !(flags & F_MINUS))
padd '0';
if (is_negative)
extra_ch = '-';
else if (flags & F_PLUS)
extra_ch = '+';
else if (flags & F_SPACE)
extra_ch = ' ';

return (write_num(ind, buffer, flags, width, precision,
length, padd, extra_ch));
}

/**
*write_num - a number using buffer
*@ind: number start on the buffer with index
*@buffer: Buffer
*@flags: flags
*@width: width
*@prec: precision spectifier
*@length: Length number
*@padd: char pading
*@extra_c: char extra
*
*Return: Number of printed chars
*/
int write_num(int ind, char buffer[],
int flags, int width, int prec,
int length, char padd, char extra_c)
{
int t, padd_start = 1;

if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
return (0); /* printf(".0d", 0) no char is printed */
if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
buffer[ind] = padd = ' '; /* width is displayed with padding ' ' */
if (prec > 0 && prec < length)
padd = ' ';
while (prec > length)
buffer[--ind] = '0', length++;
if (extra_c != 0)
length++;
if (width > length)
{
for (t = 1; t < width - length + 1; t++)
buffer[t] = padd;
buffer[t] = '\0';
if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
{
if (extra_c)
buffer[--ind] = extra_c;
return (wwrite(1, &buffer[ind], length) + write(1, &buffer[1], t - 1));
}
else if (!(flags & F_MINUS) && padd == ' ') /* extra char to left of buff */
{
{
if (extra_c)
buffer[--ind] = extra_c;
return (write(1, &buffer[1], t - 1) + write(1, &buffer[ind], length));
}
else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
{
if (extra_c)
buffer[--padd_start] = extra_c;
return (write(1, &buffer[padd_start], t - padd_start) +
write(1, &buffer[ind], length - (1 - padd_start)));
}
}
if (extra_c)
buffer[--ind] = extra_c;
return (write(1, &buffer[ind], length));
}

/**
*write_unsgnd - unsigned number
*@is_negative: if the num is negative
*@ind: index
*@buffer: chars array
*@flags: flags specifiers
*@width: width specifier
*@precision: precision specifier
*@size: size specifier
*
*Return: Number of written chars.
*/
int write_unsgnd(int is_negative, int ind,
char buffer[],
int flags, int width, int precision, int size)
{
/* The number is stored at the buffer's right and starts at position t */
int length = BUFF_SIZE - ind - 1, t = 0;
char padd = ' ';
UNUSED(is_negative);
UNUSED(size);

if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
return (0); /* printf(".0d", 0) no char printed */
if (precision > 0 && precision < length)
padd = ' ';
while (precision > length)
{
buffer[--ind] = '0';
length++;
}

if ((flags & F_ZERO) && !(flags & F_MINUS))
padd = '0';
if (width > length)
{
for (t = 0; t < width - length; t++)
buffer[t] = '\0';

if (flags & F_MINUS) /* Asign extra char to left of buffer [buffer>padd]*/
{
return (write(1, &buffer[ind], length) + write(1, &buffer[0], t));
}
else /* Asign extra char to left of padding [padd>buffer]*/
{
return (write(1, &buffer[0], t) + write(1, &buffer[ind], length));
}
}

return (write(1, &buffer[ind], length));
}
/**
*write_pointer - a memory address
*@buffer: chars array
*@ind: index
*@length: number length
*h: number length
*@width: width specifier
*@flags: flags specifier
*@padd: char representing extra padding
*@extra_c: char representing extra char
*@padd_start: Index
*
*Return: Number of written chars.
*/
int write_pointer(char buffer[], int ind, int length,
int width, int flags, char padd, char extra_c, int padd_start)
{
int t
if (width > length)
{
for (t = 3; t < width - length + 3; t++)
buffer[t] = padd;
buffer[t] = '\0';
if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
{
buffer[--ind] = 'x';
buffer[--ind] = '0';
if (extra_c)
buffer[--ind] = extra_c;
return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
