/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caziane <caziane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 07:59:37 by asayad            #+#    #+#             */
/*   Updated: 2024/10/10 18:12:44 by caziane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	bt_export(t_cmds *cmd_lst, t_list **env_list)
{
	int	i;
	int	j;

	j = 1;
	if (!ft_strcmp("export", cmd_lst->args[0]))
	{
		if (!cmd_lst->args[j])
			export_only(env_list);
		else
		{
			while (cmd_lst->args[j])
			{
				i = check_if_valid_var_to_export(cmd_lst->args[j], 1);
				if (!i)
				{
					exit_code(1, 1);
					j++;
					continue ;
				}
				else
					update_env_list(cmd_lst->args[j], env_list);
				j++;
			}
		}
	}
}

int	check_if_valid_var_to_export(char *var, int i)
{
	if (first_char_check(var) || check_rest_of_var_name(var))
	{
		if (i == 1)
			ft_putstr_fd("minishell: export: `", 2);
		else if (i == 2)
			ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(var, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (0);
	}
	return (1);
}

int	first_char_check(char *var)
{
	if (var[0] != '_' && !ft_isalpha(var[0]))
		return (1);
	return (0);
}

int	check_rest_of_var_name(char *var)
{
	int		i;
	int		j;

	i = 1;
	j = ft_strchr_helper(var, '=');
	if (j == -1)
		j = ft_strlen(var);
	while (i < j)
	{
		if (!ft_isalnum(var[i]))
		{
			if (i == j - 1 && var[i] == '+' && var[j] == '=')
			{
				i++;
				continue ;
			}
			else
				return (1);
		}
		i++;
	}
	return (0);
}

void	update_var_value(char *var_only, char *var, t_list **env_list)
{
	t_list	*tmp;
	t_env	*env_tmp;

	tmp = *env_list;
	while (tmp)
	{
		env_tmp = (t_env *)tmp->content;
		if (!ft_strcmp(env_tmp->key, var_only))
			env_tmp->value = ft_strdup_mem(var);
		tmp = tmp->next;
	}
}
