#include "main.h"
/**
*handle_print - argument based on its type
*by Bassey and Daniel
*@fmt: string in which to print the arguments
*@list: list of argument
*@ind: ind
*@buffer: array to handle print
*@flags: active flags
*@width: get width
*@precision: specification
*@size: specifier
*Return: 1 or 2;
*/
int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
int flags, int width, int precision, int size)
{
int t, unknow_len = 0, printed_chars = -1;
fmt_t fmt_types[] = {
{'c', print_char}, {'s', print_string}, {'%', print_percent},
{'i', print_int}, {'d', print_int}, {'b', print_binary},
{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
{'x', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
};
for (t = 0; fmt_types[t].fmt != '\0'; t++)
if (fmt[*ind] == fmt_types[t].fmt)
return (fmt_types[t].fn(list, buffer, flags, width, precision, size));

if (fmt_types[t].fmt == '\0')
{
if (fmt[*ind] == '\0')
return (-1);
unknow_len += write(1, "%%", 1);
if (fmt[*ind - 1] == ' ')
unknow_len += write(1, " ", 1);
else if (width)
{
--(*ind);
while (fmt[*ind] != ' ' && fmt[*ind] !=  '%')
--(*ind);
if (fmt[*ind] == ' ')
--(*ind);
return (1);
}
unknow_len += write(1, &fmt[*ind], 1);
return (unknow_len);
}
return (printed_chars);
}
