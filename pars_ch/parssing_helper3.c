/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_helper3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caziane <caziane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 21:41:29 by caziane           #+#    #+#             */
/*   Updated: 2024/10/07 21:48:36 by caziane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec_w/execution.h"

void	init_expand_args(char **new_line, char **word, int *i, int *dcount)
{
	*new_line = ft_strnew(0);
	*word = ft_strnew(0);
	*i = 0;
	*dcount = 0;
}

char	**ft_strjoin_table(char **a, char **b)
{
	int		size;
	int		i;
	char	**table;

	if (!a)
		return (b);
	if (!b)
		return (a);
	size = table_size(a) + table_size(b);
	i = 0;
	table = my_malloc((size + 1) * sizeof(char *), 0);
	if (!table)
		return (NULL);
	while (i < size)
	{
		if (i < table_size(a))
			table[i] = ft_strdup_mem(a[i]);
		else
			table[i] = ft_strdup_mem(b[i - table_size(a)]);
		i++;
	}
	table[i] = NULL;
	return (table);
}

void	args_loop2(t_cmds **list)
{
	t_cmds	*current;

	current = *list;
	while (current)
	{
		if (current->args)
			loop_norm2(current);
		current = current->next;
	}
}
