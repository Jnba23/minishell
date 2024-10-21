/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:07:35 by caziane           #+#    #+#             */
/*   Updated: 2024/10/18 15:58:18 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	print_env_list(t_list **list, int *env_counter)
{
	t_list	*current;
	t_env	*en;

	current = *list;
	if (!current)
	{
		print_custom_errors("minishell:", " env: ",
			"No such file or directory");
		exit_code(1, 1);
		return ;
	}
	if (*env_counter == 2)
		update_env_list_edge_cases(list, "env");
	if (ft_lstsize_mini(*list) == 3 || ft_lstsize_mini(*list) == 4)
		current = current->next;
	while (current)
	{
		en = (t_env *)current->content;
		if (en->value)
			printf("%s=%s\n", en->key, en->value);
		current = current->next;
	}
}

void	print_export_list(t_list *list)
{
	t_list	*current;
	t_env	*en;

	current = list;
	if (ft_lstsize_mini(list) == 4)
		current = current->next;
	while (current)
	{
		en = (t_env *)current->content;
		if (en->value)
			printf("declare -x %s=\"%s\"\n", en->key, en->value);
		else
			printf("declare -x %s\n", en->key);
		current = current->next;
	}
}

void	update_env_list_edge_cases(t_list **env_list, char *type)
{
	t_env	*env_tmp;

	env_tmp = my_malloc(sizeof(t_env), 0);
	if (!env_tmp)
		return (my_malloc(0, 1), exit_code(1, 1), exit(1));
	if (!ft_strcmp(type, "env"))
	{
		if (check_if_var_available(env_list, "_"))
			update_under_score(env_list);
		else
		{
			env_tmp->key = ft_strdup_mem("_");
			env_tmp->value = ft_strdup_mem("/usr/bin/env");
			ft_lstadd_back(env_list, ft_lstnew((void *)env_tmp));
		}
	}
	else if (!ft_strcmp(type, "OLDPWD"))
	{
		env_tmp->key = ft_strdup_mem("OLDPWD");
		env_tmp->value = NULL;
		ft_lstadd_back(env_list, ft_lstnew((void *)env_tmp));
	}
}

void	update_under_score(t_list	**env_list)
{
	t_list	*tmp;
	t_env	*env_tmp;

	tmp = *env_list;
	while (tmp)
	{
		env_tmp = (t_env *)tmp->content;
		if (!ft_strcmp("_", env_tmp->key))
			env_tmp->value = ft_strdup_mem("/usr/bin/env");
		tmp = tmp->next;
	}
}
