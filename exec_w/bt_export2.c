/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caziane <caziane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 05:57:32 by asayad            #+#    #+#             */
/*   Updated: 2024/10/09 19:51:58 by caziane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	swap_content(t_list	*fst_nd, t_list *snd_nd)
{
	t_env	*tmp;

	tmp = (t_env *)fst_nd->content;
	fst_nd->content = snd_nd->content;
	snd_nd->content = tmp;
}

void	sorted_env(t_list *env_list)
{
	t_list	*tmp;
	t_list	*l_ptr;
	int		swapped;

	l_ptr = NULL;
	swapped = 1;
	if (!env_list)
		return ;
	while (swapped)
	{
		tmp = env_list;
		swapped = 0;
		while (tmp->next != l_ptr)
		{
			if (ft_strcmp(((t_env *)(tmp->content))->key,
				((t_env *)(tmp->next->content))->key) > 0)
			{
				swap_content(tmp, tmp->next);
				swapped = 1;
			}
			tmp = tmp->next;
		}
		l_ptr = tmp->next;
	}
}

int	search_for_var_in_env(char *var, t_list **env_list)
{
	t_list	*tmp;
	t_env	*tmp_env;

	tmp = *env_list;
	while (tmp)
	{
		tmp_env = (t_env *)tmp->content;
		if (!ft_strcmp(tmp_env->key, var))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	update_env_list(char *var, t_list **env_lst)
{
	int		i;
	char	*var_only;

	var_only = find_var(var);
	i = ft_strchr_helper(var, '=');
	if (search_for_var_in_env(var_only, env_lst))
	{
		if (i < 0)
			return ;
		else
		{
			if (var[i - 1] != '+')
				update_var_value(var_only, var + i + 1, env_lst);
			else
				join_var_value(var_only, var + i + 1, env_lst);
		}
	}
	else
	{
		add_var_to_env_list(var_only, var, env_lst);
	}
}

void	export_only(t_list **env_list)
{
	sorted_env(*env_list);
	print_export_list(*env_list);
}
