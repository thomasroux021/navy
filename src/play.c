/*
** EPITECH PROJECT, 2019
** play.c
** File description:
** play
*/

#include "my.h"

int lose(char **map, char **e_map)
{
    int boat = 0;

    for (int i = 0; map[i] != NULL; i += 1) {
        for (int j = 0; map[i][j]; j += 1) {
            (map[i][j] >= 48 && map[i][j] <= 53) ? boat += 1 : 0;
        }
    }
    if (boat)
        return (0);
    print_map(map, "my positions:\n");
    print_map(e_map, "enemy's positions:\n");
    my_putstr("Enemy won\n\n");
    return (1);
}

int play(char **map, char **e_map, t_glob *glob, int tour)
{
    char *act = "ok";

    print_map(map, "my positions:\n");
    print_map(e_map, "enemy's positions:\n");
    if (!tour) {
        if ((act = attack()) == NULL)
            return (0);
        if ((e_map = send_att(act, e_map, glob->t_pid, map)) == NULL)
            return (0);
        if ((map = e_att(map, glob->t_pid, e_map)) == NULL)
            return (1);
    } else {
        if ((map = e_att(map, glob->t_pid, e_map)) == NULL)
            return (1);
        if ((act = attack()) == NULL)
            return (0);
        if ((e_map = send_att(act, e_map, glob->t_pid, map)) == NULL)
            return (0);
    }
    return (3);
}

int player(char **map, int pid, int tour, t_glob *glob)
{
    char **e_map = create_map();
    int ret;

    (pid != getpid()) ? (glob->t_pid = pid) : (pid = glob->t_pid);
    if (e_map == NULL)
        return (84);
    while (1) {
        if (glob->t_pid == -1)
            return (84);
        if (glob->t_pid == -2)
            return (0);
        if ((ret = play(map, e_map, glob, tour)) != 3) {
            (glob->t_pid == -2) ? ret = 0 : 0;
            return (ret);
        }
    }
    return (84);
}
