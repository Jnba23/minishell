/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:40:49 by asayad            #+#    #+#             */
/*   Updated: 2024/10/18 16:00:31 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	bt_cd(t_cmds *cmd, t_list **env_list)
{
	int		flag;
	char	*wd;
	char	p[PATH_MAX];

	flag = 0;
	wd = ft_strdup_mem(get_wd(env_list));
	if (!cmd->args[1] || !ft_strcmp(cmd->args[1], "-")
		|| !ft_strcmp(cmd->args[1], "~"))
		return (cd_special_cases(cmd->args[1], env_list, wd));
	else
	{
		if (!getcwd(p, sizeof(p)))
		{
			flag = 1;
			if (env_list && *env_list && !ft_strcmp(cmd->args[1], ".."))
				update_path_upon_failure(env_list, wd);
		}
		if (!chdir(cmd->args[1]) && flag == 0)
		{
			if (env_list && *env_list)
				update_path_upon_success(env_list, wd);
		}
		else
			print_error_set_ec(cmd);
	}
}

void	update_path_upon_failure(t_list **env_list, char *wd)
{
	t_env	*env_tmp;
	t_list	*tmp;

	if (!*env_list)
		return ;
	if (!check_if_var_available(env_list, "OLDPWD"))
		update_env_list_edge_cases(env_list, "OLDPWD");
	tmp = *env_list;
	while (tmp)
	{
		env_tmp = (t_env *)tmp->content;
		if (!ft_strcmp(env_tmp->key, "OLDPWD"))
			env_tmp->value = wd;
		if (!ft_strcmp(env_tmp->key, "PWD"))
			env_tmp->value = ft_strjoin_mem(env_tmp->value, "/..");
		tmp = tmp->next;
	}
}

char	*get_wd(t_list **env_list)
{
	t_list	*tmp;
	t_env	*env_tmp;

	tmp = *env_list;
	while (tmp)
	{
		env_tmp = (t_env *)tmp->content;
		if (!ft_strcmp("PWD", env_tmp->key))
			return (env_tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	update_path_upon_success(t_list **env_list, char *wd)
{
	t_env	*env_tmp;
	t_list	*tmp;
	char	*s;

	if (!*env_list)
		return ;
	tmp = *env_list;
	if (!check_if_var_available(env_list, "OLDPWD"))
		update_env_list_edge_cases(env_list, "OLDPWD");
	while (tmp)
	{
		env_tmp = (t_env *)tmp->content;
		if (!ft_strcmp(env_tmp->key, "OLDPWD"))
			env_tmp->value = wd;
		if (!ft_strcmp(env_tmp->key, "PWD"))
		{
			s = getcwd(NULL, 0);
			env_tmp->value = ft_strdup_mem(s);
			if (s)
				free(s);
		}
		tmp = tmp->next;
	}
}

int	check_if_var_available(t_list **env_list, char *var)
{
	t_env	*env_tmp;
	t_list	*tmp;

	tmp = *env_list;
	while (tmp)
	{
		env_tmp = (t_env *)tmp->content;
		if (!ft_strcmp(env_tmp->key, var))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
