/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caziane <caziane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 03:25:25 by caziane           #+#    #+#             */
/*   Updated: 2024/10/11 03:26:02 by caziane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec_w/execution.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*newone;

	newone = (t_list *)my_malloc(sizeof(t_list), 0);
	if (!newone)
		return (NULL);
	newone -> content = content;
	newone -> next = NULL;
	return (newone);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst)
		return ;
	last = *lst;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	while (last -> next)
	{
		last = last -> next;
	}
	last ->next = new;
}

char	*get_env_value(t_list *env_list, char *key)
{
	t_list	*current;
	t_env	*env;

	current = env_list;
	while (current)
	{
		env = (t_env *)current->content;
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		current = current->next;
	}
	return (NULL);
}

void	ft_ctrlc(int sig)
{
	if (sig == SIGINT)
	{
		if (!waitpid(-1, NULL, WNOHANG))
			return ;
		g_signalup = 1;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		exit_code(1, 1);
	}
}
