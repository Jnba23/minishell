/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_exit2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:56:21 by asayad            #+#    #+#             */
/*   Updated: 2024/10/12 12:35:33 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	exit_code(int value, int i)
{
	static int	e_c;

	if (i == 1)
		e_c = value;
	return (e_c);
}

int	exit_num_multi_args(t_cmds *cmd)
{
	if (!cmd->next)
		ft_putendl_fd_mini("exit", 2);
	print_custom_errors("minishell: ", "exit", "too many arguments");
	exit_code(0, 1);
	return (0);
}

void	exit_num_overflow(t_cmds *cmd)
{
	if (!cmd->next)
		ft_putendl_fd_mini("exit", 2);
	print_custom_errors("minishell: exit: ", cmd->args[1],
		"numeric argument required");
	exit_code(255, 1);
	exit(exit_code(255, 0));
}

void	exit_num_wrap_around(long long num)
{
	if (num < 0)
	{
		num *= -1;
		exit_code(256 - (num % 256), 1);
	}
	else
		exit_code(num % 256, 1);
	exit(exit_code(0, 0));
}

void	exit_no_args(t_cmds *cmd)
{
	if (!cmd->next)
		ft_putendl_fd_mini("exit", 2);
	exit_code(0, 1);
	exit(exit_code(0, 0));
}
