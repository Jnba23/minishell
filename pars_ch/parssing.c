/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caziane <caziane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 20:39:00 by caziane           #+#    #+#             */
/*   Updated: 2024/10/07 16:19:42 by caziane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec_w/execution.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*result;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < n && s[i] != '\0')
		i++;
	result = (char *)my_malloc((i + 1), 0);
	if (!result)
		return (NULL);
	while (j < i)
	{
		result[j] = s[j];
		j++;
	}
	result[i] = '\0';
	return (result);
}

int	count_pipes(char *line)
{
	int				count;
	enum e_state	state;
	int				i;

	count = 1;
	i = 0;
	state = GENERAL;
	while (line[i])
	{
		if (line[i] == '\'' && state == GENERAL)
			state = IN_SQUOTE;
		else if (line[i] == '\'' && state == IN_SQUOTE)
			state = GENERAL;
		else if (line[i] == '"' && state == GENERAL)
			state = IN_DQUOTE;
		else if (line[i] == '"' && state == IN_DQUOTE)
			state = GENERAL;
		else if (line[i] == '|' && state == GENERAL)
			count++;
		i++;
	}
	return (count);
}

void	state_checker(char c, enum e_state *state)
{
	if (c == '\'' && *state == GENERAL)
		*state = IN_SQUOTE;
	else if (c == '\'' && *state == IN_SQUOTE)
		*state = GENERAL;
	else if (c == '"' && *state == GENERAL)
		*state = IN_DQUOTE;
	else if (c == '"' && *state == IN_DQUOTE)
		*state = GENERAL;
}

char	**split_by_pipes(char *line)
{
	char			**result;
	char			*start;
	int				i;
	int				count;
	enum e_state	state;

	count = count_pipes(line);
	result = (char **)my_malloc((sizeof(char *) * (count + 1)), 0);
	if (!result)
		return (NULL);
	state = GENERAL;
	start = line;
	count = 0;
	i = -1;
	while (line[++i])
	{
		state_checker(line[i], &state);
		if (line[i] == '|' && state == GENERAL)
		{
			result[count++] = ft_strndup(start, line + i - start);
			start = line + i + 1;
		}
	}
	result[count++] = ft_strdup_mem(start);
	return (result[count] = NULL, result);
}

int	split_spaces_helper(char *line)
{
	int				i;
	int				count;
	enum e_state	state;

	count = 1;
	i = 0;
	state = GENERAL;
	while (line && line[i])
	{
		if (line[i] == '\'' && state == GENERAL)
			state = IN_SQUOTE;
		else if (line[i] == '\'' && state == IN_SQUOTE)
			state = GENERAL;
		else if (line[i] == '"' && state == GENERAL)
			state = IN_DQUOTE;
		else if (line[i] == '"' && state == IN_DQUOTE)
			state = GENERAL;
		else if ((line[i] == ' ' || line[i] == '\t') && state == GENERAL)
		{
			if (i > 0 && line[i - 1] != ' ' && line[i - 1] != '\t')
				count++;
		}
		i++;
	}
	return (count);
}
