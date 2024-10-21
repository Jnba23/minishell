/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caziane <caziane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 21:47:32 by caziane           #+#    #+#             */
/*   Updated: 2024/10/14 19:31:54 by caziane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec_w/execution.h"

void	cmds_loop(t_list **env, t_cmds **list)
{
	t_cmds	*current;

	current = *list;
	while (current)
	{
		if (current->cmd)
		{
			if (ft_strchr(current->cmd, '\''))
				cmd_expand1(current, env);
			else
				cmd_expand2(current, env);
		}
		current = current->next;
	}
}

void	args_loop(t_list **env, t_cmds **list)
{
	t_cmds	*current;
	int		i;

	i = 0;
	current = *list;
	while (current)
	{
		current->quotes = 0;
		if (current->args)
		{
			i = 0;
			while (current && i < table_size(current->args))
			{
				if (ft_strchr(current->args[i], '\''))
					arg_expand1(&current, env, &i);
				else
					arg_expand2(&current, env, &i);
				i++;
			}
		}
		if (current)
			current = current->next;
	}
}

void	loop_norm(t_cmds *current, int *i)
{
	char	**new_args;
	char	**old_args;

	new_args = NULL;
	current->args[*i] = rm_spaces(current->args[*i]);
	if (current->quotes == 1 && !ft_strchr(current->args[*i], '\"'))
	{
		new_args = ft_split_double(current->args[*i], ' ', '\t');
		new_args = add_double_quotes(new_args);
	}
	if (new_args && new_args[1])
	{
		current->args[*i] = NULL;
		old_args = current->args;
		current->args = ft_strjoin_table(old_args, new_args);
	}
	else if (new_args && new_args[0])
		current->args[*i] = ft_strdup_mem(new_args[0]);
}

void	skip_empty_arg(t_cmds *current, int *i)
{
	while (current->args[*i])
	{
		current->args[*i] = current->args[*i + 1];
		(*i)++;
	}
}

void	loop_norm2(t_cmds *current)
{
	int		i;

	i = 0;
	while (current->args[i])
	{
		if (ft_strcmp(current->args[i], "") == 0)
		{
			skip_empty_arg(current, &i);
			continue ;
		}
		if (current->quotes != 1)
		{
			if (i && current->args
				&& !ft_strcmp(current->args[i - 1], "export"))
			{
				i++;
				if (!current->args[i])
					break ;
			}
		}
		loop_norm(current, &i);
		i++;
	}
}
