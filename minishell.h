/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:11:05 by ibyeo             #+#    #+#             */
/*   Updated: 2025/05/26 10:44:19 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include "./libft/libft.h"
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>
# include <stddef.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <errno.h>

typedef struct s_env				t_env;

extern volatile sig_atomic_t		g_sigint_received;

typedef struct s_redirect_context
{
	char	**argv;
	int		*i;
	int		*last_fd;
	t_env	*envv;
	char	**path;
}	t_redirect_context;

typedef struct s_fd_state
{
	int	in_fd;
	int	out_fd;
	int	last_input_fd;
	int	saved_stdin;
	int	saved_stdout;
}	t_fd_state;

typedef struct s_io
{
	int	in_fd;
	int	out_fd;
	int	prev_fd;
	int	*pipefd;
	int	heredoc_fd;
}	t_io;

typedef struct s_exec_ctx
{
	t_env	*envv;
	char	**path;
}	t_exec_ctx;

typedef struct s_pipe_ctx
{
	int		*prev_fd;
	int		*pipefd;
	int		has_next;
}	t_pipe_ctx;

typedef struct s_proc_info
{
	pid_t	*pids;
	int		pid_index;
}	t_proc_info;

typedef struct s_cmd_ctx
{
	char		**cmds;
	int			i;
	t_pipe_ctx	*pctx;
	t_proc_info	*pinfo;
	t_exec_ctx	*ectx;
}	t_cmd_ctx;

typedef struct s_pipeline_ctx
{
	int			pipefd[2];
	int			prev_fd;
	int			pid_index;
	pid_t		pids[256];
	t_pipe_ctx	pctx;
	t_proc_info	pinfo;
	t_exec_ctx	ectx;
}	t_pipeline_ctx;

typedef struct s_node
{
	char			*value;
	struct s_node	*next;
}	t_node;

typedef struct s_token_context
{
	char	*result;
	char	temp[4096];
	size_t	b;
	char	quote;
}	t_token_context;

typedef struct s_env
{
	int				size;
	int				exit_status;
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_node	*top;
	int				file[100];
	int				file_count;
	int				arg_count;
	char			*file_arg[100];
	char			**args;
}					t_env;

typedef struct s_heredoc
{
	char				*delimiter;
	int					fd;
	struct s_heredoc	*next;
}	t_heredoc;

typedef struct s_io_fds
{
	int	in_fd;
	int	out_fd;
	int	prev_fd;
	int	heredoc_fd;
	int	*pipefd;
}	t_io_fds;

typedef struct s_redir
{
	char	**argv;
	int		*in_fd;
	int		*out_fd;
	int		*i;
	char	*mode;
	t_env	*envv;
}	t_redir;

// lexer1
char			*get_env_value(const char *key, t_env *env);
char			*extract_variable_name(const char *input, size_t *i);
char			*expand_variable(const char *input, size_t *i,
					t_env *envv, char *result);
char			*str_append_char(char *str, char c);
int				handle_dollar_sign(const char **input,
					t_env *envv, char **result);

// lexer2
int				append_segment(const char **input, char **result, size_t len);
int				handle_single_quotes(const char **input, char **result);
int				handle_quoted_expansion(const char **input, t_env *envv,
					char **result, char quote);
int				handle_plain_text(const char **input, char **result);
int				process_remaining_text(const char **input, char **result);

// lexer3
int				process_quote_or_dollar(const char **input, t_env *envv,
					char **result);
int				process_expansion_loop(const char *input, t_env *envv,
					char **result);
char			*expand_variables(const char *input, t_env *envv);
char			**ft_drop_quotes(char **arg, t_env *env);

// lexer4
int				has_unclosed_quote(const char *str);
char			*ft_strndup(const char *s, size_t n);
int				ft_isspace(char c);
const char		*skip_spacess(const char *str);
char			*handle_exit_status(char *result, int exit_status);

// lexer5
int				check_double_gt(const char *line, int *i);
int				check_single_gt(const char *line, int *i, int *count);
int				check_single_gtt(const char *line, int *i, int *count);
int				redirection_syntax_error_token(const char *line);
int				has_invalid_heredoc(const char *line);

// lexer6
int				is_invalid_or_sequence(const char **p);
int				has_invalid_or_usage(const char *line);
int				is_invalid_pipe_context(const char *line, int i);
void			update_quote_state(char c, char *quote);
int				has_invalid_pipe_syntax(const char *line);

// lexer7
int				has_invalid_and_usage(const char *line);
char			*handle_null_line( t_env *env);
char			*free_and_null(char *line);
int				check_redirection_syntax(char *line);
int				check_quote_and_special_tokens(char *line, t_env *env);

// lexer8
int				check_logic_operator_syntax(char *line, t_env *env);
char			*read_full_line(t_env *env);

// parser
size_t			skip_spaces(const char *input, size_t i);
size_t			handle_quotes(const char *input, size_t i, char *quote);
char			*extract_argument(const char *input, size_t start, size_t end);
char			**ft_split_args(const char *input);

// builtins1
void			handle_cd(t_env *envv, char **argv);
void			handle_pwd(t_env *envv);
void			ft_echanger(char **a, char **b);
char			**put_char_in_order(char **str);
char			**copy_env_to_array(t_env *env);

// builtins2
void			print_env_array(char **str, int size, int o);
void			ft_printf_env(t_env *env, int o);
int				handle_builtin_commands1_extra(char **argv, t_env *envv);
int				handle_builtin_commands1(char **argv, t_env *envv);
int				update_existing_var(t_node *current, char *str, size_t key_len);

// builtins3
void			ft_strcpy3(char *dest, const char *s1, const char *s2,
					const char *s3);
char			*ft_strjoin3(const char *s1, const char *s2, const char *s3);
void			add_new_var(t_env *env, char *str);
char			*export_with_plus(char *str, t_env *env);
int				is_valid_export_identifier(char *str);

// builtins4
int				handle_invalid_identifier(t_env *env, char *str);
void			process_valid_export(t_env *env, char *str);
void			ft_push(t_env *env, char *str);
int				is_valid_unset_identifier(const char *str);
int				ft_drop_error_if_invalid(t_env *env, char *str);

// builtins5
int				ft_remove_env_node(t_env *env, char *str, size_t len);
void			ft_drop(t_env *env, char *str);
void			free_path(char **split);
int				handle_export(char **argv, t_env *envv);
int				handle_unset(char **argv, t_env *envv, char ***path);

// builtins6
int				is_numeric(const char *str);
int				exit_shell(char **argv, t_env *envv);
int				handle_builtin_commands2(char **argv,
					t_env *envv, char ***path);
void			execute_command_based_on_input(char **argv,
					t_env *envv, char **path);
void			free_split(char **arr);

// dolarquestion1
int				print_is_directory_error(char *arg, t_env *env);
int				is_path_directory(char *arg, t_env *env);
void			print_command_not_found_or_no_file(char *arg, t_env *env);
int				check_command_accessibility(char *cmd_path, char *arg,
					t_env *env);
int				handle_command_errors(char *cmd_path, char *arg, t_env *env);

// dolarquestion2
void			fork_and_run_child(char *cmd_path, char **argv);
void			handle_child_status(pid_t pid, t_env *env);
void			run_child_process(char *cmd_path, char **argv, t_env *env);
char			*find_command_path(char **path, char **argv);
void			execute_external_command(char **argv, char **path, t_env *env);

// environment1
void			fill_in_env(t_env *envv, char **str);
t_env			*create_env_list(char **envp);

// environment1
t_env			*init_env_struct(void);
void			handle_signal(void);
void			disable_echoctl(void);

// heredoc
void			handle_input_loop(int pipe_fd[2], char *delimiter);
int				start_heredoc_process(char *delimiter);
void			free_env_list(t_env *head);
int				ft_strlenn(char **c);

// redirections1
int				open_output_file(t_redir *r);
void			clear_redir_args(t_redir *r);
int				handle_output_redir(t_redir *r);
int				handle_input_redir(t_redir *r);
int				process_redirection(t_redir *r);

// redirections2
int				handle_redirection_iteration(t_redir *redir,
					char **new_argv, int *i, int *j);
char			**handle_redirection_loop(t_redir *redir, char **new_argv);
char			**handle_redirection(char **argv, int *in_fd,
					int *out_fd, t_env *envv);

// pipe1
void			setup_input_fd(t_io_fds *fds);
void			setup_output_fd(t_io_fds *fds);
void			setup_child_io(t_io_fds *fds);
pid_t			execute_child(char **argv, t_io *io, t_exec_ctx *ctx);
int				setup_pipe(int *pipefd, int has_next);

// pipe2
void			wait_all(pid_t *pids, int count, t_env *envv);
void			copy_strings(char *dest, char *s1, char *s2);
char			*ft_strjoin_free(char *s1, char *s2);
char			*get_next_line(int fd);
int				write_heredoc_lines(int write_fd, char *delim);

// pipe3
int				handle_single_heredoc(char *delim, int *last_fd);
int				handle_heredocs_multiple(char **argv, t_env *envv);
int				count_non_heredoc_tokens(char **argv);
void			copy_non_heredoc_tokens(char **dst, char **src);
char			**remove_heredoc_tokens(char **argv);

// pipe4
char			**process_quotes_and_redirects(char **argv,
					t_io *io, t_env *envv);
char			**process_heredocs(char **argv, t_io *io, t_env *envv);
char			**prepare_argv(char *cmd, t_io *io, t_env *envv);
pid_t			execute_with_pipe(char **argv, t_pipe_ctx *pctx,
					t_io *io, t_exec_ctx *ectx);
void			update_fds(t_pipe_ctx *pctx);

// pipe5
void			handle_command(t_cmd_ctx *ctx);
void			init_pipeline_ctx(t_pipeline_ctx *ctx,
					t_env *envv, char **path);
void			execute_pipeline(char **cmds, t_env *envv, char **path);

// executor1
int				count_non_empty_args(char **argv);
void			copy_non_empty_args(char **argv, char **result);
char			**remove_empty_args(char **argv);
int				has_unquoted_pipe(const char *str);
int				open_infile(char **argv, int *i, int *last_fd);

// executor2
int				process_heredoc(t_redirect_context *ctx, int *fd, int i);
int				open_heredoc(t_redirect_context *ctx);
int				process_redirect_token(char **argv, t_redirect_context *ctx);
int				handle_input_redirect(char **argv, t_env *envv,
					char **path, int *last_fd);
void			restore_fds(int in_fd, int out_fd,
					int stdin_copy, int stdout_copy);

// executor3
int				setup_redirections(char **argv, t_env *envv, char **path,
					int *last_input_fd);
void			save_std_fds(int *saved_stdin, int *saved_stdout);
void			init_fd_state(t_fd_state *fds);
void			setup_child_signals_and_io(t_fd_state *fds);
void			handle_child_process_ex(char ***cleaned_argv,
					t_fd_state *fds, t_env *envv, char **path);

// executor4
void			handle_parent_process_ex(pid_t pid, t_fd_state *fds,
					t_env *envv);
int				prepare_io_and_execute(char ***cleaned_argv, t_fd_state *fds,
					t_env *envv, char **path);
int				handle_and_exec_builtin_or_continue(char ***cleaned_argv,
					t_env *envv, char **path, t_fd_state *fds);

// executor5
int				handle_redir_and_prepare(char **argv, t_env *envv,
					char **path, char ***cleaned_argv);
void			handle_user_input_2(char *inputt, char **argv, t_env *envv,
					char **path);
void			handle_user_input(char *inputt, char **argv,
					t_env *envv, char **path);

// main
int				init_shell(char **envp, t_env **envv, char ***path);
void			shell_loop(char **argv, t_env *envv, char **path);
int				main(int argc, char **argv, char **envp);

#endif /* MINISHELL_H */
