/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caziane <caziane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:55:49 by caziane           #+#    #+#             */
/*   Updated: 2024/10/07 21:51:53 by caziane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec_w/execution.h"

int	ft_lstsize(t_list *lst)
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

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (free(s1), NULL);
	ft_memcpy(res, s1, ft_strlen(s1));
	ft_memcpy(res + ft_strlen(s1), s2, ft_strlen(s2));
	res[len] = '\0';
	return (free(s1), res);
}

char	*ft_strjoin_mem(char *s1, char *s2)
{
	size_t	len;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	res = my_malloc((len + 1) * sizeof(char), 0);
	if (!res)
		return (NULL);
	ft_memcpy(res, s1, ft_strlen(s1));
	ft_memcpy(res + ft_strlen(s1), s2, ft_strlen(s2));
	res[len] = '\0';
	return (res);
}

char	*ft_strjoin_char(char *s1, char s2)
{
	size_t	len;
	char	*res;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1) + 1;
	res = my_malloc((len + 1) * sizeof(char), 0);
	if (!res)
		return (NULL);
	ft_memcpy(res, s1, ft_strlen(s1));
	res[len - 1] = s2;
	res[len] = '\0';
	return (res);
}

char	*set_expand(char *line)
{
	int	i;
	int	j;
	int	d_quote;

	j = ft_strlen(line);
	i = -1;
	d_quote = 0;
	while (line && i < j && line[++i])
	{
		if (line[i] == '\"')
			d_quote = !d_quote;
		if (line[i] == '\'' && !d_quote)
		{
			i++;
			while (line[i] && line[i] != '\'')
			{
				line[i] *= -1;
				i++;
			}
		}
	}
	return (line);
}
