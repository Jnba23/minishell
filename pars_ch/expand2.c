/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caziane <caziane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 20:33:18 by caziane           #+#    #+#             */
/*   Updated: 2024/10/08 16:13:36 by caziane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec_w/execution.h"

void	redir_expand1(t_cmds *current, char **new, int *i)
{
	*new = ft_strjoin_mem(*new, "<<<");
	current->redirections[*i - 1] = *new;
}

char	*add_double(char *a)
{
	int	i;

	i = 0;
	if (!a)
		return (NULL);
	if (ft_strchr(a, '\'') && ft_strchr(a, '\"'))
		return (a);
	if (ft_strchr(a, '\'') || ft_strchr(a, '\"'))
	{
		a = ft_strjoin_mem(ft_strdup_mem("\""), a);
		a = ft_strjoin_mem(a, ft_strdup_mem("\""));
	}
	return (a);
}

void	redi_sexpand(t_cmds *current, t_list **env, int *i)
{
	char	*arg;
	char	*expanded;
	char	*test;
	char	*t;
	char	*new;

	new = ft_strnew(0);
	t = ft_strdup_mem(current->redirections[*i]);
	arg = current->redirections[*i];
	arg = set_expand(arg);
	expanded = expand(env, arg);
	expanded = set_expand(expanded);
	test = ft_strtrim(expanded, " \t");
	if (ft_strchr(arg, '$') && !ft_strchr(arg, '\"')
		&& (ft_strchr(test, ' ') || ft_strchr(test, '\t')
			|| !ft_strcmp(test, "")))
	{
		current->redirections[*i] = t;
		redir_expand1(current, &new, i);
	}
	else
	{
		expanded = add_double(expanded);
		current->redirections[*i] = expanded;
	}
}

void	redi_dexpand(t_cmds *current, t_list **env, int *i)
{
	char	*arg;
	char	*expanded;
	char	*test;
	char	*new;

	new = ft_strnew(0);
	arg = current->redirections[*i];
	expanded = expand(env, arg);
	test = ft_strtrim(expanded, " \t");
	if (ft_strchr(arg, '$') && !ft_strchr(arg, '\"')
		&& (ft_strchr(test, ' ') || ft_strchr(test, '\t')
			|| !ft_strcmp(test, "")))
		redir_expand1(current, &new, i);
	else
	{
		expanded = add_double(expanded);
		current->redirections[*i] = expanded;
	}
}

void	redir_expand2(t_cmds *current, t_list **env, int *i)
{
	if (!ft_strcmp(current->redirections[*i], ">")
		|| !ft_strcmp(current->redirections[*i], "<")
		|| !ft_strcmp(current->redirections[*i], ">>"))
	{
		(*i)++;
		if (ft_strchr(current->redirections[*i], '\''))
			redi_sexpand(current, env, i);
		else
			redi_dexpand(current, env, i);
	}
}
