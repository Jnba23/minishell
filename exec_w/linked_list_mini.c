/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_mini.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caziane <caziane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:55:32 by asayad            #+#    #+#             */
/*   Updated: 2024/10/11 03:43:16 by caziane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_lstadd_back_mini(t_list **env_list, t_list *new)
{
	t_list	*temp;

	if (!*env_list)
	{
		*env_list = new;
		return ;
	}
	temp = *env_list;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

t_list	*ft_lstnew_mini(char *key, char *value)
{
	t_list	*node;
	t_env	*env_var;

	node = my_malloc(sizeof(t_list), 0);
	if (!node)
		return (NULL);
	env_var = my_malloc(sizeof(t_env), 0);
	if (!env_var)
		return (NULL);
	env_var->key = key;
	env_var->value = value;
	node->content = (void *)env_var;
	node->next = NULL;
	return (node);
}

void	ft_lstclear_mini(t_list **lst, void (*del_mini)(void*))
{
	t_list	*cur_node;
	t_list	*nxt_node;

	if (!lst || !del_mini)
		return ;
	cur_node = (*lst);
	while (cur_node)
	{
		nxt_node = cur_node -> next;
		del_mini(cur_node->content);
		free (cur_node);
		cur_node = nxt_node;
	}
	*lst = NULL;
}

void	del_mini(void *content)
{
	t_env	*cont;

	cont = (t_env *)content;
	free(cont->key);
	cont->key = NULL;
	free(cont->value);
	cont->value = NULL;
}

void	ft_lstdelone_mini(t_list *lst, void (*del_mini)(void*))
{
	if (!lst || !del_mini)
		return ;
	del_mini (lst -> content);
	free (lst);
}
