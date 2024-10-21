/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caziane <caziane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 07:59:37 by asayad            #+#    #+#             */
/*   Updated: 2024/10/10 20:00:43 by caziane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	bt_echo(t_cmds *lst)
{
	int		i;
	int		flag;
	int		args_nb;

	flag = 0;
	i = 1;
	args_nb = table_size(lst->args);
	if (args_nb == 1)
	{
		ft_putstr_fd("\n", 1);
		exit_code(0, 1);
		return ;
	}
	i += check_echo_args(lst->args);
	if (i == 1)
		flag = 1;
	print_args(lst->args, i);
	if (flag)
		ft_putstr_fd("\n", 1);
	exit_code(0, 1);
}

int	check_echo_args(char **args)
{
	int	i;

	i = 1;
	while (!print_nl(args[i]))
		i++;
	return (i - 1);
}

int	print_nl(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (!str)
		return (1);
	i = dash_counter(str);
	if (str[0] == '-' && i == 1)
	{
		if (n_counter(str + i) == 1)
			flag = 1;
	}
	else
		return (1);
	if (flag != 0)
		return (0);
	return (1);
}

int	dash_counter(char *str)
{
	int	counter;

	counter = 0;
	while (str[counter] == '-')
		counter++;
	if (counter != 1)
		return (0);
	return (1);
}

int	n_counter(char *str)
{
	if (!str || !*str)
		return (0);
	while (*str)
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	return (1);
}
