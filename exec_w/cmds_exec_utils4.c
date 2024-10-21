/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_exec_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 00:43:55 by caziane           #+#    #+#             */
/*   Updated: 2024/10/18 14:34:12 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	cd_errors(char *arg)
{
	if (!ft_strcmp("-", arg))
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
	if (!arg)
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
}

int	single_bt_cmd(t_cmds **lst, t_cmds *cmd_lst, t_list **env_list)
{
	if (!cmd_lst->next && !cmd_lst->previous
		&& !builtins(lst, cmd_lst, env_list))
	{
		close(cmd_lst->tmp_fd[0]);
		close(cmd_lst->tmp_fd[1]);
		return (1);
	}
	return (0);
}
