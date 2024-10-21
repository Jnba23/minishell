/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_mini.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caziane <caziane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:34:44 by asayad            #+#    #+#             */
/*   Updated: 2024/10/10 00:15:25 by caziane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	countword(const char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != '\0')
			j++;
		while (s[i] != c && s[i])
			i++;
	}
	return (j);
}

static int	charcount(const char *s, char c, int *p)
{
	int	nw;

	nw = 0;
	while (s[*p] == c && s[*p])
		(*p)++;
	while (s[*p + nw] != c && s[*p + nw])
		nw++;
	return (nw);
}

// static void	*allocfail(char **ar, int k)
// {
// 	int	i;

// 	i = 0;
// 	while (i < k)
// 	{
// 		free(ar[i]);
// 		i++;
// 	}
// 	free(ar);
// 	return (NULL);
// }

char	**ft_split_mini(char *s, char c)
{
	int		i;
	char	**ar;
	int		k;

	k = 0;
	i = 0;
	if (!s)
		return (NULL);
	ar = my_malloc((countword(s, c) + 1) * sizeof(char **), 0);
	if (!ar)
		return (NULL);
	while (k < countword(s, c))
	{
		ar[k] = my_malloc((charcount(s, c, &i) + 1) * sizeof(char), 0);
		if (!ar[k])
			return (NULL);
		ft_strlcpy(ar[k], s + i, charcount(s, c, &i) + 1);
		k++;
		i += charcount(s, c, &i);
	}
	ar[k] = NULL;
	return (ar);
}

int	ft_lstsize_mini(t_list *lst)
{
	int	count;

	count = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		lst = lst -> next;
		count++;
	}
	return (count);
}
