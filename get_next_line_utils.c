/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 20:36:34 by mirokugo          #+#    #+#             */
/*   Updated: 2024/05/26 15:02:47 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t count, size_t size)
{
	void		*ptr;
	long long	i;

	i = count * size;
	if (i == 0)
		i = 1;
	else if (i / size != count)
		return (NULL);
	ptr = malloc(i);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, i);
	return (ptr);
}

char	*ft_strdup(const char *s1)
{
	char	*ptr;

	ptr = (char *)malloc(ft_strlen(s1) + 1);
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, s1, ft_strlen(s1) + 1);
	return (ptr);
}

char	*ft_strrchr(const char *s, int c)
{
	char	*last_ad;
	char	c1;

	c1 = (char)c;
	last_ad = NULL;
	if (c1 == '\0')
	{
		while (*s)
			s++;
		return ((char *)s);
	}
	while (*s)
	{
		if (*s == c1)
			last_ad = (char *)s;
		s++;
	}
	return (last_ad);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		s1_len;
	int		s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!result)
		return (NULL);
	while (*s1)
		*result++ = *s1++;
	while (*s2)
		*result++ = *s2++;
	*result = '\0';
	return (result - s1_len - s2_len);
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

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char *ptr;
	size_t i;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}