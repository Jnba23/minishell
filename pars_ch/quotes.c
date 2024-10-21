/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caziane <caziane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 20:35:21 by caziane           #+#    #+#             */
/*   Updated: 2024/10/11 02:08:42 by caziane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec_w/execution.h"

char	*rm_quotes_herdoc(char *deli)
{
	int		i;
	char	*arg;

	arg = ft_strnew(0);
	i = 0;
	while (deli && deli[i])
	{
		if (deli[i] == '\'')
		{
			i++;
			skip_quotes_hd(deli, &i, &arg, 0);
			if (deli[i] == '\'')
				i++;
		}
		else if (deli[i] == '\"')
		{
			i++;
			skip_quotes_hd(deli, &i, &arg, 1);
			if (deli[i] == '\"')
				i++;
		}
		else
			arg = ft_strjoin_char(arg, deli[i++]);
	}
	return (arg);
}

void	cq_helper(t_cmds *current, char **arg, int *i)
{
	while (current->cmd[*i])
	{
		if (current->cmd[*i] == '\'')
		{
			(*i)++;
			while (current->cmd[*i] && current->cmd[*i] != '\'')
				*arg = ft_strjoin_char(*arg, current->cmd[(*i)++]);
			if (current->cmd[*i] == '\'')
				(*i)++;
		}
		else if (current->cmd[*i] == '\"')
		{
			(*i)++;
			while (current->cmd[*i] && current->cmd[*i] != '\"')
				*arg = ft_strjoin_char(*arg, current->cmd[(*i)++]);
			if (current->cmd[*i] == '\"')
				(*i)++;
		}
		else
		{
			*arg = ft_strjoin_char(*arg, current->cmd[*i]);
			(*i)++;
		}
	}
}

void	rm_quotes_cmd(t_cmds *list)
{
	t_cmds	*current;
	int		i;
	char	*arg;

	current = list;
	while (current)
	{
		if (current->cmd)
		{
			i = 0;
			arg = ft_strnew(0);
			cq_helper(current, &arg, &i);
			current->cmd = arg;
		}
		current = current->next;
	}
}

void	rm_helper(t_cmds *current, char **arg, int *i, int *j)
{
	while (current->args[*i][*j])
	{
		if (current->args[*i][*j] == '\'')
		{
			(*j)++;
			while (current->args[*i][*j] && current->args[*i][*j] != '\'')
				*arg = ft_strjoin_char(*arg, current->args[*i][(*j)++]);
			if (current->args[*i][*j] == '\'')
				(*j)++;
		}
		else if (current->args[*i][*j] == '\"')
		{
			(*j)++;
			while (current->args[*i][*j] && current->args[*i][*j] != '\"')
				*arg = ft_strjoin_char(*arg, current->args[*i][(*j)++]);
			if (current->args[*i][*j] == '\"')
				(*j)++;
		}
		else
			*arg = ft_strjoin_char(*arg, current->args[*i][(*j)++]);
	}
}

void	rm_quotes(t_cmds *list)
{
	t_cmds	*current;
	int		i;
	int		j;
	char	*arg;

	current = list;
	while (current)
	{
		if (current->args)
		{
			i = 0;
			while (current->args[i])
			{
				arg = ft_strnew(0);
				j = 0;
				rm_helper(current, &arg, &i, &j);
				current->args[i] = arg;
				i++;
			}
		}
		current = current->next;
	}
}
