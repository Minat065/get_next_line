/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 04:18:51 by mirokugo          #+#    #+#             */
/*   Updated: 2024/09/08 04:18:58 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char **argv)
{
    int fd;
    char *line;

    if (argc == 2)
    {
        fd = open(argv[1], O_RDONLY);
        while ((line = get_next_line(fd)))
        {
            printf("%s\n", line);
            free(line);
        }
        close(fd);
    }
    else
    {
        printf("Usage: ./gnl_test file_name\n");
    }
    return (0);
}
