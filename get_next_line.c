/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:32:39 by mirokugo          #+#    #+#             */
/*   Updated: 2024/05/20 10:49:40 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;

	ptr = (char *)malloc(ft_strlen(s1) + 1);
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, s1, ft_strlen(s1) + 1);
	return (ptr);
}

char	*ft_strchr(const char *s, int c)
{
	while (c > 127)
		c -= 128;
	while (c < 0)
		c += 128;
	if (c < 0 || c > 127)
		return ((char *)s);
	if (c == '\0')
	{
		while (*s)
			s++;
		return ((char *)s);
	}
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

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
	while (!ft_strchr(save, '\n'))
	{
		i = read(fd, buf, BUFFER_SIZE);
		if (i <= 0)
			break ;
		buf[i] = '\0';
		save = ft_strjoin(save, buf);
	}
	free(buf);
	if (!ft_strchr(save, '\n'))
	{
		line = ft_strdup(save);
		free(save);
		save = NULL;
		return (line);
	}
	i = ft_strchr(save, '\n') - save;
	line = (char *)ft_calloc(i + 1, sizeof(char));
	if (!line)
		return (NULL);
	ft_memcpy(line, save, i);
	ft_memcpy(save, save + i + 1, ft_strlen(save) - i);
	return (line);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	if (!dst && !src)
		return (NULL);
	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
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
// 		printf("%s\n", line);
// 		free(line);
// 		i++;
// 	}
// }
