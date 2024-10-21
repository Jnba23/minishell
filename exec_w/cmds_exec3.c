/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_exec3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 08:32:46 by asayad            #+#    #+#             */
/*   Updated: 2024/10/13 18:11:56 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	execute_cmd(t_cmd_param *paths, t_cmds *cmd)
{
	if (cmd->cmd && (cmd->cmd[0] == '/' || cmd->cmd[0] == '.'
			|| (ft_strlen(cmd->cmd) > 0
				&& cmd->cmd[ft_strlen(cmd->cmd) - 1] == '/')))
	{
		if (access(cmd->args[0], F_OK))
		{
			print_custom_errors("minishell: ", cmd->args[0], strerror(errno));
			exit_code(127, 1);
			exit(127);
		}
		else if (access(cmd->args[0], X_OK))
		{
			print_custom_errors("minishell: ", cmd->args[0], strerror(errno));
			exit_code(126, 1);
			exit(126);
		}
		else
			abs_p_or_valid_dir(paths, cmd);
	}
	else
	{
		check_if_valid_path(paths, cmd);
		check_cmd_bin(paths, cmd);
	}
}

void	abs_p_or_valid_dir(t_cmd_param *paths, t_cmds *cmd)
{
	struct stat	buff;

	if (!stat(cmd->cmd, &buff))
	{
		if (S_ISDIR(buff.st_mode))
		{
			print_custom_errors("minishell: ", cmd->cmd, strerror(EISDIR));
			return (paths->environ = NULL,
				paths->path_slash = NULL, exit_code(126, 1), exit(126));
		}
		if (buff.st_size == 0)
		{
			return (paths->environ = NULL,
				paths->path_slash = NULL, exit_code(0, 1), exit(0));
		}
	}
	if ((execve(cmd->args[0], cmd->args, paths->environ)) == -1)
	{
		print_custom_errors("minishell: ", cmd->cmd, strerror(errno));
		return (paths->environ = NULL, paths->path_slash = NULL,
			exit_code(127, 1), exit(127));
	}
}

void	check_cmd_bin(t_cmd_param *paths, t_cmds *cmd)
{
	int		i;
	int		size;
	char	*cmd_full_path;

	i = 0;
	size = table_size(paths->path_slash);
	if (!cmd->args[0])
		return (exit_code(0, 1), exit(0));
	while (paths->path_slash[i])
	{
		cmd_full_path = ft_strjoin(paths->path_slash[i], cmd->args[0]);
		if ((execve(cmd_full_path, cmd->args, paths->environ) == -1
				&& i == size - 1))
			return (exit_code(127, 1), print_custom_errors("minishell: ",
					cmd->args[0], "command not found"), exit(127));
		i++;
	}
}

void	term_previous_processes(t_cmds *cmd)
{
	while (cmd)
	{
		if (kill(cmd->p_id, SIGTERM) < 0)
			if (errno == ESRCH)
				return (ft_putstr_fd("process terminated !", 2),
					exit(EXIT_SUCCESS));
		if (kill(cmd->p_id, SIGKILL) < 0)
			if (errno == ESRCH)
				return (ft_putstr_fd("process terminated !", 2),
					exit(EXIT_SUCCESS));
		cmd = cmd->previous;
	}
}

void	check_if_valid_path(t_cmd_param *paths, t_cmds *cmd)
{
	int	flag;
	int	i;

	i = 0;
	if (!paths->path_slash)
	{
		if (cmd->args[0])
			print_custom_errors("minishell: ", cmd->args[0],
				"No such file or directory");
		exit_code(127, 1);
		exit(127);
	}
	flag = find_var_in_table(paths->path_slash, "PATH");
	if (flag == 0)
	{
		if (cmd->args[0])
			print_custom_errors("minishell: ", cmd->args[0],
				"No such file or directory");
		exit_code(127, 1);
		exit(127);
	}
}
