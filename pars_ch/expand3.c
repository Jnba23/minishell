/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caziane <caziane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 21:45:19 by caziane           #+#    #+#             */
/*   Updated: 2024/10/14 18:57:55 by caziane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec_w/execution.h"

void	arg_expand1(t_cmds **curr, t_list **env, int *i)
{
	char	*arg;
	t_cmds	*current;
	char	*expanded;

	current = *curr;
	arg = current->args[*i];
	arg = set_expand(arg);
	expanded = expand(env, arg);
	expanded = set_expand(expanded);
	current->args[*i] = expanded;
	if (ft_strchr(arg, '$'))
		current->quotes = 1;
}

char	**add_double_quotes(char **a)
{
	int	i;

	i = 0;
	if (!a || !*a)
		return (NULL);
	while (a[i])
	{
		if (ft_strchr(a[i], '\'') && ft_strchr(a[i], '\"'))
			i++;
		else if (a[i][0] == '\'' && a[i][ft_strlen(*a) - 1] == '\'')
			i++;
		else if (ft_strchr(a[i], '\'') || ft_strchr(a[i], '\"'))
		{
			a[i] = ft_strjoin_mem(ft_strdup_mem("\""), a[i]);
			a[i] = ft_strjoin_mem(a[i], ft_strdup_mem("\""));
			i++;
		}
		else
			i++;
	}
	return (a);
}

void	arg_expand2(t_cmds **curr, t_list **env, int *i)
{
	char	*arg;
	t_cmds	*current;
	char	*expanded;

	current = *curr;
	arg = current->args[*i];
	expanded = expand(env, arg);
	current->args[*i] = expanded;
	if (ft_strchr(arg, '$'))
		current->quotes = 1;
}

void	cmd_expand1(t_cmds *current, t_list **env)
{
	char	*arg;
	char	*expanded;

	arg = current->cmd;
	arg = set_expand(arg);
	expanded = expand(env, arg);
	expanded = set_expand(expanded);
	current->cmd = expanded;
}

void	cmd_expand2(t_cmds *current, t_list **env)
{
	char	*arg;
	char	*expanded;

	arg = current->cmd;
	expanded = expand(env, arg);
	current->cmd = expanded;
}
