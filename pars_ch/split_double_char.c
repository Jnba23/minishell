/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_double_char.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:34:44 by asayad            #+#    #+#             */
/*   Updated: 2024/10/18 19:00:38 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	countword(const char *s, char c, char p)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while ((s[i] == c || s[i] == p) && s[i])
			i++;
		if (s[i] != '\0')
			j++;
		while (s[i] != c && s[i] != p && s[i])
			i++;
	}
	return (j);
}

static int	charcount(const char *s, char c, char a, int *p)
{
	int	nw;

	nw = 0;
	while ((s[*p] == c || s[*p] == a) && s[*p])
		(*p)++;
	while (s[*p + nw] != c && s[*p + nw] != a && s[*p + nw])
		nw++;
	return (nw);
}

char	**ft_split_double(char *s, char c, char p)
{
	int		i;
	char	**ar;
	int		k;

	k = 0;
	i = 0;
	if (!s)
		return (NULL);
	ar = my_malloc((countword(s, c, p) + 1) * sizeof(char **), 0);
	if (!ar)
		return (NULL);
	while (k < countword(s, c, p))
	{
		ar[k] = my_malloc((charcount(s, c, p, &i) + 1) * sizeof(char), 0);
		if (!ar[k])
			return (NULL);
		ft_strlcpy(ar[k], s + i, charcount(s, c, p, &i) + 1);
		k++;
		i += charcount(s, c, p, &i);
	}
	ar[k] = NULL;
	return (ar);
}

int	only_spaces(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}
