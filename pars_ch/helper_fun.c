/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_fun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caziane <caziane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 20:24:00 by caziane           #+#    #+#             */
/*   Updated: 2024/10/11 01:43:50 by caziane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec_w/execution.h"

int	basic_errors(char *cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd[i])
	{
		if ((cmd[i] == '(' || cmd[i] == ')' || cmd[i] == '&')
			&& !is_inside_quotes(cmd, i))
			return (printf("minishell: syntax error \n"), 0);
		if ((cmd[i] == '>' && cmd[i + 1] == '<')
			|| ((cmd[i] == '<' && cmd[i + 1] == '>')))
			return (printf("minishell: syntax error \n"), 0);
		if ((cmd[i] == '>' || cmd[i] == '<') && !is_inside_quotes(cmd, i))
		{
			if (cmd[i + 1] == '|' || cmd[i + 2] == '|'
				|| cmd[i + 2] == '>' || cmd[i + 2] == '<')
				return (printf("minishell: syntax error \n"), 0);
		}
		if (cmd[i] == '|' && !is_inside_quotes(cmd, i))
		{
			if (cmd[i + 1] == '|' || cmd[i + 2] == '|')
				return (printf("minishell: syntax error \n"), 0);
		}
		i++;
	}
	return (1);
}

int	ft_strcmp(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (1);
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	ft_isalpha(int a)
{
	if ((a >= 97 && a <= 122) || (a >= 65 && a <= 90))
		return (1);
	return (0);
}

int	ft_isdigit(int a)
{
	if (a >= '0' && a <= '9')
		return (1);
	return (0);
}

int	ft_isalnum(int a)
{
	if (ft_isdigit(a) || ft_isalpha(a) || a == '_')
		return (1);
	return (0);
}
