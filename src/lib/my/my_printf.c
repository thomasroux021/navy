/*
** EPITECH PROJECT, 2019
** JD_my_printf
** File description:
** my_printf file
*/

#include "lib.h"

void flag_manager(char flag, va_list myprintf)
{
    switch (flag) {
    case 'c':
        my_putchar(va_arg(myprintf, int));
        return;
    case 's':
        my_putstr(va_arg(myprintf, char *));
        return;
    case 'd':
        my_put_nbr(va_arg(myprintf, int));
    default:
        return;
    }
}

void my_printf(char *format, ...)
{
    va_list myprintf;

    va_start(myprintf, format);
    for (int i = 0; format[i]; i++) {
        if (format[i] == '%') {
            i++;
            flag_manager(format[i], myprintf);
            i++;
            my_putchar(format[i]);
        } else
            my_putchar(format[i]);
    }
    va_end(myprintf);
}
