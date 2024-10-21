/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caziane <caziane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 20:30:27 by caziane           #+#    #+#             */
/*   Updated: 2024/10/14 20:59:01 by caziane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec_w/execution.h"

void	digit_alph_exp(t_list **env, char *line, t_expvar *expvar, int *dcount)
{
	if (line[expvar->i] == '?')
		exit_status(expvar, dcount);
	else if (ft_isdigit(line[expvar->i]))
	{
		if (*dcount % 2 != 0)
		{
			(expvar->i)++;
			expvar->new_line = expand_norm1(line, &expvar->i,
					&expvar->word, expvar->new_line);
		}
		else
			expvar->new_line = expand_norm1(line, &expvar->i,
					&expvar->word, expvar->new_line);
	}
	else if (ft_isalpha(line[expvar->i]) || line[expvar->i] == '_')
	{
		expand_norm1(line, &expvar->i, &expvar->word, NULL);
		expand_norm(&expvar->new_line, env, expvar->word, *dcount);
	}
}

void	dollars_counting(int *dcount, char *line, t_expvar *expvar)
{
	(*dcount)++;
	while (line[++(expvar->i)] && line[expvar->i] == '$')
		(*dcount)++;
}

char	*expand_herdoc(t_list **env, char *line)
{
	t_expvar	expvar;
	int			dcount;

	if (!line)
		return (NULL);
	expvar.new_line = ft_strnew(0);
	expvar.word = ft_strnew(0);
	expvar.i = 0;
	dcount = 0;
	expvar.in_quote = 0;
	while (line && line[expvar.i])
	{
		dollar_cases_herdoc(line, &expvar.i, &expvar.new_line);
		if (line[expvar.i] == '$')
		{
			dollars_counting(&dcount, line, &expvar);
			digit_alph_exp(env, line, &expvar, &dcount);
		}
		dcount = 0;
		expvar.word = ft_strnew(0);
	}
	return (expvar.new_line);
}

void	exit_status(t_expvar *var, int *dcount)
{
	if (*dcount % 2 != 0)
	{
		(var->i)++;
		if (g_signalup == 1)
		{
			var->new_line = ft_strjoin_mem(var->new_line,
					ft_strdup_mem(ft_itoa(1)));
			g_signalup = 0;
		}
		else
		{
			var->new_line = ft_strjoin_mem(var->new_line,
					ft_strdup_mem(ft_itoa(exit_code(1, 0))));
		}
	}
}

char	*expand(t_list **env, char *line)
{
	t_expvar	expvar;
	int			dcount;

	if (!line)
		return (NULL);
	expvar.new_line = ft_strnew(0);
	expvar.word = ft_strnew(0);
	expvar.i = 0;
	dcount = 0;
	expvar.in_quote = 0;
	while (line && line[expvar.i])
	{
		dollar_cases(line, &expvar.i, &expvar.new_line, &expvar.in_quote);
		if (line[expvar.i] == '$')
		{
			expand_counting(&dcount, line, &expvar);
			digit_alph_exp(env, line, &expvar, &dcount);
		}
		dcount = 0;
		expvar.word = ft_strnew(0);
	}
	return (expvar.new_line);
}
