/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caziane <caziane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:36:23 by caziane           #+#    #+#             */
/*   Updated: 2024/10/07 22:05:09 by caziane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec_w/execution.h"

static	int	countdigit(int d)
{
	int	count;

	count = 0;
	if (d == 0)
		return (1);
	if (d < 0)
	{
		count++;
		d = -d;
	}
	while (d > 0)
	{
		d = d / 10;
		count++;
	}
	return (count);
}

static	char	*specielcase(int n)
{
	if (n == -2147483648)
		return (ft_strdup_mem("-2147483648"));
	return (NULL);
}

char	*ft_itoa(int n)
{
	char	*r;
	int		d;
	int		signe;

	d = countdigit(n);
	signe = 1;
	if (n == -2147483648)
		return (specielcase(n));
	if (n < 0)
	{
		n = -n;
		signe = -1;
	}
	r = my_malloc((d + 1) * sizeof(char), 0);
	if (!r)
		return (NULL);
	r[d] = '\0';
	while (d > 0)
	{
		r[--d] = n % 10 + '0';
		n = n / 10;
	}
	if (signe == -1)
		r[0] = '-';
	return (r);
}

void	delet(void *k)
{
	free(k);
}

void	ft_lstclear_env(t_list **lst, void (*delet)(void*))
{
	t_list	*cur_node;
	t_list	*nxt_node;

	if (!lst || !delet)
		return ;
	cur_node = (*lst);
	while (cur_node)
	{
		nxt_node = cur_node -> next;
		delet (cur_node->content);
		free (cur_node);
		cur_node = nxt_node;
	}
	*lst = NULL;
}
