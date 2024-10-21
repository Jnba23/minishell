/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caziane <caziane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:43:11 by caziane           #+#    #+#             */
/*   Updated: 2024/10/14 19:26:13 by caziane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec_w/execution.h"

void	free_mem(t_mem **lst)
{
	t_mem	*tmp;
	t_mem	*current;

	if (!lst || !*lst)
		return ;
	current = *lst;
	while (current)
	{
		tmp = current->next;
		if (current->arg)
		{
			free (current->arg);
			current->arg = NULL;
		}
		if (current)
		{
			free (current);
			current = NULL;
		}
		current = tmp;
	}
	*lst = NULL;
}

t_mem	*ft_newone(void *arg)
{
	t_mem	*new_one;

	new_one = (t_mem *)malloc(sizeof(t_mem));
	if (!new_one)
		return (NULL);
	new_one->arg = arg;
	new_one->next = NULL;
	return (new_one);
}

t_mem	*get_last_one(t_mem *arg)
{
	t_mem	*last;

	if (!arg)
		return (NULL);
	last = arg;
	while (last->next)
		last = last->next;
	return (last);
}

void	add_mem_back(t_mem **list, t_mem *new)
{
	t_mem	*last;

	if (!*list)
		*list = new;
	else
	{
		last = get_last_one(*list);
		last->next = new;
	}
}

void	*my_malloc(size_t size, int i)
{
	static t_mem	*alloc;
	t_mem			*current;
	t_mem			*new;
	void			*arg;

	(void)size;
	current = NULL;
	if (i == 1)
	{
		free_mem (&alloc);
		return (NULL);
	}
	arg = malloc(size);
	if (!arg)
		return (NULL);
	new = ft_newone(arg);
	if (!new)
		return (my_malloc(0, 1), exit(1), NULL);
	add_mem_back(&alloc, new);
	return (new->arg);
}
