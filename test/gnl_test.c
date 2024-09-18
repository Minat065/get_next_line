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

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "../get_next_line.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *line;
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        perror("Cannot open file");
        return EXIT_FAILURE;
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);  // Assuming newline is included in line
        free(line);
    }

    close(fd);
    return EXIT_SUCCESS;
}
