/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldusty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 18:03:11 by ldusty            #+#    #+#             */
/*   Updated: 2022/02/19 18:09:19 by ldusty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../pipex.h"

void	error(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

size_t	ft_strlen(const char *a)
{
	size_t	len;

	len = 0;
	while (a[len])
		len++;
	return (len);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n-- > 0)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		else if (!*s1++ || !*s2++)
			return (0);
	}
	return (0);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dsize)
{
	size_t	i;

	i = 0;
	if (dsize > 0)
	{
		while (src[i] && (i + 1 < dsize))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

size_t	ft_strlcat(char *dst, const char *src, size_t dsize)
{
	char		*d;
	const char	*s;
	size_t		dlen;
	size_t		size;

	d = dst;
	s = src;
	size = dsize;
	while (size-- && *d)
		d++;
	dlen = d - dst;
	size = dsize - dlen;
	if (!size)
		return (dlen + ft_strlen(s));
	while (*s)
	{
		if (size != 1)
		{
			*d++ = *s;
			size--;
		}
		s++;
	}
	*d = '\0';
	return (dlen + (s - src));
}
