/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caziane <caziane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:15:51 by caziane           #+#    #+#             */
/*   Updated: 2024/10/07 16:19:53 by caziane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec_w/execution.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (!d && !s)
		return (NULL);
	if (d != s)
	{
		while (n > 0)
		{
			*d = *s;
			d++;
			s++;
			n--;
		}
	}
	return (dst);
}

int	inset(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char const *set)
{
	size_t	l;
	size_t	r;
	char	*res;

	l = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[l] && inset(set, s1[l]) == 1)
		l++;
	if (l == (size_t)ft_strlen(s1))
	{
		res = my_malloc(1, 0);
		if (!res)
			return (NULL);
		res[0] = '\0';
		return (res);
	}
	r = ft_strlen(s1) - 1;
	while (s1[r] && inset(set, s1[r]) == 1)
		r--;
	res = my_malloc((r - l + 1 + 1) * sizeof(char), 0);
	if (!res)
		return (NULL);
	ft_memcpy(res, s1 + l, r - l + 1);
	return (res[r - l + 1] = '\0', res);
}

char	*ft_strdup_mem(char *src)
{
	char	*dup;
	size_t	i;
	size_t	l;

	i = 0;
	l = ft_strlen(src);
	dup = my_malloc(sizeof(char) * (l + 1), 0);
	if (!dup)
		return (NULL);
	while (i < l)
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	ft_strncpy(char *dest, const char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}
