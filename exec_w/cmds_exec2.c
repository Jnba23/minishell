/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_exec2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 11:51:18 by asayad            #+#    #+#             */
/*   Updated: 2024/10/18 15:30:50 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	family_processes(t_cmd_param *paths, t_cmds **cmd_lst, t_cmds *cmd,
	t_list **env_list)
{
	signal(SIGQUIT, sig_quit);
	signal(SIGINT, sig_quit);
	cmd->p_id = fork();
	if (cmd->p_id < 0)
		return (my_malloc(0, 1),
			term_previous_processes(cmd), perror("Fork "), -1);
	if (cmd->p_id == 0)
		child_process(paths, cmd_lst, cmd, env_list);
	close(cmd->pipe_fd[1]);
	if (cmd->previous)
		close(cmd->previous->pipe_fd[0]);
	return (0);
}

void	child_process(t_cmd_param *paths, t_cmds **cmd_lst, t_cmds *cmd,
	t_list **env_list)
{
	(void)env_list;
	if (!cmd->previous)
		first_cmd(cmd);
	else if (!cmd->next && cmd->previous)
		last_cmd(cmd);
	else if (cmd->next && cmd->previous)
		middle_cmds(cmd);
	if (!builtins(cmd_lst, cmd, env_list))
		exit(EXIT_SUCCESS);
	execute_cmd(paths, cmd);
}

void	first_cmd(t_cmds *cmd)
{
	close(cmd->pipe_fd[0]);
	if (!cmd->here_doc)
	{
		if (cmd->fd[0] >= 0)
			dup2_custom(cmd->fd[0], STDIN_FILENO, cmd);
	}
	else
		dup2_custom(cmd->fd[2], STDIN_FILENO, cmd);
	if (cmd->fd[1] > 0)
	{
		dup2_custom(cmd->fd[1], STDOUT_FILENO, cmd);
		close(cmd->pipe_fd[1]);
	}
	else if (cmd->pipe_fd[1] > -1)
		dup2_custom(cmd->pipe_fd[1], STDOUT_FILENO, cmd);
}

void	middle_cmds(t_cmds *cmd)
{
	close(cmd->pipe_fd[0]);
	if (!cmd->here_doc)
	{
		if (cmd->fd[0] >= 0)
		{
			close(cmd->previous->pipe_fd[0]);
			dup2_custom(cmd->fd[0], STDIN_FILENO, cmd);
		}
		else
			dup2_custom(cmd->previous->pipe_fd[0], STDIN_FILENO, cmd);
	}
	else
	{
		dup2_custom(cmd->fd[2], STDIN_FILENO, cmd);
		close(cmd->previous->pipe_fd[0]);
	}
	if (cmd->fd[1] > 0)
	{
		dup2_custom(cmd->fd[1], STDOUT_FILENO, cmd);
		close(cmd->pipe_fd[1]);
	}
	else
		dup2_custom(cmd->pipe_fd[1], STDOUT_FILENO, cmd);
}

void	last_cmd(t_cmds *cmd)
{
	if (!cmd->here_doc)
	{
		if (cmd->fd[0] >= 0)
		{
			dup2_custom(cmd->fd[0], STDIN_FILENO, cmd);
			close(cmd->previous->pipe_fd[0]);
		}
		else
			dup2_custom(cmd->previous->pipe_fd[0], STDIN_FILENO, cmd);
	}
	else
	{
		dup2_custom(cmd->fd[2], STDIN_FILENO, cmd);
		close(cmd->previous->pipe_fd[0]);
	}
	if (cmd->fd[1] > 0)
		dup2_custom(cmd->fd[1], STDOUT_FILENO, cmd);
}
