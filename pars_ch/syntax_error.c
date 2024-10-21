/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caziane <caziane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 20:18:53 by caziane           #+#    #+#             */
/*   Updated: 2024/10/01 13:47:20 by caziane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec_w/execution.h"

int	quotes(char *arg)
{
	int	i;
	int	dquote;
	int	squote;

	i = 0;
	dquote = 0;
	squote = 0;
	while (arg && arg[i])
	{
		if (arg[i] == '"')
		{
			if (!squote)
				dquote = !dquote;
		}
		else if (arg[i] == '\'')
		{
			if (!dquote)
				squote = !squote;
		}
		i++;
	}
	if (squote || dquote)
		return (printf("minishell: syntax error\n"), 0);
	return (1);
}

bool	is_inside_quotes(char *cmd, int index)
{
	bool	in_single_quote;
	bool	in_double_quote;
	int		i;

	in_single_quote = false;
	in_double_quote = false;
	i = 0;
	while (i < index)
	{
		if (cmd[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (cmd[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		i++;
	}
	return (in_single_quote || in_double_quote);
}

void	skip_spaces(char *cmd, int *i)
{
	while (cmd && cmd[*i] && (cmd[*i] == ' ' || cmd[*i] == '\t'))
		(*i)++;
}

int	pipes_syntax(char *cmd, int len)
{
	if (len != 0 && (cmd[0] == '|' || cmd[--len] == '|'))
	{
		if (!is_inside_quotes(cmd, 0) && !is_inside_quotes(cmd, len - 1))
			return (0);
	}
	return (1);
}

int	first_end_line(char *cmd)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(cmd);
	skip_spaces(cmd, &i);
	if (len == 1 && (cmd[0] == '<' || cmd[0] == '>'))
	{
		if (!is_inside_quotes(cmd, i) && !is_inside_quotes(cmd, i + 1))
			return (printf("minishell: syntax error \n"), 0);
	}
	while (len > 0 && (cmd[len - 1] == ' ' || cmd[len - 1] == '\t'))
		cmd[--len] = '\0';
	if (!pipes_syntax(cmd, len))
		return (printf("minishell: syntax error \n"), 0);
	if (len > 0 && (cmd[len - 1] == '>' || cmd[len - 1] == '<'))
	{
		if (!is_inside_quotes(cmd, len))
			return (printf("minishell: syntax error\n"), 0);
	}
	return (1);
}
