/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caziane <caziane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:07:23 by asayad            #+#    #+#             */
/*   Updated: 2024/10/11 04:39:08 by caziane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	command_execution(t_cmds **lst, t_list **env_list)
{
	t_cmds		*cmd_lst;
	t_cmd_param	paths;

	cmd_lst = *lst;
	paths.environ = NULL;
	paths.path_slash = NULL;
	while (cmd_lst)
	{
		if (single_bt_cmd(lst, cmd_lst, env_list))
			return ;
		pre_execution_mini(&paths, env_list);
		fd_init(cmd_lst);
		if (cmd_lst->next)
			open_pipe(cmd_lst);
		if (check_files(cmd_lst)
			|| family_processes(&paths, lst, cmd_lst, env_list) < 0)
		{
			close_in_out(cmd_lst);
			cmd_lst = cmd_lst->next;
			continue ;
		}
		cmd_lst = cmd_lst->next;
	}
	close_fds_wait_processes(lst);
}

int	check_files(t_cmds *cmd)
{
	int	i;

	i = 0;
	while (cmd->redirections[i])
	{
		if (!is_redirection(cmd->redirections[i]))
		{
			if (check_redirections(cmd->redirections[i + 1],
					cmd->redirections[i], cmd))
				return (1);
		}
		else if (!ft_strcmp(cmd->redirections[i], "<<<"))
		{
			print_custom_errors("minishell: ", cmd->redirections[i + 1],
				"ambiguous redirect");
			exit_code(1, 1);
			return (1);
		}
		i += 2;
	}
	return (0);
}

int	is_redirection(char *s)
{
	if (!ft_strcmp("<", s) || !ft_strcmp(">", s) || !ft_strcmp(">>", s))
		return (0);
	return (1);
}

int	check_redirections(char *file, char *redirection, t_cmds *cmd)
{
	static int	counter;

	if (!ft_strcmp(redirection, ">") || !ft_strcmp(redirection, ">>"))
	{
		if (ft_outfile(cmd, file, redirection, counter))
			return (1);
	}
	if (!ft_strcmp(redirection, "<"))
	{
		if (counter)
			close_open_fds_file_check(cmd, counter, 0);
		cmd->fd[0] = open(file, O_RDONLY);
		if (cmd->fd[0] < 0)
		{
			print_custom_errors("minishell: ", file, strerror(errno));
			exit_code(1, 1);
			return (1);
		}
	}
	counter++;
	return (0);
}

int	ft_outfile(t_cmds *cmd, char *file, char *redirection, int counter)
{
	if (counter)
		close_open_fds_file_check(cmd, counter, 1);
	if (!ft_strcmp(redirection, ">"))
		cmd->fd[1] = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else
		cmd->fd[1] = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (cmd->fd[1] < 0)
	{
		print_custom_errors("minishell: ", file, strerror(errno));
		exit_code(1, 1);
		return (1);
	}
	return (0);
}
