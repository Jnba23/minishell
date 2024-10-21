/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:07:28 by asayad            #+#    #+#             */
/*   Updated: 2024/10/18 15:32:25 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	bt_unset(t_cmds *cmd, t_list **env_list)
{
	int		i;
	int		j;

	i = 1;
	j = 1;
	if (table_size(cmd->args) == 1)
		return ;
	while (cmd->args[i])
	{
		j = check_if_valid_var_to_export(cmd->args[i], 2);
		if (!j)
		{
			i++;
			continue ;
		}
		*env_list = updated_env(*env_list, cmd->args[i]);
		i++;
	}
	exit_code(0, 1);
}

t_list	*updated_env(t_list *env_list, char *var)
{
	t_list	*new_env;
	t_list	*tmp;
	t_env	*env_tmp;

	tmp = env_list;
	new_env = NULL;
	while (tmp)
	{
		env_tmp = (t_env *)tmp->content;
		if (ft_strcmp(env_tmp->key, var))
		{
			if (env_tmp->value)
				ft_lstadd_back_mini(&new_env,
					ft_lstnew_mini(ft_strdup_mem(env_tmp->key),
						ft_strdup_mem(env_tmp->value)));
			else
				ft_lstadd_back_mini(&new_env,
					ft_lstnew_mini(ft_strdup_mem(env_tmp->key),
						NULL));
		}
		tmp = tmp->next;
	}
	return (new_env);
}
