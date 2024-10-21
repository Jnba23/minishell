/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 20:28:20 by caziane           #+#    #+#             */
/*   Updated: 2024/10/18 18:48:55 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec_w/execution.h"

char	*expand_norm1(char *line, int *i, char **word, char *new_line)
{
	while (line[*i] && ft_isalnum(line[*i]))
	{
		*word = ft_strjoin_char(*word, line[*i]);
		(*i)++;
	}
	if (new_line)
		return (ft_strjoin_mem(new_line, *word));
	return (NULL);
}

void	expand_norm(char **new_line, t_list **env, char *word, int dcount)
{
	char	*env_value;

	env_value = get_env_value(*env, word);
	if (!env_value || !only_spaces(env_value))
		env_value = "";
	if (dcount % 2 != 0)
		*new_line = ft_strjoin_mem(*new_line, env_value);
	else if (dcount % 2 == 0)
		*new_line = ft_strjoin_mem(*new_line, word);
}

void	dollar_cases_herdoc(char *line, int *i, char **new_line)
{
	if (line[*i] != '$')
		*new_line = ft_strjoin_char(*new_line, line[(*i)++]);
	if (line[*i] == '$' && (line[*i + 1] == ' '
			|| line[*i + 1] == '\t' || !line[*i + 1]))
		*new_line = ft_strjoin_char(*new_line, line[(*i)++]);
	if (line[*i] == '$' && (line[*i + 1] == '\''
			|| line[*i + 1] == '\"'))
		*new_line = ft_strjoin_char(*new_line, line[(*i)++]);
}

void	dollar_cases(char *line, int *i, char **new_line, int *in_quote)
{
	if (line[*i] == '\"')
		*in_quote = !*in_quote;
	if (line[*i] != '$')
		*new_line = ft_strjoin_char(*new_line, line[(*i)++]);
	if (line[*i] == '$' && (line[*i + 1] == ' '
			|| line[*i + 1] == '\t' || !line[*i + 1]))
		*new_line = ft_strjoin_char(*new_line, line[(*i)++]);
	if (line[*i] == '$' && (line[*i + 1] == '\''
			|| line[*i + 1] == '\"') && !*in_quote)
		(*i)++;
}

void	expand_counting(int *dcount, char *line, t_expvar *expvar)
{
	(*dcount)++;
	while (line[++(expvar->i)] && line[expvar->i] == '$')
		(*dcount)++;
	if ((*dcount) % 2 != 0 && (line[expvar->i] == ' '
			|| line[expvar->i] == '\t' || !line[expvar->i]))
		expvar->new_line = ft_strjoin_char(expvar->new_line, '$');
	if ((*dcount) % 2 != 0 && (line[expvar->i] == '\"'
			|| line[expvar->i] == '\'' || !line[expvar->i]) && expvar->in_quote)
		expvar->new_line = ft_strjoin_char(expvar->new_line, '$');
}
