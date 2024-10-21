/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 06:12:03 by asayad            #+#    #+#             */
/*   Updated: 2024/10/21 13:21:03 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	export_func(t_list **env_list, t_cmds *lst)
{
	bt_export(lst, env_list);
	if (lst->fd[1] > -1)
		dup2_custom(lst->tmp_fd[1], STDOUT_FILENO, lst);
	if (lst->fd[0] > -1)
		dup2_custom(lst->tmp_fd[0], STDIN_FILENO, lst);
	else if (lst->fd[2] > -1)
		dup2_custom(lst->tmp_fd[0], STDIN_FILENO, lst);
	return (0);
}

int	echo_func(t_cmds *lst)
{
	bt_echo(lst);
	if (lst->fd[1] > -1)
		dup2_custom(lst->tmp_fd[1], STDOUT_FILENO, lst);
	if (lst->fd[0] > -1)
		dup2_custom(lst->tmp_fd[0], STDIN_FILENO, lst);
	else if (lst->fd[2] > -1)
		dup2_custom(lst->tmp_fd[0], STDIN_FILENO, lst);
	return (0);
}

int	pwd_func(t_list **env_list, t_cmds *lst)
{
	bt_pwd(env_list);
	if (lst->fd[1] > -1)
		dup2_custom(lst->tmp_fd[1], STDOUT_FILENO, lst);
	if (lst->fd[0] > -1)
		dup2_custom(lst->tmp_fd[0], STDIN_FILENO, lst);
	else if (lst->fd[2] > -1)
		dup2_custom(lst->tmp_fd[0], STDIN_FILENO, lst);
	return (0);
}

int	cd_func(t_list **env_list, t_cmds *lst)
{
	bt_cd(lst, env_list);
	if (lst->fd[1] > -1)
		dup2_custom(lst->tmp_fd[1], STDOUT_FILENO, lst);
	if (lst->fd[0] > -1)
		dup2_custom(lst->tmp_fd[0], STDIN_FILENO, lst);
	else if (lst->fd[2] > -1)
		dup2_custom(lst->tmp_fd[0], STDIN_FILENO, lst);
	return (0);
}

int	unset_func(t_list **env_list, t_cmds *lst)
{
	bt_unset(lst, env_list);
	if (lst->fd[1] > -1)
		dup2_custom(lst->tmp_fd[1], STDOUT_FILENO, lst);
	if (lst->fd[0] > -1)
		dup2_custom(lst->tmp_fd[0], STDIN_FILENO, lst);
	else if (lst->fd[2] > -1)
		dup2_custom(lst->tmp_fd[0], STDIN_FILENO, lst);
	return (0);
}
