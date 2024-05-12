/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:32:39 by mirokugo          #+#    #+#             */
/*   Updated: 2024/05/12 20:15:51 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

char	ft_getchar(int fd)
{
	char	c;

	read(fd, &c, BUFFER_SIZE);
	return (c);
}

char	*get_next_line(int fd)
{
	int		i;
	int		j;
	char	c;
	char	*result;

	i = 0;
	j = 0;
	result = (char *)malloc(sizeof(char) * 1024);
	if (!result)
		return (NULL);
	while (1)
	{
		c = ft_getchar(fd);
		if (c == '\n' || c == '\0' || c == EOF || c == -1 || c == 0)
			break ;
		result[i] = c;
		i++;
	}
	if (c == EOF || c == -1 || c == 0)
	{
		free(result);
		return (NULL);
	}
	result[i] = '\0';
	return (result);
}

int	main(void)
{
	int		i;
	int		j;
	int		fd;
	char	*str;

	fd = open("test.txt", O_RDONLY);
	i = 0;
	j = 0;
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		printf("%s\n", str);
		free(str);
	}
}
