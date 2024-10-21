/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_exec_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caziane <caziane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:56:56 by asayad            #+#    #+#             */
/*   Updated: 2024/10/11 03:42:02 by caziane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	pre_execution_mini(t_cmd_param *paths, t_list **env_list)
{
	char	*path;
	char	**splitted_path;

	path = find_path(*env_list);
	if (path)
	{
		splitted_path = ft_split_mini(path, ':');
		if (splitted_path)
		{
			paths->path_slash = my_malloc((table_size(splitted_path) + 1)
					* sizeof(char *), 0);
			if (!paths->path_slash)
				return ;
			path_slash(splitted_path, paths->path_slash);
		}
	}
	else
		paths->path_slash = NULL;
	paths->environ = env_table(env_list);
}

char	*find_path(t_list *env_lst)
{
	t_env	*tmp;
	char	*path;
	int		flag;

	flag = 0;
	while (env_lst)
	{
		tmp = (t_env *)env_lst->content;
		if (!ft_strcmp(tmp->key, "PATH"))
		{
			path = join_env(ft_strdup_mem(tmp->key), ft_strdup_mem(tmp->value));
			flag = 1;
		}
		env_lst = env_lst->next;
	}
	if (flag == 0)
		path = NULL;
	return (path);
}

void	path_slash(char **splited_path, char **path_slash)
{
	int	i;

	i = 0;
	while (splited_path[i])
	{
		path_slash[i] = ft_strjoin_mem(splited_path[i], "/");
		i++;
	}
	path_slash[i] = NULL;
}

char	**env_table(t_list **env_list)
{
	t_env	*tmp_env;
	int		i;
	char	**env_equal;
	char	**env;
	t_list	*tmp_lst;

	i = 0;
	tmp_lst = *env_list;
	env_equal = key_equal(env_list);
	if (!env_equal)
		return (NULL);
	env = my_malloc((ft_lstsize(*env_list) + 1) * sizeof(char *), 0);
	if (!env)
		return (NULL);
	while (tmp_lst && env_equal[i])
	{
		tmp_env = (t_env *)tmp_lst->content;
		env[i] = join_env(ft_strdup_mem(env_equal[i]),
				ft_strdup_mem(tmp_env->value));
		tmp_lst = tmp_lst->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}

void	close_in_out(t_cmds *cmd)
{
	close(cmd->fd[0]);
	close(cmd->fd[1]);
	close(cmd->pipe_fd[1]);
}
