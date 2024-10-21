/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_fun1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caziane <caziane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 20:25:29 by caziane           #+#    #+#             */
/*   Updated: 2024/10/07 21:50:41 by caziane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec_w/execution.h"

char	*ft_strdup(char *src)
{
	char	*dup;
	size_t	i;
	size_t	l;

	i = 0;
	l = ft_strlen(src);
	dup = malloc(sizeof(char) * (l + 1));
	if (!dup)
		return (NULL);
	while (i < l)
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s && s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s && s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

void	spaces_helper(char **line, char **new_line)
{
	int	len;

	len = ft_strlen(*line);
	*new_line = my_malloc(len * 3 + 1, 0);
	if (!*new_line)
		return ;
}

char	*add_spaces_redirections(char *line)
{
	char			*new_line;
	int				i;
	int				j;
	enum e_state	state;

	spaces_helper(&line, &new_line);
	i = -1;
	j = 0;
	state = GENERAL;
	while (line && line[++i])
	{
		state_checker(line[i], &state);
		if ((line[i] == '<' || line[i] == '>') && state == GENERAL)
		{
			if (i > 0 && line[i - 1] != ' '
				&& line[i - 1] != '<' && line[i - 1] != '>')
				new_line[j++] = ' ';
			new_line[j++] = line[i];
			if (line[i + 1] != ' ' && line[i + 1] != '<' && line[i + 1] != '>')
				new_line[j++] = ' ';
		}
		else
			new_line[j++] = line[i];
	}
	return (new_line[j] = '\0', new_line);
}

char	*ft_strnew(size_t size)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)my_malloc((size + 1), 0);
	if (!str)
		return (NULL);
	while (i <= size)
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}
