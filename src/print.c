/*
** EPITECH PROJECT, 2019
** print.c
** File description:
** print
*/

#include "my.h"

int print_help(int ac, char **av)
{
    if (ac == 2 && !my_strcmp(av[1], "-h")) {
        my_putstr("USAGE\n     ./navy [first_player_pid] navy_positions\nDESC");
        my_putstr("RIPTION\n     first_player_pid:  only for the 2nd player. ");
        my_putstr(" pid of the first player.\n     navy_positions:  file repr");
        my_putstr("ensenting the positions of the ships.\n");
        return (0);
    }
    return (-1);
}

void print_map(char **map)
{
    my_putstr("  ABCDEFGH\n");
    for (int i = 0; map[i] != NULL; i += 1) {
        my_put_nbr(i + 1);
        my_putchar(' ');
        my_putstr(map[i]);
        my_putchar('\n');
    }
}
