/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:11:05 by ibyeo             #+#    #+#             */
/*   Updated: 2025/04/03 10:09:06 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	handle_parent_process_ex(pid_t pid, t_fd_state *fds, t_env *envv)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			write(1, "Quit (core dumped)\n", 19);
		envv->exit_status = 128 + WTERMSIG(status);
	}
	else if (WIFEXITED(status))
	{
		envv->exit_status = WEXITSTATUS(status);
	}
	handle_signal();
	restore_fds(fds->in_fd, fds->out_fd,
		fds->saved_stdin, fds->saved_stdout);
}

int	prepare_io_and_execute(char ***cleaned_argv,
	t_fd_state *fds, t_env *envv, char **path)
{
	pid_t	pid;

	if (!*cleaned_argv)
	{
		restore_fds(fds->in_fd, fds->out_fd,
			fds->saved_stdin, fds->saved_stdout);
		return (-1);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid < 0)
	{
		handle_signal();
		perror("fork");
		restore_fds(fds->in_fd, fds->out_fd,
			fds->saved_stdin, fds->saved_stdout);
		return (-1);
	}
	else if (pid == 0)
		handle_child_process_ex(cleaned_argv, fds, envv, path);
	else
		handle_parent_process_ex(pid, fds, envv);
	return (0);
}

int	handle_and_exec_builtin_or_continue(char ***cleaned_argv,
			t_env *envv, char **path, t_fd_state *fds)
{
	if (*cleaned_argv)
	{
		if (handle_builtin_commands1(*cleaned_argv, envv)
			|| handle_builtin_commands2(*cleaned_argv, envv, &path))
		{
			restore_fds(fds->in_fd, fds->out_fd,
				fds->saved_stdin, fds->saved_stdout);
			return (0);
		}
	}
	return (prepare_io_and_execute(cleaned_argv,
			fds, envv, path));
}
