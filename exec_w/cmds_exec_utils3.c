/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_exec_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 07:16:31 by asayad            #+#    #+#             */
/*   Updated: 2024/10/18 21:49:10 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	**key_equal(t_list **env_list)
{
	int		i;
	t_list	*tmp_lst;
	t_env	*env_tmp;
	char	**env_eq;

	i = 0;
	tmp_lst = *env_list;
	env_eq = my_malloc((ft_lstsize(*env_list) + 1) * sizeof(char *), 0);
	if (!env_eq)
		return (NULL);
	while (tmp_lst)
	{
		env_tmp = (t_env *)(tmp_lst->content);
		env_eq[i++] = ft_strjoin_mem(ft_strdup_mem(env_tmp->key), "=");
		tmp_lst = tmp_lst->next;
	}
	env_eq[i] = NULL;
	return (env_eq);
}

void	close_fds_wait_processes(t_cmds **cmd_lst)
{
	t_cmds	*cmd;
	int		status;

	cmd = *cmd_lst;
	while (cmd)
	{
		close(cmd->pipe_fd[0]);
		close(cmd->pipe_fd[1]);
		close(cmd->fd[0]);
		close(cmd->fd[1]);
		close(cmd->fd[2]);
		close(cmd->tmp_fd[0]);
		close(cmd->tmp_fd[1]);
		if (waitpid(cmd->p_id, &status, 0) == -1)
			puts("here");
		if (WIFSIGNALED(status) && exit_code(0, 52) != 1)
			exit_code(WTERMSIG(status) + 128, 1);
		if (WIFEXITED(status))
			exit_code(WEXITSTATUS(status), 1);
		cmd = cmd->next;
	}
}

void	ft_putendl_fd_mini(char *s, int fd)
{
	int	i;

	i = 0;
	if (fd < 0 || !s)
		return ;
	while (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
	write (fd, "\n", 1);
}

int	find_var_in_table(char **env, char *var)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (env[i])
	{
		if ((ft_strlen(env[i]) >= ft_strlen(var))
			&& !ft_strncmp(env[i], var, ft_strlen(var)))
		{
			flag = 1;
			break ;
		}
		i++;
	}
	return (flag);
}

void	print_custom_errors(char *cmd, char *arg, char *error)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
}
