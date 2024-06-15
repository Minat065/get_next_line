/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:32:39 by mirokugo          #+#    #+#             */
/*   Updated: 2024/05/26 20:21:20 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int			i;
	char		*buf;
	static char	*save;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (NULL);
	if (!save)
		save = ft_strdup("");
	while (!ft_strrchr(save, '\n'))
	{
		i = read(fd, buf, BUFFER_SIZE);
		if (i <= 0)
			break ;
		buf[i] = '\0';
		save = ft_strjoin(save, buf);
	}
	free(buf);
	if (!ft_strrchr(save, '\n'))
	{
		line = ft_strdup(save);
		free(save);
		save = NULL;
		return (line);
	}
	i = ft_strrchr(save, '\n') - save;
	line = (char *)ft_calloc(i + 1, sizeof(char));
	if (!line)
		return (NULL);
	ft_memcpy(line, save, i + 1);
	ft_memcpy(save, save + i + 1, ft_strlen(save) - i - 1);
	return (line);
}

// int	main(void)
// {
// 	int		i;
// 	int		fd;
// 	char	*line;

// 	fd = open("test.txt", O_RDONLY);
// 	i = 0;
// 	while (i < 10)
// 	{
// 		line = get_next_line(fd);
// 		printf("%s", line);
// 		free(line);
// 		i++;
// 	}
// }
