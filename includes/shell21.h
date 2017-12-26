/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 14:06:10 by heynard           #+#    #+#             */
/*   Updated: 2017/10/13 13:59:05 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL21_H
# define SHELL21_H

# include <sys/ioctl.h>
# include <dirent.h>
# include <signal.h>
# include <sys/stat.h>
# include <time.h>
# include <fcntl.h>
# include "../libft/includes/libft.h"
# include "linediting.h"

# define TRUE			1
# define FALSE			0

# define MALLOCERROR	"21sh: memory allocation failed\n"

/*
** linked list storing environment variables
** as two strings name and value.
*/

typedef struct			s_var_env
{
	char				*name;
	char				*value;
	struct s_var_env	*next;
}						t_var_env;

/*
** struct storing whole 21sh informations all the time
** the 21sh process is running as the environment variables list,
** the shell return value and others stuff.
*/

typedef struct			s_shell
{
	struct s_var_env	*env;
	struct s_line		*line;
	struct s_line		*quotes;
	struct s_line		*heredoc;
	struct s_line		*sub;
	struct termios		*current_term;
	struct termios		*save_term;
	struct winsize		*win_size;
	struct s_histo		*histo;
	char				q;
	int					err_closed;
	char				*curpath;
	int					exit_value;
	short int			exit_builtin;
	int					nbl;
	int					prompt_size;
	short int			malloc_error;
	short int			simple_mode;
}						t_shell;

/*
** Linked list of token for lexing and parsing operation with the enum typedef
** assiciated
*/

typedef enum			e_tokentype
{
	COMMAND, WORD, SEMI, UNDER_COMMAND, GREAT,
	LESS, DGREAT, DLESS, GREATAND,
	OR_IF, AND_IF, PIPE, GREATPIPE, AND, DEFAULT
}						t_tokentype;

typedef struct			s_token
{
	t_tokentype		type;
	char			*str;
	int				pos;
	struct s_token	*next;
}						t_token;

/*
** Parser
*/

typedef struct			s_redirection
{
	t_tokentype				type;
	int						fd;
	int						target_fd;
	short int				closed;
	struct s_heredoc		*heredoc;
	char					*param;
	struct s_redirection	*next;
}						t_redirection;

typedef	struct			s_ast
{
	char				**av;
	t_tokentype			type;
	t_redirection		*redirection;
	struct s_ast		*left;
	struct s_ast		*right;
}						t_ast;

/*
** execution
*/

typedef struct			s_path_finding
{
	char				*path;
	char				*current_path;
	char				*tmp;
	char				*next_path;
}						t_path_finding;

typedef struct			s_heredoc
{
	char				*str;
	struct s_heredoc	*next;
}						t_heredoc;

/*
** Main function of the shell
*/

void					sh_key_event(t_shell *shell, t_line *line, long key);
void					ft_shell(t_shell *shell, t_line *line);
char					*sh_create_string(t_line *line);
void					sh_prepare_shell(t_shell *shell);
void					sh_prepare_line(t_shell *shell, t_line *line);
void					sh_treat_line(t_shell *shell, t_line *line);
t_shell					*sh_call_shell();
void					sh_end_main(t_shell *shell, t_line *line);

/*
** Simple print error function
*/

void					sh_print_error(int fd, const char *error);

/*
** environment handler functions
*/

void					sh_init_env(char **environ, t_shell *shell);
void					sh_free_env(t_var_env *env);
t_var_env				*sh_malloc_env(t_shell *shell);
void					sh_print_env(t_var_env *env);
char					*sh_get_var_env(t_var_env *env, const char *name);
t_var_env				*sh_copy_environ(char **environ, t_shell *shell,
											t_var_env *tmp, t_var_env *new);
char					**sh_swapenv_to_char(t_var_env *env);
t_var_env				*sh_update_env(t_shell *shell, char *name, char *value);
t_var_env				*sh_add_to_env(t_shell *shell, char *name, char *value);
void					sh_init_env2(t_shell *shell);

/*
** prompt functions
*/

int						sh_prompt(t_shell *shell);

/*
** Line edition functions
*/

int						sh_setup_terminal(t_shell *shell);
void					sh_run_term_config(t_shell *shell);
void					sh_run_save_config(t_shell *shell);
void					sh_print_char_in_line(t_shell *shell,
								t_line *line, char c);
void					sh_move_right(t_shell *shell, t_line *line);
void					sh_move_left(t_shell *shell, t_line *line);
void					sh_delete_char(t_shell *shell, t_line *line);
void					sh_print_line(t_shell *shell, t_line *line);
void					sh_init_line(t_shell *shell, t_line *line);
void					sh_free_line(t_line *line);
void					sh_print_string(t_line *line);
t_string				*sh_add_char_in_string(t_string *str, char c,
								size_t size);
t_string				*sh_add_end(t_string *str, char c);
t_string				*sh_delete_char_in_string(t_string *str);
t_string				*sh_delete_2char_in_string(t_string *str,
								t_string *tmp);
void					sh_remove_cursor(t_line *line);
void					sh_move_left_word(t_shell *shell, t_line *line);
void					sh_move_right_word(t_shell *shell, t_line *line);
void					sh_quote_line(t_shell *shell, t_line *line);
void					sh_move_begin(t_shell *shell, t_line *line);
void					sh_move_end(t_shell *shell, t_line *line);
void					sh_prepare_line_quotes(t_shell *shell,
								t_line *line, char q, t_line *current);
void					sh_quote_prompt(t_shell *shell, char q);

/*
** Historic functions
*/

t_histo					*sh_insert_histo(t_line *line, t_histo *histo);
void					sh_reset_histo(t_histo *histo);
t_string				*sh_dupline(t_string *str);
t_string				*first_space();
void					sh_move_down_histo(t_shell *shell, t_line *line,
								t_histo *histo, t_histo *tmp);
void					sh_move_up_histo(t_shell *shell, t_line *line,
								t_histo *histo, t_histo *tmp);
void					sh_select_one(t_shell *shell, t_line *line);
void					sh_select_all(t_shell *shell, t_line *line);
void					sh_cut(t_shell *shell, t_line *line, int i);
void					sh_copy(t_line *line);
void					sh_paste(t_shell *shell, t_line *line);

/*
** Lexer functions
*/

t_token					*sh_lexer(const char *str, int i, size_t size);
t_token					*lexerloop(const char *str, int *i,
								t_token *lst, t_token **current);
t_token					*handle_quotes(const char *str, int *i, t_token *lst,
								t_token **current);
t_token					*handle_undifined(const char *str, int i, t_token *lst,
								t_token **current);
t_token					*handle_separator(t_token *lst, t_token **current);
t_token					*handle_rredirect(t_token *lst, t_token **current);
t_token					*handle_lredirect(t_token *lst, t_token **current);
t_token					*handle_pipe(t_token *lst, t_token **current);
t_token					*handle_ifs(t_token *lst, t_token **current);
t_token					*handle_and(t_token *lst, t_token **current);
t_token					*init_token(size_t size);
t_token					*save_token(t_token *token, t_token *lst);
void					print_lst(t_token	*lst);
void					free_lst(t_token	*lst);
int						sh_isifs(char c);
void					sh_alter_lst_venv(t_shell *shell, t_token *tmp,
								int i, char *res);
t_token					*handle_integer(const char *str, int *i,
								t_token *lst, t_token **current);
t_token					*handle_integer_greatpipe(const char *str, int *i,
								t_token *lst, t_token **current);
t_token					*handle_integer_great(const char *str, int *i,
								t_token *lst, t_token **current);
t_token					*handle_integer_less(const char *str, int *i,
								t_token *lst, t_token **current);
/*
** parser
*/

char					**create_argv_tab(t_token *first,
								size_t size, t_token *tmp);
int						sh_parse_lst(t_shell *shell,
								t_token *list, t_ast *ast);
int						is_redirection_operator(t_tokentype type);
int						is_binary_operator(t_tokentype type);
int						is_right_required_operator(t_tokentype type);
t_ast					*sh_create_first_node(t_shell *shell, t_token *first,
								int *error);
t_ast					*sh_create_right_node(t_shell *shell, t_token *first,
								t_ast *ast, int *error);
t_ast					*sh_create_left_node(t_shell *shell, t_token *first,
								t_ast *ast, int *error);
t_ast					*sh_create_operator_node(t_token *tmp, t_ast *ast);
t_ast					*sh_parser_words(t_ast *ast, t_token **tmp, int *error);
t_ast					*sh_parser_word(t_token *tmp, t_token *first,
								t_ast *ast, int *error);
t_ast					*sh_parser_semi(t_ast *ast, t_token **tmp);
t_ast					*sh_parser_operator(t_ast *ast, t_token **tmp);
void					sh_free_ast(t_ast *ast);
void					print_ast(t_ast *ast);
int						sh_condition_operator(t_ast *ast, t_token *tmp);
t_redirection			*create_redirection_list(t_shell *shell,
								t_token *first, int *error);
void					free_redirection_list(t_redirection *list);
char					**fill_null_tab(char **argv, size_t size);

/*
** execution functions
*/

void					sh_exec_tree(t_shell *shell, t_ast *ast);
int						sh_handle_redirection(t_shell *shell, t_ast *node,
								t_redirection *redir);
void					sh_handle_command(t_shell *shell, char **av,
								t_ast *node);
t_heredoc				*sh_handle_heredoc(t_shell *shell, t_redirection *redir,
								long int key, int test);
void					sh_free_heredoc(t_heredoc *tmp);
void					sh_path_finding(t_shell *shell, char **av, t_ast *node);
int						sh_handle_redirection(t_shell *shell, t_ast *node,
								t_redirection *redir);
void					sh_exec_pipe(t_shell *shell, t_ast *ast);
int						sh_wait_child(pid_t pid);
int						count_argv(char **av);
t_heredoc				*sh_add_heredoc(t_line *current,
								t_heredoc *tmp, char *s);
void					sh_heredoc_prompt(t_shell *shell);
void					sh_error_execve(const char *path, char **environ);
int						sh_greatand_simple(t_redirection *redir);
int						sh_greatand_param(t_shell *shell, t_redirection *redir);
void					sh_exec_bin(t_shell *shell, const char *path,
								char **av, t_ast *node);

/*
** builtins functions
*/

char					*sh_catpath(t_shell *shell, const char *dir);
void					sh_handle_cd_env_link(t_shell *shell, char *curpath);
void					sh_handle_cd_env(t_shell *shell, char *curpath);
void					sh_builtin_cd(t_shell *shell, int ac, char **av);
void					sh_builtin_echo(int ac, char **av);
void					sh_builtin_env(t_shell *shell, int ac, char **av,
								t_ast *node);
void					sh_builtin_exit(t_shell *shell, int ac, char **av);
void					sh_builtin_setenv(t_shell *shell, int ac, char **av);
int						sh_builtin_unsetenv(t_shell *shell, int ac, char **av);

/*
** signal functions
*/

void					sh_window_resize(int sig);
void					sh_ctr_c(int sig);
void					sh_alternative_ctr_c(int sig);
void					sh_suspended(int sig);
void					sh_ctr_c_quotes(int sig);
void					sh_check_signal(int sig);
void					sh_get_sigint_pipe(int sig);
void					sh_get_sigint(int sig);

/*
** alternative shell
*/

void					sh_alternative_shell(t_shell *shell);

/*
** other functions
*/

char					**ft_strsplit_sh(char const *s);
void					free_argv_tab(char **argv);

#endif
