/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_export3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caziane <caziane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 06:00:20 by asayad            #+#    #+#             */
/*   Updated: 2024/10/11 02:35:40 by caziane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	join_var_value(char *var_only, char *var, t_list **env_list)
{
	t_list	*tmp;
	t_env	*env_tmp;

	tmp = *env_list;
	while (tmp)
	{
		env_tmp = (t_env *)tmp->content;
		if (!ft_strcmp(env_tmp->key, var_only))
		{
			if (!env_tmp->value)
				env_tmp->value = ft_strdup_mem("");
			env_tmp->value = ft_strjoin_mem(env_tmp->value, ft_strdup_mem(var));
		}
		tmp = tmp->next;
	}
}

void	add_var_to_env_list(char *var_only, char *var, t_list **env_list)
{
	t_env	*tmp_env;
	int		i;

	tmp_env = my_malloc(sizeof(t_env), 0);
	if (!tmp_env)
		return ;
	i = ft_strchr_helper(var, '=');
	if (i >= 0)
	{
		tmp_env->key = ft_strdup_mem(var_only);
		tmp_env->value = ft_strdup_mem(var + i + 1);
	}
	else
	{
		tmp_env->key = ft_strdup(var_only);
		tmp_env->value = 0;
	}
	ft_lstadd_back(env_list, ft_lstnew((void *)tmp_env));
}

char	*find_var(char *var)
{
	int	i;

	i = ft_strchr_helper(var, '=');
	if (i > -1)
	{
		if (var[i - 1] != '+')
			return (ft_strdup_helper(var, i - 1));
		else
			return (ft_strdup_helper(var, i - 2));
	}
	else
		return (ft_strdup_mem(var));
}
