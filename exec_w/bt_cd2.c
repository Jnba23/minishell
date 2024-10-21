/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 05:30:49 by asayad            #+#    #+#             */
/*   Updated: 2024/10/18 15:53:12 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	cd_special_cases(char *arg, t_list **env_list, char *wd)
{
	t_list	*list;
	t_env	*tmp;

	list = *env_list;
	while (list)
	{
		tmp = (t_env *)list->content;
		if ((!arg && !ft_strcmp(tmp->key, "HOME"))
			|| (!ft_strcmp("-", arg) && !ft_strcmp(tmp->key, "OLDPWD")))
		{
			if (chdir(tmp->value))
			{
				print_custom_errors("cd: ", tmp->value, strerror(errno));
				exit_code(1, 1);
			}
			else
				return (update_path_upon_success(env_list, wd));
		}
		list = list->next;
	}
	if (!ft_strcmp(arg, "~"))
		chdir_home(env_list);
	cd_errors(arg);
	exit_code(1, 1);
}

void	chdir_home(t_list **env_list)
{
	t_list	*tmp;
	t_env	*env_tmp;

	tmp = *env_list;
	if (search_for_var_in_env("HOME", env_list))
	{
		while (tmp)
		{
			env_tmp = (t_env *)tmp->content;
			if (!ft_strcmp(env_tmp->key, "HOME"))
			{
				if (chdir(env_tmp->value))
					print_custom_errors("minishell: cd: ",
						env_tmp->value, strerror(errno));
				exit_code(1, 1);
				update_path_upon_success(env_list,
					ft_strdup_mem(env_tmp->value));
				return ;
			}
			tmp = tmp->next;
		}
	}
	else
		chdir_home_set(env_list);
}

void	chdir_home_set(t_list **env_list)
{
	char	*username;
	char	*path;
	char	*wd;
	char	*s;

	wd = getcwd(NULL, 0);
	s = ft_strdup_mem(wd);
	free(wd);
	username = getenv("USER");
	path = ft_strjoin_mem(ft_strdup_mem("/Users/"), username);
	if (chdir(path))
	{
		print_custom_errors("minishell: ", "cd", "cannot retrieve HOME");
		exit_code(1, 1);
		return ;
	}
	update_path_upon_success(env_list, s);
}

void	print_error_set_ec(t_cmds *cmd)
{
	print_custom_errors("minishell: cd: ", cmd->args[1],
		strerror(errno));
	exit_code(1, 1);
}
