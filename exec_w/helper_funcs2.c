/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_funcs2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caziane <caziane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 07:27:44 by asayad            #+#    #+#             */
/*   Updated: 2024/10/11 03:42:56 by caziane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*ft_strlcpy_gnl(char *s1, char *s2, char *line, int l)
{
	int		i;
	int		j;

	i = -1;
	j = ft_strlen(s2);
	while (++i < l - j)
		line[i] = s1[i];
	while (--j >= 0)
		line[i + j] = s2[j];
	line[l] = '\0';
	return (line);
}

char	*join_env(char *s1, char *s2)
{
	char	*line;
	int		l;

	if (!s2)
		return (NULL);
	if (!s1)
	{
		s1 = my_malloc(sizeof(char), 0);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	l = ft_strlen(s1) + ft_strlen(s2);
	line = my_malloc ((l + 1) * sizeof(char), 0);
	if (!line)
		return (NULL);
	line = ft_strlcpy_gnl(s1, s2, line, l);
	return (s1 = NULL, s2 = NULL, line);
}

void	free_table(char **table)
{
	int	i;

	i = 0;
	if (!table || !*table)
		return ;
	while (table[i])
		free(table[i++]);
	free(table);
}

int	ft_strlcpy(char *dst, char *src, int dstsize)
{
	int	i;
	int	lsrc;

	i = 0;
	lsrc = ft_strlen(src);
	if (dstsize == 0)
		return (lsrc);
	while (src[i] != '\0' && i < (dstsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (lsrc);
}

void	print_table(char **a)
{
	int	i;

	i = 0;
	if (!a || !*a)
		return ;
	while (a[i])
	{
		printf("%s\n", a[i]);
		i++;
	}
}
