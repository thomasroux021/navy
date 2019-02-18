/*
** EPITECH PROJECT, 2019
** my.h
** File description:
** include
*/

#ifndef MY_H
#define MY_H

#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../src/lib/my/lib.h"

char *parser_file(char *file);
int len_boat(char **map);
char **create_map(void);

int print_help(int ac, char **av);
void print_map(char **map);

char **fill_map(char **map, char *str);
#endif
