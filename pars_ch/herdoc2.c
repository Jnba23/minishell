/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:31:10 by asayad            #+#    #+#             */
/*   Updated: 2024/10/15 12:32:16 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec_w/execution.h"

void	close_hd(t_cmds **cmd_lst)
{
	t_cmds	*tmp;

	tmp = *cmd_lst;
	while (tmp)
	{
		close(tmp->fd[2]);
		tmp = tmp->next;
	}
}

void	set_exec(t_cmds **cmds, int i)
{
	t_cmds	*tmp;

	tmp = *cmds;
	while (tmp)
	{
		if (i == 0)
			tmp->execute = false;
		else
			tmp->execute = true;
		tmp = tmp->next;
	}
}
