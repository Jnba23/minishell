/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_helper1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caziane <caziane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 20:41:02 by caziane           #+#    #+#             */
/*   Updated: 2024/10/14 22:07:03 by caziane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec_w/execution.h"

char	**split_norm(char *line, char **result)
{
	char			*start;
	int				i;
	int				count;
	enum e_state	state;

	state = GENERAL;
	start = line;
	count = 0;
	i = 0;
	while (line && line[i])
	{
		state_checker(line[i], &state);
		if ((line[i] == ' ' || line[i] == '\t') && state == GENERAL)
		{
			if (start < line + i && line[i - 1] != ' ' && line[i - 1] != '\t')
			{
				result[count++] = ft_strndup(start, line + i - start);
				start = line + i + 1;
			}
		}
		i++;
	}
	if (i > 0 && line[i - 1] != ' ' && line[i - 1] != '\t')
		result[count++] = ft_strdup_mem(start);
	return (result[count] = NULL, result);
}

char	**split_by_spaces(char *line)
{
	char			**result;
	int				count;

	count = split_spaces_helper(line);
	result = (char **)my_malloc(sizeof(char *) * (count + 1), 0);
	if (!result)
		return (NULL);
	return (split_norm(line, result));
}

t_cmds	*create_token(char *cmd, char **args, char **redirections)
{
	t_cmds	*new_token;

	new_token = (t_cmds *)my_malloc(sizeof(t_cmds), 0);
	if (!new_token)
		return (NULL);
	new_token->cmd = cmd;
	new_token->exit_code = -1;
	new_token->args = args;
	new_token->redirections = redirections;
	new_token->next = NULL;
	new_token->previous = NULL;
	new_token->here_doc = false;
	new_token->execute = true;
	new_token->tmp_fd[0] = -1;
	new_token->tmp_fd[1] = -1;
	new_token->fd[0] = -1;
	new_token->fd[1] = -1;
	new_token->fd[2] = -1;
	return (new_token);
}

int	count_redir(char **res2)
{
	int	i;
	int	redir_count;

	i = 0;
	redir_count = 0;
	while (res2[i])
	{
		if (ft_strcmp(res2[i], ">") == 0 || ft_strcmp(res2[i], ">>") == 0
			|| ft_strcmp(res2[i], "<") == 0 || ft_strcmp(res2[i], "<<") == 0)
			redir_count += 2;
		i++;
	}
	return (redir_count);
}

int	count_args(char **res2)
{
	int	i;
	int	arg_count;

	i = 0;
	arg_count = 0;
	while (res2[i])
	{
		if (ft_strcmp(res2[i], ">") && ft_strcmp(res2[i], ">>")
			&& ft_strcmp(res2[i], "<") && ft_strcmp(res2[i], "<<"))
			arg_count++;
		i++;
	}
	return (arg_count);
}
