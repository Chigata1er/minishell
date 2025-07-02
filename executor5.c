/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:11:05 by ibyeo             #+#    #+#             */
/*   Updated: 2025/04/03 10:09:06 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	handle_redir_and_prepare(char **argv, t_env *envv,
								char **path, char ***cleaned_argv)
{
	t_fd_state	fds;
	char		**cleaned_args;

	init_fd_state(&fds);
	if (setup_redirections(argv, envv, path, &fds.last_input_fd) < 0)
		return (-1);
	cleaned_args = remove_empty_args(argv);
	free_split(argv);
	save_std_fds(&fds.saved_stdin, &fds.saved_stdout);
	*cleaned_argv = handle_redirection(cleaned_args,
			&fds.in_fd, &fds.out_fd, envv);
	free_split(cleaned_args);
	return (handle_and_exec_builtin_or_continue(cleaned_argv,
			envv, path, &fds));
}

void	handle_user_input_2(char *inputt, char **argv, t_env *envv, char **path)
{
	char	**cleaned_argv;
	char	**cmds;

	if (has_unquoted_pipe(inputt))
	{
		cmds = ft_split(inputt, '|');
		execute_pipeline(cmds, envv, path);
		free_split(cmds);
		free_split(argv);
		return ;
	}
	if (handle_redir_and_prepare(argv, envv, path, &cleaned_argv) == 0)
		free_split(cleaned_argv);
}

void	handle_user_input(char *inputt, char **argv, t_env *envv, char **path)
{
	argv = ft_split_args(inputt);
	if (!argv || !argv[0] || argv[0][0] == '\0')
	{
		free_split(argv);
		return ;
	}
	argv = ft_drop_quotes(argv, envv);
	add_history(inputt);
	if (ft_strcmp(argv[0], "") == 0)
	{
		free_split(argv);
		printf("minishell: '' command not found \n");
		return ;
	}
	handle_user_input_2(inputt, argv, envv, path);
}
/*
void	handle_user_input(char *inputt, char **argv,
			t_env *envv, char **path)
{
	char	**cleaned_argv;
	char	**cmds;

	argv = ft_split_args(inputt);
	if (!argv || !argv[0] || argv[0][0] == '\0')
	{
		free_split(argv);
		return ;
	}
	argv = ft_drop_quotes(argv, envv);
	add_history(inputt);
	if (ft_strcmp(argv[0], "") == 0)
	{
		free_split(argv);
		printf("minishell: '' command not found \n");
		return ;
	}
	if (has_unquoted_pipe(inputt))
	{
		cmds = ft_split(inputt, '|');
		execute_pipeline(cmds, envv, path);
		free_split(cmds);
		free_split(argv);
		return ;
	}
	if (handle_redir_and_prepare(argv, envv, path, &cleaned_argv) == 0)
		free_split(cleaned_argv);
}
*/