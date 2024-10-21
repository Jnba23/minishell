/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 01:57:10 by caziane           #+#    #+#             */
/*   Updated: 2024/10/13 15:07:17 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec_w/execution.h"

void	ft_putendl_fd(char *s, int fd)
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

void	herdoc_handler(int sig)
{
	g_signalup = 1;
	if (sig == SIGINT)
		close(0);
}

void	update_shlvl(char **env)
{
	int		i;
	char	*s;

	i = 0;
	if (!env || !env[0])
		return ;
	if (find_var_in_table(env, "SHLVL"))
	{
		while (env[i])
		{
			if ((ft_strlen(env[i]) > 5)
				&& !ft_strncmp(env[i], "SHLVL", 5) && env[i][5] == '=')
			{
				env[i] = update(env[i]);
				break ;
			}
			i++;
		}
	}
	else
	{
		s = ft_strdup_mem("SHLVL=1");
		env = ft_strjoin_table(env, &s);
	}
}

char	*update(char *var)
{
	int		i;
	char	*num;

	if (!var[6] || !ft_isnum(var + 7))
	{
		var = ft_strdup_mem("SHLVL=1");
		return (var);
	}
	if (ft_atoi(var + 6) == 999)
	{
		var = ft_strdup_mem("SHLVL=");
		return (var);
	}
	i = ft_atoi(var + 6) + 1;
	num = ft_strjoin_mem(ft_strdup_mem("="), ft_itoa(i));
	var = ft_strjoin_mem(ft_strdup_mem("SHLVL"), num);
	return (var);
}

void	skip_quotes_hd(char *deli, int *i, char **arg, int x)
{
	if (x == 0)
	{
		while (deli[*i] && deli[*i] != '\'')
			*arg = ft_strjoin_char(*arg, deli[(*i)++]);
	}
	else
	{
		while (deli[*i] && deli[*i] != '\"')
			*arg = ft_strjoin_char(*arg, deli[(*i)++]);
	}
}
