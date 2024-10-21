/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 07:49:11 by asayad            #+#    #+#             */
/*   Updated: 2024/10/21 13:22:21 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	builtins(t_cmds **cmd_lst, t_cmds *lst, t_list **env_list)
{
	static int	env_counter;
	int			out_fd;

	(void) cmd_lst;
	out_fd = 0;
	if (is_builtin(lst->args[0]))
		out_fd = builtins_redirections(lst);
	if (out_fd == -1)
		return (0);
	if ((!ft_strcmp(lst->cmd, "env")))
		return (env_func(env_list, lst, &env_counter));
	if (!ft_strcmp("export", lst->args[0]))
		return (export_func(env_list, lst));
	if (!ft_strcmp("echo", lst->cmd))
		return (echo_func(lst));
	if (!ft_strcmp("pwd", lst->cmd))
		return (pwd_func(env_list, lst));
	if (!ft_strcmp("cd", lst->cmd))
		return (cd_func(env_list, lst));
	if (!ft_strcmp("unset", lst->cmd))
		return (unset_func(env_list, lst));
	if (!ft_strcmp("exit", lst->cmd))
		return (bt_exit(cmd_lst, lst));
	return (1);
}

int	builtins_redirections(t_cmds *cmd)
{
	cmd->tmp_fd[1] = dup(STDOUT_FILENO);
	cmd->tmp_fd[0] = dup(STDIN_FILENO);
	if (check_files(cmd))
	{
		close_in_out(cmd);
		dup2_custom(cmd->tmp_fd[1], STDOUT_FILENO, cmd);
		dup2_custom(cmd->tmp_fd[0], STDIN_FILENO, cmd);
		return (close(cmd->tmp_fd[0]), close(cmd->tmp_fd[1]), -1);
	}
	if (cmd->redirections && *(cmd->redirections))
	{
		if (cmd->fd[1] > -1)
			dup2_custom(cmd->fd[1], STDOUT_FILENO, cmd);
		if (cmd->fd[0] > 0)
			dup2_custom(cmd->fd[0], STDIN_FILENO, cmd);
		else if (cmd->fd[2] > 0)
			dup2_custom(cmd->fd[2], STDIN_FILENO, cmd);
	}
	return (0);
}

int	is_builtin(char *cmd)
{
	if (!ft_strcmp("env", cmd) || !ft_strcmp("export", cmd)
		|| !ft_strcmp("echo", cmd))
		return (1);
	if (!ft_strcmp("pwd", cmd) || !ft_strcmp("cd", cmd)
		|| !ft_strcmp("unset", cmd))
		return (1);
	return (0);
}

int	env_func(t_list **env_list, t_cmds *lst, int *env_counter)
{
	if (table_size(lst->args) > 1)
	{
		print_custom_errors("env : ", lst->args[1],
			"No such file or directory");
		return (0);
	}
	*env_counter += 1;
	print_env_list(env_list, env_counter);
	if (lst->fd[1] > -1)
		dup2_custom(lst->tmp_fd[1], STDOUT_FILENO, lst);
	if (lst->fd[0] > -1)
		dup2_custom(lst->tmp_fd[0], STDIN_FILENO, lst);
	else if (lst->fd[2] > -1)
		dup2_custom(lst->tmp_fd[0], STDIN_FILENO, lst);
	return (0);
}
