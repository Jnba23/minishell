/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 00:18:12 by asayad            #+#    #+#             */
/*   Updated: 2024/10/11 05:24:05 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	bt_exit(t_cmds **cmd_lst, t_cmds *cmd)
{
	long long	num;

	(void)cmd_lst;
	if (cmd->args[1])
	{
		if (ft_isnum(cmd->args[1]))
		{
			if (cmd->args[2])
				return (exit_num_multi_args(cmd));
			else
			{
				num = ft_atoi(cmd->args[1]);
				if (num == -1)
					exit_num_overflow(cmd);
				else
					exit_num_wrap_around(num);
			}
		}
		else
			exit_num_overflow(cmd);
	}
	else
		exit_no_args(cmd);
	return (0);
}

int	ft_isnum(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

long long	ft_atoi(char *str)
{
	int					sign;
	unsigned long long	num;

	num = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str == '0')
		str++;
	while (*str >= 48 && *str <= 57)
	{
		num = (num * 10) + (*str - 48);
		str++;
	}
	if (num > LONG_MAX)
		return (-1);
	return ((long long)num * sign);
}
