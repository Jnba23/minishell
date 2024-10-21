/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_helper2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caziane <caziane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 16:48:28 by caziane           #+#    #+#             */
/*   Updated: 2024/10/11 04:41:23 by caziane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec_w/execution.h"

int	is_redi(char *str)
{
	return (ft_strcmp(str, ">") == 0 || ft_strcmp(str, ">>") == 0
		|| ft_strcmp(str, "<") == 0 || ft_strcmp(str, "<<") == 0);
}

void	fill_initialisation(t_cmds *token, char **res2)
{
	int	arg_count;
	int	redir_count;

	arg_count = count_args(res2);
	redir_count = count_redir(res2);
	token->args = my_malloc((arg_count + 1) * sizeof(char *), 0);
	token->redirections = my_malloc((redir_count + 1) * sizeof(char *), 0);
	if (!token->args || !token->redirections)
		return ;
}

void	fill_token(t_cmds *token, char **res2)
{
	int	i;
	int	arg_count;
	int	redir_count;

	fill_initialisation(token, res2);
	i = 0;
	arg_count = 0;
	redir_count = 0;
	while (res2[i])
	{
		if (is_redi(res2[i]))
		{
			token->redirections[redir_count++] = ft_strdup_mem(res2[i++]);
			token->redirections[redir_count++] = ft_strdup_mem(res2[i]);
		}
		else
		{
			if (arg_count == 0)
				token->cmd = ft_strdup_mem(res2[i]);
			token->args[arg_count++] = ft_strdup_mem(res2[i]);
		}
		i++;
	}
	token->args[arg_count] = NULL;
	token->redirections[redir_count] = NULL;
}

void	initialiser(t_cmds **new_token)
{
	char	*cmd;
	t_cmds	*tmp;
	char	**args;
	char	**redi;

	tmp = *new_token;
	cmd = NULL;
	args = NULL;
	redi = NULL;
	*new_token = create_token(cmd, args, redi);
}

t_cmds	*tokenize_commands(char **res)
{
	t_cmds	*head;
	t_cmds	*current;
	int		i;
	t_cmds	*new_token;
	char	**res2;

	i = -1;
	head = NULL;
	current = NULL;
	new_token = NULL;
	while (res[++i])
	{
		initialiser(&new_token);
		res2 = split_by_spaces(ft_strtrim(res[i], " \t"));
		fill_token(new_token, res2);
		if (!head)
			head = new_token;
		else
		{
			current->next = new_token;
			new_token->previous = current;
		}
		current = new_token;
	}
	return (head);
}
