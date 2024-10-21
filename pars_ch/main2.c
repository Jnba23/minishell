/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 03:25:32 by caziane           #+#    #+#             */
/*   Updated: 2024/10/18 10:52:50 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec_w/execution.h"

char	*rm_spaces(char *line)
{
	int				i;
	char			*new_line;
	enum e_state	state;

	i = 0;
	state = GENERAL;
	if (!line)
		return (NULL);
	new_line = ft_strnew(0);
	line = ft_strtrim(line, " \t");
	while (line && line[i])
	{
		state_checker(line[i], &state);
		if ((line[i] == ' ' || line[i] == '\t') && state == GENERAL)
		{
			new_line = ft_strjoin_char(new_line, ' ');
			while (line && line[i] && (line[i] == ' ' || line[i] == '\t'))
				i++;
			state_checker(line[i], &state);
		}
		new_line = ft_strjoin_char(new_line, line[i]);
		i++;
	}
	return (new_line);
}

void	parssing(char **cmd, t_list **list, t_cmds **token)
{
	char	**res;
	t_cmds	*tmp;

	res = NULL;
	res = split_by_pipes(*cmd);
	*token = tokenize_commands(res);
	cmds_loop(list, token);
	tmp = *token;
	while (tmp)
	{
		if (!tmp->next && tmp->previous)
		{
			if (!ft_strcmp(tmp->cmd, "echo") && !ft_strcmp(tmp->args[1], "$?"))
				exit_code(0, 1);
		}
		tmp = tmp->next;
	}
	args_loop(list, token);
	args_loop2(token);
	redirect_loop(list, *token);
	herdoc_open(token, list);
	rm_quotes_cmd(*token);
	rm_quotes(*token);
	rm_quotes_redi(*token);
}

void	ctrld(char *line)
{
	if (!line)
	{
		my_malloc(0, 1);
		printf("exit\n");
		exit(exit_code(0, 0));
	}
}

void	minishell(t_cmds **token, t_list **list, char **cmd, int *exitt)
{
	parssing(cmd, list, token);
	if ((*token)->execute)
		command_execution(token, list);
	set_exec(token, 1);
	*exitt = exit_code(*exitt, 0);
}

int	syntax_error(char *cmd, char *line)
{
	if (!cmd || !first_end_line(cmd) || !quotes(cmd) || !basic_errors(cmd))
	{
		exit_code(258, 1);
		free(line);
		line = NULL;
		return (0);
	}
	return (1);
}
