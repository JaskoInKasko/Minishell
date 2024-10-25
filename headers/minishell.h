/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:55:25 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 18:55:27 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <sys/types.h>
# include <time.h>
# include <fcntl.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include <errno.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <dirent.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

extern int	g_exit_code;

typedef enum e_sign
{
	COMMAND,
	PIPE,
	REDIR,
	OUTPUT_REDIR,
	APPEND_REDIR,
	INPUR_REDIR,
	HEREDOC,
	SKIP,
	SEMICOLON,
	NEW_LINE,
	DIRECTORY,
	SLASH,
	DOT
}	t_sign;

typedef struct s_env
{
	char			*env;
	char			*exp;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_mini_argv
{
	char					*mini_argv;
	int						num;
	int						quote_found;
	struct s_mini_argv		*next;
	struct s_mini_argv		*prev;
}	t_mini_argv;

typedef struct s_group_args
{
	char					**group;
	char					**fd_str;
	int						num;
	int						quote_found;
	int						fd[2];
	int						pid;
	int						file_fd;
	struct s_group_args		*next;
	struct s_group_args		*prev;
}	t_group_args;

typedef struct s_shell
{
	char			*cm_buf; //return value of readline
	t_env			*env_list; //linked list env variables
	t_mini_argv		*argv_list;
	t_group_args	*group_list;
	int				lst_size;
	int				count_childs;
	int				count_args;
	int				stdout_fd;
	int				stdin_fd;
	char			**path_list; // folders in PATH
	char			*path; //path string
	char			*execve_path; //adding path the command name
	char			**argv;// main argv 
	char			**env;// main env
	char			*pwd;
	char			*old_pwd;
	char			**mini_argv; // user input in the shell separated by spaces
	char			**group_args; // user input devided and sorted into groups
	int				access_flag;
	int				argv_len;

	int				i;
	int				redirs_i;
	int				redir_flag;
	int				start;
	int				len;
	int				len_dollar;
	int				len_quote;
	char			c;

	int				cmd;
	int				fd;
	int				num;

	t_mini_argv		*temp;
	t_mini_argv		*old_temp;
	t_group_args	*group;
	t_env			*temp_env_list;

	char			*temp_substr;
	char			*t_sjoin;
	char			*remove;
	char			*remove2;
	char			*remove3;
	char			*temp_cm_buf;

	int				m;
	int				n;
	int				u;
	int				t;

	int				exit_code;

	char			*home;
	char			*hdoc_line;
	char			*temp_hdoc_line;
	char			*hdoc_deliminer;

	int				z;
	int				open_quote;
	int				quote_found;

	pid_t			pid;
	int				is_pipe;
	int				check;
	int				check_sign;
	char			**split;

	t_env			*remove_env_list;

	int				env_check;
	int				env_len;
	int				exp_j;

}	t_shell;

//		LIST
int				ft_lstsize_group_args(t_group_args *lst);
t_env			*ft_lstnew_env(t_shell *shell, char *env_str);
t_env			*ft_lstlast_modified(t_env *lst);
void			ft_lstadd_back_modified(t_env **lst, t_env *node);
void			ft_lstadd_front_modified(t_env **lst, t_env *new);
t_mini_argv		*ft_lstnew_argv(t_shell *shell, char *argv_str);
void			ft_lstadd_back_argv(t_mini_argv **lst, t_mini_argv *node);
t_mini_argv		*ft_lstlast_argv(t_mini_argv *lst);

//      FT_STRCMP
int				ft_strcmp(const char *s1, const char *s2);

//		SIGNAL
void			ft_config_signals(t_shell *shell);
void			ft_stop_heredoc(int signal);
void			ft_handle_signal(int signal);
void			ft_config_child(t_shell *shell);

//		INIT_VARIABLES
bool			ft_init_variables(t_shell *shell, char **argv, char **env);
bool			ft_init_argv(t_shell *shell);
void			ft_find_links(t_shell *shell);
void			ft_check_argv(t_shell *shell, char *str, int start, int len);
void			ft_make_list(t_shell *shell, char *str);
void			ft_argv_len(t_shell *shell);
void			ft_make_double_pointer(t_shell *shell);
int				ft_is_option(char **mini_argv, int index);
int				ft_get_group_len(t_shell *shell);
void			ft_group_list(t_shell *shell, char *group, char *fd_str);
void			ft_make_groups(t_shell *shell);
void			ft_env_list(t_shell *shell);

//		EXIT
void			ft_exit(t_shell *shell, char *msg);

void			ft_check_argv(t_shell *shell, char *str, int start, int len);
void			ft_make_list(t_shell *shell, char *str);

//		GROUPS
void			ft_group_list(t_shell *shell, char *group, char *fd_str);
void			ft_make_groups(t_shell *shell);
t_group_args	*ft_lstnew_group(t_shell *shell);
t_group_args	*ft_lstlast_group(t_group_args *lst);
void			ft_lstadd_back_group(t_group_args **lst, t_group_args *node);

//		FREE_LOOP
void			ft_free_loop(t_shell *shell);
void			ft_free_argv_list(t_shell *shell);
void			ft_free_group_list(t_shell *shell);

//		MAKE_GROUPS
void			ft_make_groups(t_shell *shell);

char			**ft_split_modified(char const *s, char c, char h);

t_group_args	*ft_lstnew_pipe(t_shell *shell);

void			ft_free_env(t_shell *shell);
bool			ft_update_env(t_shell *shell);
void			ft_free_path_list(t_shell *shell);
bool			ft_update_path(t_shell *shell);

char			*get_next_line(int fd);

void			ft_dollar_detected(t_shell *shell);

void			ft_dollar_found(t_shell *shell);
void			ft_dollar_found_in_double_quote(t_shell *shell);

void			ft_update_cm_buf_heredoc(t_shell *shell);
void			ft_quote_found_heredoc(t_shell *shell, char *deliminer,
					int quote_found);
bool			ft_heredoc_check_heredoc(t_shell *shell, char *deliminer);
void			ft_dollar_found_heredoc(t_shell *shell, char *deliminer,
					int quote_found);
void			ft_dollar_check_heredoc(t_shell *shell, char *deliminer,
					int quote_found);
void			ft_print_mini_argv(t_shell *shell);
void			ft_print_group_list(t_shell *shell);

bool			ft_check_empty_group(t_shell *shell);

void			ft_home_found(t_shell *shell);
void			ft_update_env_value(t_shell *shell);

bool			ft_heredoc_check(t_shell *shell);
void			ft_update_cm_buf(t_shell *shell);
void			ft_malloc_check(t_shell *shell, char *ptr,
					char *check1, char *check2);
void			ft_update_env_malloc(t_shell *shell);
void			ft_malloc_env(t_shell *shell, char *check1,
					char *check2, t_env *check3);
void			ft_malloc_group(t_shell *shell, char **check1,
					char **check2, t_group_args *check3);
void			ft_malloc_free(char *ptr, char *check1, char *check2);

void			ft_question_mark_found(t_shell *shell);
void			ft_second_dollar_found(t_shell *shell);

void			ft_dollar_found_in_double_quote(t_shell *shell);

void			ft_home_found(t_shell *shell);
void			ft_quote_found(t_shell *shell);

bool			ft_check_syntax(t_shell *shell);
void			ft_dollar_check(t_shell *shell);

void			ft_cd(t_shell *shell, char **group);
void			ft_update_oldpwd(t_shell *shell);
void			ft_update_pwd(t_shell *shell);
void			ft_add_env(t_shell *shell, char *str);
void			ft_add_env_if_exist(t_shell *shell, char *str);

//      CASE
int				ft_case(t_shell *shell);
void			ft_wait_for_children(t_shell *shell);
int				ft_check_if_wait_for_child(t_shell *shell);
void			ft_wait_and_exit_status(t_shell *shell, t_group_args *temp);
bool			ft_handle_builtins(t_shell *shell, t_group_args *temp);
bool			ft_is_builtin(t_shell *shell);

//      PROCESSESS
void			ft_increment_child_count_and_start_process(t_shell *shell,
					t_group_args *temp);

//      PIPES
void			ft_handle_both_pipes(t_shell *shell, t_group_args *temp);
void			ft_close_prev_pipes(t_group_args *temp);

//      REDIRECTIONS
int				ft_setup_redirection(t_shell *shell, t_group_args *temp, int i);

//      REDIRECTION_RESET
int				ft_reset_redirections(t_shell *shell);
int				ft_reset_stdout(t_shell *shell);
int				ft_reset_stdin(t_shell *shell);

//		REDIRECTION_ERROR_MSGS
void			ft_get_correct_err_msg(t_shell *shell, t_group_args *temp);

//		HEREDOC
int				ft_handle_heredoc(t_shell *shell, t_group_args *temp);

//      CHILDS
void			ft_childs(t_shell *shell, t_group_args *temp);

//      HELPER
int				ft_is_redirection(t_group_args *temp, int i);
int				ft_is_absolute_path(t_group_args *temp);
void			ft_print_cmd_not_found(t_shell *shell, t_group_args *temp);
void			ft_handle_execution_errors(t_shell *shell, t_group_args *temp);

void			ft_pwd(t_shell *shell);
int				ft_check_input(t_shell *shell, char *str);
void			ft_remove_env(t_shell *shell);
void			ft_add_space(t_shell *shell);
bool			ft_heredoc_check_heredoc(t_shell *shell, char *deliminer);
void			ft_update_cm_buf_heredoc(t_shell *shell);
void			ft_init_pipe_values(t_shell *shell);
char			*ft_find_in_env(t_shell *shell, char *var, int len);

//built_in
void			ft_echo(t_shell *shell, char **group);
void			ft_export(t_shell *shell, char **group);
void			ft_unset(t_shell *shell, char **group);
void			ft_env(t_shell *shell, char **group);
void			ft_exit_cmd(t_shell *shell, char **group);
int				ft_is_directory(const char *path);
void			ft_handle_error(t_shell *shell, char **group);

//get_next_line
char			*get_next_line(int fd);
char			*ft_strjoin_jasmin(char *s1, char *s2, int len);
size_t			ft_strlen_jasmin(const char *str);
char			*ft_strchr_jasmin(char *s, int c);
char			*ft_strdup_jasmin(const char *s);
//getpid
pid_t			ft_getpid(void);
//check_in_env
void			ft_check_item_in_env(t_shell *shell);
void			ft_item_found_in_env(t_shell *shell);

void			ft_copy_env(t_shell *shell, char **env);
void			ft_update_oldpwd_if_exist(t_shell *shell);

#endif
