/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_exec_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:22:14 by asayad            #+#    #+#             */
/*   Updated: 2024/10/15 10:07:13 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	open_pipe(t_cmds *cmd)
{
	if (cmd->next)
	{
		if (pipe(cmd->pipe_fd) < 0)
			perror(strerror(errno));
	}
}

void	fd_init(t_cmds *cmd)
{
	cmd->fd[0] = -1;
	cmd->fd[1] = -1;
	cmd->pipe_fd[0] = -1;
	cmd->pipe_fd[1] = -1;
}

void	close_open_fds_file_check(t_cmds *cmd, int counter, int in_or_out)
{
	static int	tmp;

	if (tmp != counter)
	{
		if (in_or_out)
			close(cmd->fd[1]);
		else
			close(cmd->fd[0]);
	}
	tmp = counter;
}

void	dup2_custom(int old_fd, int new_fd, t_cmds *cmd)
{
	if (dup2(old_fd, new_fd) < 0)
	{
		ft_putstr_fd("dup2 :", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		close(cmd->pipe_fd[0]);
		close(cmd->pipe_fd[1]);
		close(cmd->fd[0]);
		close(cmd->fd[1]);
		close(cmd->fd[2]);
		exit(EXIT_FAILURE);
	}
	close(old_fd);
}

void	close_fds(t_cmds **cmd_lst)
{
	t_cmds	*cmd;

	cmd = *cmd_lst;
	while (cmd)
	{
		close(cmd->pipe_fd[0]);
		close(cmd->pipe_fd[1]);
		close(cmd->fd[0]);
		close(cmd->fd[1]);
		close(cmd->fd[2]);
		cmd = cmd->next;
	}
}
