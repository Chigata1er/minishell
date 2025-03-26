/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:07:51 by thitran           #+#    #+#             */
/*   Updated: 2025/03/20 09:08:31 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

// Structure for shell state
typedef struct s_shell
{
    char    *input;           // User input
    char    **args;           // Parsed arguments
    char    **env;            // Environment variables
    int     last_exit_status; // Last command exit status
}	t_shell;

void    init_shell(t_shell *shell, char **env);

void    parse_input(t_shell *shell);
void    expand_variables(t_shell *shell);
char    **split_pipes(char *input); // Function to split pipes

void	   execute_command(t_shell *shell);
void    execute_pipeline(t_shell *shell, char **cmds);
void    handle_redirections(t_shell *shell);
int 	is_builtin(char *cmd);
void    signal_handler(int sig);

int     ft_echo(char **args);
int 	ft_cd(t_shell *shell, char **args);
int     ft_pwd(void);
int     ft_export(t_shell *shell, char **args);
int 	ft_unset(t_shell *shell, char **args);
int 	ft_env(char **env);
int     ft_exit(char **args);

void    signal_handler(int sig);

#endif

