/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caziane <caziane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 21:53:31 by caziane           #+#    #+#             */
/*   Updated: 2024/10/14 15:45:57 by caziane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec_w/execution.h"

void	redirect_loop(t_list **env, t_cmds *list)
{
	t_cmds	*current;
	int		i;

	current = list;
	while (current)
	{
		if (current->redirections)
		{
			i = 0;
			while (current->redirections[i])
			{
				redir_expand2(current, env, &i);
				i++;
			}
		}
		current = current->next;
	}
}

void	rq_helper(t_cmds *current, char **arg, int *i, int *j)
{
	while (current->redirections[*i][*j])
	{
		if (current->redirections[*i][*j] == '\'')
		{
			(*j)++;
			while (current->redirections[*i][*j]
				&& current->redirections[*i][*j] != '\'')
				*arg = ft_strjoin_char(*arg, current->redirections[*i][(*j)++]);
			if (current->redirections[*i][*j] == '\'')
				(*j)++;
		}
		else if (current->redirections[*i][*j] == '\"')
		{
			(*j)++;
			while (current->redirections[*i][*j]
				&& current->redirections[*i][*j] != '\"')
				*arg = ft_strjoin_char(*arg, current->redirections[*i][(*j)++]);
			if (current->redirections[*i][*j] == '\"')
				(*j)++;
		}
		else
			*arg = ft_strjoin_char(*arg, current->redirections[*i][(*j)++]);
	}
}

void	rm_quotes_redi(t_cmds *list)
{
	t_cmds	*current;
	int		i;
	int		j;
	char	*arg;

	current = list;
	while (current)
	{
		if (current->redirections)
		{
			i = 0;
			while (current->redirections[i])
			{
				arg = ft_strnew(0);
				j = 0;
				rq_helper(current, &arg, &i, &j);
				current->redirections[i] = arg;
				i++;
			}
		}
		current = current->next;
	}
}

void	herdoc_file(t_herdoc *h, char **her, t_list **env, int *fd)
{
	char	*her2;

	if (!ft_strchr(h->deli, '\'') && !ft_strchr(h->deli, '\"'))
	{
		her2 = expand_herdoc(env, *her);
		ft_putendl_fd(her2, fd[2]);
	}
	else
		ft_putendl_fd(*her, fd[2]);
}
