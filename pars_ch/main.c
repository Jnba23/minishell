/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:10:52 by caziane           #+#    #+#             */
/*   Updated: 2024/10/18 18:57:52 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec_w/execution.h"

void	skip_equal(char **env, int *i, int *j)
{
	while (env[*i][*j] != '=' && env[*i][*j])
		(*j)++;
}

int	check_cmd(char *cmd, char *line)
{
	if (!cmd)
	{
		free(line);
		line = NULL;
		return (0);
	}
	return (1);
}

void	main_norm(t_main *m, t_cmds **token, t_list **list, int *exitt)
{
	while (1)
	{
		signal(SIGINT, ft_ctrlc);
		signal(SIGQUIT, SIG_IGN);
		rl_catch_signals = 0;
		m->line = readline("minishell$ ");
		ctrld(m->line);
		add_history(m->line);
		m->cmd = rm_spaces(m->line);
		if (!syntax_error(m->cmd, m->line))
			continue ;
		m->cmd = add_spaces_redirections(m->cmd);
		if (!check_cmd(m->cmd, m->line))
			continue ;
		minishell(token, list, &m->cmd, exitt);
		free(m->line);
		m->line = NULL;
	}
}

int	main(int ac, char **av, char **env)
{
	t_main			m;
	t_list			*list;
	t_cmds			*token;
	static int		exitt;
	struct termios	term;

	(void)av;
	token = NULL;
	list = NULL;
	add_env(&list, env);
	if (ac == 1)
	{
		tcgetattr(STDIN_FILENO, &term);
		main_norm(&m, &token, &list, &exitt);
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
	else
		printf("Don't use args :|\n");
	my_malloc(0, 1);
}
