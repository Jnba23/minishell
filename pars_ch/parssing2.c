/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:07:35 by caziane           #+#    #+#             */
/*   Updated: 2024/10/18 20:59:38 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec_w/execution.h"

char	*ft_strdup_env(char *src)
{
	char	*dup;
	size_t	i;
	size_t	l;

	i = 0;
	l = ft_strlen(src);
	dup = my_malloc(sizeof(char) * (l + 1), 0);
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


t_env	*create_env(char *key, char *value)
{
	t_env	*new_env;

	new_env = (t_env *)my_malloc(sizeof(t_env), 0);
	if (!new_env)
		return (NULL);
	new_env->key = key;
	new_env->value = ft_strdup_env(value);
	if (!new_env->value)
		return (NULL);
	return (new_env);
}

void	print_env_listt(t_list **list)
{
	t_list	*current;
	t_env	*en;

	current = *list;
	while (current)
	{
		en = current->content;
		printf("%s=%s\n", en->key, en->value);
		current = current->next;
	}
}

void	ft_lstclear(t_list **lst)
{
	t_list	*cur_node;
	t_list	*nxt_node;

	if (!lst)
		return ;
	cur_node = (*lst);
	while (cur_node)
	{
		nxt_node = cur_node -> next;
		free (cur_node);
		cur_node = nxt_node;
	}
	*lst = NULL;
}

void	add_env(t_list **head, char **env)
{
	int		i;
	int		j;
	char	*key;
	char	*value;

	update_shlvl(env);
	if (!env || !env[0])
		return (create_min_env(head));
	i = -1;
	while (env[++i])
	{
		j = 0;
		skip_equal(env, &i, &j);
		key = my_malloc(j + 1, 0);
		if (!key)
			return ;
		ft_strncpy(key, env[i], j);
		value = ft_strdup_env(env [i] + j + 1);
		if (ft_strlen(env[i]) > 6 && !ft_strncmp("OLDPWD", env[i], 6))
		{
			i++;
			continue ;
		}
		ft_lstadd_back(head, ft_lstnew_env(create_env(key, value)));
	}
}
