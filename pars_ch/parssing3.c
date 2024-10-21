/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:58:03 by caziane           #+#    #+#             */
/*   Updated: 2024/10/16 20:09:54 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec_w/execution.h"

t_list	*ft_lstnew_env(void *content)
{
	t_list	*newone;

	newone = (t_list *)my_malloc(sizeof(t_list), 0);
	if (!newone)
		return (NULL);
	newone -> content = content;
	newone -> next = NULL;
	return (newone);
}

void	create_min_env(t_list **head)
{
	int		i;
	t_list	*h;
	t_env	*env_var;

	i = -1;
	while (++i < 4)
		ft_lstadd_back(head, ft_lstnew_env(NULL));
	h = *head;
	i = 0;
	while (h)
	{
		env_var = (t_env *) my_malloc (sizeof(t_env), 0);
		if (!env_var)
			return ;
		h->content = env_var;
		fill_env_vars(i, env_var);
		i++;
		h = h->next;
	}
}

void	fill_env_vars(int i, t_env *env_var)
{
	char	*s;

	s = getcwd(NULL, 0);
	if (i == 0)
	{
		env_var->key = ft_strdup_env("PATH");
		env_var->value
			= ft_strdup_env("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	}
	else if (i == 1)
	{
		env_var->key = ft_strdup_env("PWD");
		env_var->value = ft_strdup_mem(s);
	}
	else if (i == 2)
	{
		env_var->key = ft_strdup_env("SHLVL");
		env_var->value = ft_strdup_env("1");
	}
	else if (i == 3)
	{
		env_var->key = ft_strdup_env("_");
		env_var->value = ft_strdup_env("/usr/bin/env");
	}
	free(s);
}
