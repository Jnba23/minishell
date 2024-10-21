/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:35:23 by asayad            #+#    #+#             */
/*   Updated: 2024/10/18 14:32:23 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	empty_env(void)
{
	char	*s;

	s = getcwd(NULL, 0);
	ft_putendl_fd_mini(s, 1);
	if (s)
	{
		free(s);
		s = NULL;
	}
}

void	set_pwd(char *env_pwd)
{
	char	*s;

	s = getcwd(NULL, 0);
	env_pwd = ft_strdup_mem(s);
	free(s);
}

void	bt_pwd(t_list **env_list)
{
	t_list	*tmp;
	t_env	*env_tmp;
	int		flag;

	tmp = *env_list;
	flag = 0;
	if (!tmp)
		return (empty_env());
	while (tmp)
	{
		env_tmp = (t_env *)tmp->content;
		if (!ft_strcmp("PWD", env_tmp->key))
		{
			flag = 1;
			if (!ft_strcmp(env_tmp->value, ""))
				set_pwd(env_tmp->value);
			ft_putendl_fd_mini(env_tmp->value, 1);
		}
		tmp = tmp->next;
	}
	if (flag == 0)
		empty_env();
}

void	sig_quit(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putendl_fd_mini("QUIT: 3", 1);
		exit_code(131, 1);
	}
	else if (sig == SIGINT)
		exit_code(130, 1);
}
