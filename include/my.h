/*
** EPITECH PROJECT, 2019
** my.h
** File description:
** include
*/

#ifndef MY_H
#define MY_H

#include <stddef.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../src/lib/my/lib.h"

#ifndef READ_SIZE
#define READ_SIZE 1
#endif

typedef struct s_glob
{
    int t_pid;
    int res;
    int col;
    int line;
} t_glob;

t_glob *glob;

char *parser_file(char *file);
int len_boat(char **map);
char **create_map(void);

int print_help(int ac, char **av);
void print_map(char **map, char *str);

char **fill_map(char **map, char *str);

char *get_next_line(int fd);
#endif
