/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes1.c                                      	:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:11:05 by ibyeo             #+#    #+#             */
/*   Updated: 2025/04/03 10:09:06 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	setup_input_fd(t_io_fds *fds)
{
	if (fds->heredoc_fd != -1)
	{
		dup2(fds->heredoc_fd, STDIN_FILENO);
		close(fds->heredoc_fd);
	}
	else if (fds->prev_fd != -1)
	{
		dup2(fds->prev_fd, STDIN_FILENO);
		close(fds->prev_fd);
	}
	else if (fds->in_fd != -1)
	{
		dup2(fds->in_fd, STDIN_FILENO);
		close(fds->in_fd);
	}
}

void	setup_output_fd(t_io_fds *fds)
{
	if (fds->pipefd)
	{
		dup2(fds->pipefd[1], STDOUT_FILENO);
		close(fds->pipefd[0]);
		close(fds->pipefd[1]);
	}
	else if (fds->out_fd != -1)
	{
		dup2(fds->out_fd, STDOUT_FILENO);
		close(fds->out_fd);
	}
}

void	setup_child_io(t_io_fds *fds)
{
	setup_input_fd(fds);
	setup_output_fd(fds);
}

pid_t	execute_child(char **argv, t_io *io, t_exec_ctx *ctx)
{
	pid_t		pid;
	t_io_fds	fds;

	fds.in_fd = io->in_fd;
	fds.out_fd = io->out_fd;
	fds.prev_fd = io->prev_fd;
	fds.heredoc_fd = io->heredoc_fd;
	fds.pipefd = io->pipefd;
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		setup_child_io(&fds);
		execute_command_based_on_input(argv, ctx->envv, ctx->path);
		free_split(argv);
		exit(ctx->envv->exit_status);
	}
	return (pid);
}

int	setup_pipe(int *pipefd, int has_next)
{
	if (has_next)
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		return (1);
	}
	return (0);
}
