/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_echo2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 05:43:54 by asayad            #+#    #+#             */
/*   Updated: 2024/10/08 05:44:35 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	print_args(char **args, int i)
{
	int	args_nb;

	args_nb = table_size(args);
	while (i < args_nb)
	{
		if (i == args_nb - 1)
			ft_putstr_fd(args[i++], 1);
		else
		{
			ft_putstr_fd(args[i++], 1);
			ft_putstr_fd(" ", 1);
		}
	}
}
