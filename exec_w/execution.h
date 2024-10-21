/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 22:37:21 by asayad            #+#    #+#             */
/*   Updated: 2024/10/18 15:06:24 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../pars_ch/minishell.h"
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>

typedef enum memory_manager
{
	Alloc,
	Del_node,
	Del_list,
}	t_memory;

typedef struct malloced_mem
{
	void				*node;
	struct malloced_mem	*next;
}	t_malloc;

typedef struct cmd_param
{
	char	**path_slash;
	char	**environ;
}	t_cmd_param;

/*	Builtins	*/

int			builtins(t_cmds **cmd_lst, t_cmds *lst, t_list **env_list);
int			is_builtin(char *cmd);
int			env_func(t_list **env_list, t_cmds *lst, int *env_counter);
int			export_func(t_list **env_list, t_cmds *lst);
int			echo_func(t_cmds *lst);
int			pwd_func(t_list **env_list, t_cmds *lst);
int			cd_func(t_list **env_list, t_cmds *lst);
int			unset_func(t_list **env_list, t_cmds *lst);
void		update_shlvl(char **env);
char		*update(char *var);
int			single_bt_cmd(t_cmds **lst, t_cmds *cmd_lst, t_list **env_list);

/*	Env	functions	*/

void		add_env(t_list **head, char **env);
void		print_env_list(t_list **list, int *env_counter);
void		print_export_list(t_list *list);
t_env		*create_env(char *key, char *value);
int			ft_strcmp(char *s1, char *s2);
void		ft_strncpy(char *dest, const char *src, unsigned int n);
void		create_min_env(t_list **head);
void		update_env_list_edge_cases(t_list **env_list, char *type);
void		update_under_score(t_list	**env_list);

/*	Export functions	*/

void		bt_export(t_cmds *cmd_lst, t_list **env_list);
void		sorted_env(t_list *env_list);
void		swap_content(t_list *fst_nd, t_list *snd_nd);
int			check_if_valid_var_to_export(char *var, int i);
int			first_char_check(char *var);
int			check_rest_of_var_name(char *var);
void		update_env_list(char *var, t_list **env_list);
int			search_for_var_in_env(char *var, t_list **env_lst);
char		*find_var(char *s);
void		update_var_value(char *var_only, char *var, t_list **env_lst);
void		join_var_value(char *var_only, char *var, t_list **env_lst);
void		add_var_to_env_list(char *var_only, char *var, t_list **env_list);
void		export_only(t_list **env_list);

/*	echo functions	*/

void		bt_echo(t_cmds *lst);
int			print_nl(char *str);
int			dash_counter(char *str);
int			n_counter(char *str);
int			check_echo_args(char **args);
void		print_args(char **args, int i);

/*	pwd funcitons	*/

void		bt_pwd(t_list **env_list);

/*	cd funcitons	*/

void		bt_cd(t_cmds *cmd, t_list **env_list);
void		update_path_upon_failure(t_list **env_list, char *wd);
void		update_path_upon_success(t_list **env_list, char *wd);
char		*get_wd(t_list **env_list);
int			check_if_var_available(t_list **env_list, char *var);
void		cd_special_cases(char *arg, t_list **env_list, char *wd);
void		chdir_home(t_list **env_list);
void		chdir_home_set(t_list **env_list);
void		print_error_set_ec(t_cmds *cmd);

/*	unset	*/

void		bt_unset(t_cmds *cmd, t_list **env_lst);
t_list		*updated_env(t_list *env_list, char *var);
void		ft_lstdelone_mini(t_list *lst, void (*del_mini)(void*));

/*	exit	*/

int			bt_exit(t_cmds **cmd_lst, t_cmds *cmd);
int			exit_code(int value, int i);
int			exit_num_multi_args(t_cmds *cmd);
void		exit_num_overflow(t_cmds *cmd);
void		exit_num_wrap_around(long long num);
void		exit_no_args(t_cmds *cmd);
int			ft_isnum(char *arg);

/*	fds and redirections */

int			is_redirection(char *s);
int			check_files(t_cmds *cmd);
int			check_redirections(char *file, char *redirection, t_cmds *cmds);
void		close_open_fds_file_check(t_cmds *cmd, int counter, int in_or_out);
void		fd_init(t_cmds *cmd);
void		open_pipe(t_cmds *cmd);
int			builtins_redirections(t_cmds *cmd);

/*	Helper functions	*/

int			ft_strncmp(char *s1, char *s2, size_t n);
int			ft_strchr_helper(char *s, int c);
char		*ft_strdup_helper(char *src, int idx);
int			table_size(char **table);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd_mini(char *s, int fd);
void		print_custom_errors(char *cmd, char *arg, char *error);
char		*join_env(char *s1, char *s2);
void		free_table(char **table);
int			ft_strlcpy(char *dst, char *src, int dstsize);
long long	ft_atoi(char *str);

/*  Commands execution  */
void		command_execution(t_cmds **lst, t_list **env_list);
void		abs_p_or_valid_dir(t_cmd_param *paths, t_cmds *cmd);
t_list		*ft_lstnew_mini(char *key, char *value);
void		ft_lstadd_back_mini(t_list **lst, t_list *new);
void		ft_lstclear_mini(t_list **lst, void (*del_mini)(void*));
void		del_mini(void *content);
int			ft_lstsize_mini(t_list *lst);
char		**env_table(t_list **env_list);
char		*find_path(t_list *env_lst);
char		**ft_split_mini(char *s, char c);
void		pre_execution_mini(t_cmd_param *paths, t_list **env_list);
void		path_slash(char **splited_path, char **path_slash);
int			family_processes(t_cmd_param *paths, t_cmds **cmd_lst, t_cmds *cmd,
				t_list **env_list);
void		child_process(t_cmd_param *paths, t_cmds **cmd_lst, t_cmds *cmd,
				t_list **env_list);
void		dup2_custom(int old_fd, int new_fd, t_cmds *cmd);
void		close_in_out(t_cmds *cmd);
void		close_fds(t_cmds **cmd_lst);
void		first_cmd(t_cmds *cmd);
void		last_cmd(t_cmds *cmd);
void		middle_cmds(t_cmds *cmd);
void		execute_cmd(t_cmd_param *paths, t_cmds *cmd);
void		term_previous_processes(t_cmds *cmd);
void		close_fds_wait_processes(t_cmds **cmd_lst);
void		check_cmd_bin(t_cmd_param *paths, t_cmds *cmd);
int			ft_outfile(t_cmds *cmd, char *file, char *redirection, int counter);
char		**key_equal(t_list **env_list);
void		check_if_valid_path(t_cmd_param *paths, t_cmds *cmd);
void		print_table(char **a);
int			find_var_in_table(char **env, char *var);
void		cd_errors(char *arg);
void		sig_quit(int sig);

#endif