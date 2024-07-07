/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:32:39 by mirokugo          #+#    #+#             */
/*   Updated: 2024/07/07 20:01:29 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char *read_to_leftover(int fd, char *leftover)
{
    char    *buffer;
    int     read_bytes;
    char    *temp;

    buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buffer)
        return (NULL);
    read_bytes = 1;
    while (!leftover || (!ft_strchr(leftover, '\n') && read_bytes != 0))
    {
        read_bytes = read(fd, buffer, BUFFER_SIZE);
        if (read_bytes == -1)
        {
            free(buffer);
            free(leftover);
            return (NULL);
        }
        buffer[read_bytes] = '\0';
        temp = leftover;
        leftover = ft_strjoin(temp ? temp : "", buffer);
        free(temp);
        if (!leftover)
        {
            free(buffer);
            return (NULL);
        }
    }
    free(buffer);
    return (leftover);
}

static char	*extract_line(char *leftover)
{
    int		i;
    char	*line;

    i = 0;
    if (!leftover[i])
        return (NULL);
    while (leftover[i] && leftover[i] != '\n')
        i++;
    line = ft_substr(leftover, 0, i + 1);
    if (!line)
        return (NULL);
    if (line[i] == '\n')
        line[i + 1] = '\0';
    return (line);
}

static char *update_leftover(char *leftover)
{
    int     i;
    char    *new_leftover;

    i = 0;
    while (leftover[i] && leftover[i] != '\n')
        i++;
    if (!leftover[i])
    {
        free(leftover);
        return (NULL);
    }
    if (leftover[i + 1] == '\0')
    {
        free(leftover);
        return (ft_strdup(""));
    }
    new_leftover = ft_substr(leftover, i + 1, ft_strlen(leftover) - i - 1);
    free(leftover);
    return (new_leftover);
}

char    *get_next_line(int fd)
{
    static char *leftover;
    char        *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    leftover = read_to_leftover(fd, leftover);
    if (!leftover)
        return (NULL);
    line = extract_line(leftover);
    leftover = update_leftover(leftover);
    return (line);
}


// int	main(void)
// {
//     int		i;
//     int		fd;
//     char	*line;

//     fd = open("test.txt", O_RDONLY);
//     if (fd == -1)
//     {
//         perror("Error opening file");
//         return (1);
//     }
//     i = 0;
//     while (i < 10)
//     {
//         line = get_next_line(fd);
//         if (line == NULL)
//             break;
//         printf("%s", line);
//         free(line);
//         i++;
//     }
//     close(fd);
//     return (0);
// }
