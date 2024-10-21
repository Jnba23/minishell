/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:47:10 by caziane           #+#    #+#             */
/*   Updated: 2024/10/18 20:59:26 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h> 
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <libc.h>
# include <stdbool.h>
# include <signal.h>
# include "../exec_w/execution.h"
# include <termios.h>



int	g_signalup;
typedef struct s_cmds
{
	char			*cmd;
	char			**args;
	char			**redirections;
	int				fd[3];
	int				pipe_fd[2];
	int				tmp_fd[2];
	bool			here_doc;
	bool			execute;
	pid_t			p_id;
	int				exit_code;
	struct s_cmds	*next;
	struct s_cmds	*previous;
	int				quotes;
}	t_cmds;

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

typedef struct s_expvar
{
	char	*new_line;
	char	*word;
	int		i;
	int		hh;
	int		in_quote;
	t_cmds	*cmd;
}	t_expvar;

typedef enum e_state
{
	GENERAL,
	IN_SQUOTE,
	IN_DQUOTE,
}	t_state;

typedef struct s_main
{
	char		*cmd;
	char		*line;
}	t_main;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_mem
{
	void			*arg;
	struct s_mem	*next;
}	t_mem;

typedef struct s_herdoc
{
	char	*isme;
	char	*deli;
	char	*deli_up;
	int		i;
}	t_herdoc;

//syntaxe error functions
int		quotes(char *arg);
bool	is_inside_quotes(char *cmd, int index);
void	skip_spaces(char *cmd, int *i);
int		pipes_syntax(char *cmd, int len);
int		first_end_line(char *cmd);
int		basic_errors(char *cmd);

//helper functions

int		ft_strcmp(char *s1, char *s2);
int		ft_isalpha(int a);
int		ft_isdigit(int a);
int		ft_isalnum(int a);
char	*ft_strchr(const char *s, int c);
char	*add_spaces_redirections(char *line);
char	*ft_strnew(size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		inset(char const *s, char c);
char	*ft_strtrim(char *s1, char const *set);
char	*ft_strdup(char *src);
void	ft_strncpy(char *dest, const char *src, unsigned int n);
char	*rm_spaces(char *line);
char	**ft_split_double(char *s, char c, char p);
char	*ft_itoa(int n);

//expand

char	*expand_norm1(char *line, int *i, char **word, char *new_line);
void	expand_norm(char **new_line, t_list **env, char *word, int dcount);
void	dollar_cases(char *line, int *i, char **new_line, int *in_quote);
void	expand_counting(int *dcount, char *line, t_expvar *expvar);
void	init_expand_args(char **new_line, char **word, int *i, int *dcount);
void	digit_alph_exp(t_list **env, char *line, t_expvar *expvar, int *dcount);
char	*expand(t_list **env, char *line);
void	arg_expand1(t_cmds **current, t_list **env, int *i);
void	arg_expand2(t_cmds **current, t_list **env, int *i);
void	args_loop(t_list **env, t_cmds **list);
void	redir_expand1(t_cmds *current, char **new, int *i);
void	redir_expand2(t_cmds *current, t_list **env, int *i);
void	redirect_loop(t_list **env, t_cmds *list);
void	cmds_loop(t_list **env, t_cmds **list);
char	**ft_strjoin_table(char **a, char **b);
char	*expand_herdoc(t_list **env, char *line);
void	dollar_cases_herdoc(char *line, int *i, char **new_line);
void	exit_status(t_expvar *var, int *dcount);

//rm quotes
void	rq_helper(t_cmds *current, char **arg, int *i, int *j);
void	rm_quotes_redi(t_cmds *list);
char	*rm_quotes_herdoc(char *deli);
void	cq_helper(t_cmds *current, char **arg, int *i);
void	rm_quotes_cmd(t_cmds *list);
void	rm_helper(t_cmds *current, char **arg, int *i, int *j);
void	rm_quotes(t_cmds *list);

//parssing
char	*ft_strndup(const char *s, size_t n);
int		count_pipes(char *line);
void	state_checker(char c, enum e_state *state);
char	**split_by_pipes(char *line);
int		split_spaces_helper(char *line);
char	**split_norm(char *line, char **result);
char	**split_by_spaces(char *line);
t_cmds	*create_token(char *cmd, char **args, char **redirections);
int		count_redir(char **res2);
int		count_args(char **res2);
int		is_redirection(char *str);
void	fill_token(t_cmds *token, char **res2);
void	initialiser(t_cmds **new_token);
t_cmds	*tokenize_commands(char **res);
void	print_tokens(t_cmds *token_list);
int		ft_strlen(char *s);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		first_end_line(char *cmd);
void	ft_strncpy(char *dest, const char *src, unsigned int n);
t_env	*create_env(char *key, char *value);
void	add_env(t_list **head, char **env);
char	*ft_strdup(char *src);
int		ft_lstsize(t_list *lst);
void	create_min_env(t_list **head);
void	fill_env_vars(int i, t_env *env_var);
void	clear_env(t_list **lst, void (*del)(t_env *var));
void	del(t_env *p);
char	*ft_strtrim(char *s1, char const *set);
int		inset(char const *s, char c);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	print_env_listt(t_list **list);
void	ft_lstclear(t_list **lst);
char	**split_by_pipes(char *line);
char	**split_by_spaces(char *line);
t_cmds	*create_token(char *cmd, char **args, char **redirections);
t_cmds	*tokenize_commands(char **res);
void	print_tokens(t_cmds *token_list);
int		ft_strcmp(char *s1, char *s2);
int		ft_isalnum(int a);
int		ft_isdigit(int a);
int		ft_isalpha(int a);
char	*get_env_value(t_list *env_list, char *key);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoin_char(char *s1, char s2);
char	*set_expand(char *line);
char	*ft_strchr(const char *s, int c);
char	*ft_strndup(const char *s, size_t n);
void	herdoc_open(t_cmds **list, t_list **env);
char	*rm_quotes_herdoc(char *deli);
void	ft_ctrlc(int sig);
void	state_checker(char c, enum e_state *state);
void	args_loop2(t_cmds **list);
void	*my_malloc(size_t size, int i);
t_list	*ft_lstnew_env(void *content);
char	*ft_strdup_env(char *src);
char	*ft_strdup_mem(char *src);
char	*ft_strjoin_mem(char *s1, char *s2);
char	*join_env_mem(char *s1, char *s2);
void	init_expand_args(char **new_line, char **word, int *i, int *dcount);
char	**ft_strjoin_table(char **a, char **b);
void	arg_expand1(t_cmds **curr, t_list **env, int *i);
char	**add_double_quotes(char **a);
void	arg_expand2(t_cmds **curr, t_list **env, int *i);
void	cmd_expand1(t_cmds *current, t_list **env);
void	cmd_expand2(t_cmds *current, t_list **env);
void	cmds_loop(t_list **env, t_cmds **list);
void	args_loop(t_list **env, t_cmds **list);
void	loop_norm(t_cmds *current, int *i);
void	skip_empty_arg(t_cmds *current, int *i);
void	loop_norm2(t_cmds *current);
void	args_loop2(t_cmds **list);
void	redirect_loop(t_list **env, t_cmds *list);
void	rq_helper(t_cmds *current, char **arg, int *i, int *j);
void	rm_quotes_redi(t_cmds *list);
void	delet(void *k);
void	ft_lstclear_env(t_list **lst, void (*delet)(void*));
void	skip_quotes_hd(char *deli, int *i, char **arg, int x);
void	ft_putendl_fd(char *s, int fd);
void	herdoc_handler(int sig);
char	*get_env_value(t_list *env_list, char *key);
void	ft_ctrlc(int sig);
char	*rm_spaces(char *line);
void	parssing(char **cmd, t_list **list, t_cmds **token);
void	ctrld(char *line);
void	minishell(t_cmds **token, t_list **list, char **cmd, int *exitt);
int		syntax_error(char *cmd, char *line);
void	skip_equal(char **env, int *i, int *j);
void	herdoc_file(t_herdoc *h, char **her, t_list **env, int *fd);
void	set_exec(t_cmds **cmds, int i);
void	close_hd(t_cmds **cmd_lst);
void	set_exec(t_cmds **cmds, int i);
int		only_spaces(char *str);

#endif