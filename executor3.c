/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:11:05 by ibyeo             #+#    #+#             */
/*   Updated: 2025/04/03 10:09:06 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	setup_redirections(char **argv, t_env *envv, char **path,
									int *last_input_fd)
{
	if (handle_input_redirect(argv, envv, path, last_input_fd) < 0)
	{
		free_split(argv);
		return (-1);
	}
	return (0);
}

void	save_std_fds(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
}

void	init_fd_state(t_fd_state *fds)
{
	fds->in_fd = -1;
	fds->out_fd = -1;
	fds->last_input_fd = -1;
}

void	setup_child_signals_and_io(t_fd_state *fds)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (fds->last_input_fd != -1)
	{
		dup2(fds->last_input_fd, STDIN_FILENO);
		close(fds->last_input_fd);
	}
	if (fds->out_fd >= 0)
		dup2(fds->out_fd, STDOUT_FILENO);
}

void	handle_child_process_ex(char ***cleaned_argv,
	t_fd_state *fds, t_env *envv, char **path)
{
	setup_child_signals_and_io(fds);
	execute_command_based_on_input(*cleaned_argv, envv, path);
	exit(envv->exit_status);
}
