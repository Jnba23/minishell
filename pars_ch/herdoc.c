/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:26:20 by caziane           #+#    #+#             */
/*   Updated: 2024/10/18 14:35:37 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec_w/execution.h"

char	*delimiter_up(char *deli)
{
	int		i;
	char	*deli_up;

	i = 0;
	deli_up = ft_strnew(0);
	while (deli[i])
	{
		if (deli[i] == '$' && deli[i + 1] == '$')
			deli_up = ft_strjoin_char(deli_up, deli[i++]);
		if (deli[i] == '$' && (deli[i + 1] == '\'' || deli[i + 1] == '\"'))
			i++;
		else
			deli_up = ft_strjoin_char(deli_up, deli[i++]);
	}
	return (deli_up);
}

char	*open_name(int *fd)
{
	char	*isme;

	isme = ft_strdup_mem("/tmp/brunette.txt");
	fd[2] = open(isme, O_CREAT | O_RDWR | O_TRUNC, 0644);
	return (isme);
}

void	herdoc_loop(t_herdoc *h, t_list **env, int *fd, t_cmds **cmds)
{
	char	*her;

	her = NULL;
	while (1)
	{
		her = readline("> ");
		if (!ttyname(0))
		{
			set_exec(cmds, 0);
			close (fd[2]);
			if (her)
				free(her);
			open(ttyname(2), O_RDWR);
			break ;
		}
		if (!her || !ft_strcmp(her, h->deli_up))
		{
			if (her)
				free(her);
			break ;
		}
		herdoc_file(h, &her, env, fd);
		if (her)
			free (her);
	}
}

void	herdoc_norm(t_herdoc *h, t_cmds *current, t_list **env,
	t_cmds **cmd_list)
{
	while (current->redirections[h->i] && current->execute == true)
	{
		if (!ft_strcmp(current->redirections[h->i], "<<"))
		{
			(current->fd[2] > 0) && (close(current->fd[2]), 0);
			h->isme = open_name(current->fd);
			h->deli = current->redirections[++(h->i)];
			h->deli = delimiter_up(h->deli);
			h->deli_up = rm_quotes_herdoc(h->deli);
			herdoc_loop(h, env, current->fd, cmd_list);
			close(current->fd[2]);
			current->here_doc = true;
		}
		if (!ft_strcmp(current->redirections[h->i], "<"))
			(1) && (current->here_doc = false, close(current->fd[2]),
				current->fd[2] = -1, 0);
		((close(current->fd[2])) && (current->fd[2] = open(h->isme, O_RDONLY),
				unlink(h->isme), 0));
		if (current->execute == false)
			close_hd(cmd_list);
		(h->i)++;
	}
}

void	herdoc_open(t_cmds **list, t_list **env)
{
	t_cmds		*current;
	int			x;
	t_herdoc	h;

	current = *list;
	x = 0;
	signal(SIGINT, herdoc_handler);
	while (current)
	{
		current->fd[2] = -1;
		if (current->redirections)
		{
			h.i = 0;
			herdoc_norm(&h, current, env, list);
		}
		if (current->execute == false)
			break ;
		current = current->next;
	}
	signal(SIGINT, ft_ctrlc);
}
