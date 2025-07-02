/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes4.c                                      	:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:11:05 by ibyeo             #+#    #+#             */
/*   Updated: 2025/04/03 10:09:06 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	**process_quotes_and_redirects(char **argv, t_io *io, t_env *envv)
{
	char	**new_argv;

	new_argv = ft_drop_quotes(argv, envv);
	if (!new_argv)
		return (free_split(argv), NULL);
	if (new_argv != argv)
		free_split(argv);
	argv = new_argv;
	new_argv = handle_redirection(argv, &io->in_fd, &io->out_fd, envv);
	if (!new_argv)
		return (free_split(argv), NULL);
	if (new_argv != argv)
		free_split(argv);
	return (new_argv);
}

char	**process_heredocs(char **argv, t_io *io, t_env *envv)
{
	char	**new_argv;
	int		i;

	i = 0;
	while (argv && argv[i])
	{
		if (ft_strcmp(argv[i], "<<") == 0 && argv[i + 1])
		{
			io->heredoc_fd = handle_heredocs_multiple(argv, envv);
			if (io->heredoc_fd == -1)
				return (free_split(argv), NULL);
			new_argv = remove_heredoc_tokens(argv);
			if (!new_argv)
				return (free_split(argv), NULL);
			if (new_argv != argv)
				free_split(argv);
			return (new_argv);
		}
		i++;
	}
	return (argv);
}

char	**prepare_argv(char *cmd, t_io *io, t_env *envv)
{
	char	**argv;

	argv = ft_split_args(cmd);
	if (!argv)
		return (NULL);
	argv = process_heredocs(argv, io, envv);
	if (!argv)
		return (NULL);
	argv = process_quotes_and_redirects(argv, io, envv);
	return (argv);
}

pid_t	execute_with_pipe(char **argv, t_pipe_ctx *pctx,
				t_io *io, t_exec_ctx *ectx)
{
	if (setup_pipe(pctx->pipefd, pctx->has_next))
		io->pipefd = pctx->pipefd;
	else
		io->pipefd = NULL;
	return (execute_child(argv, io, ectx));
}

void	update_fds(t_pipe_ctx *pctx)
{
	if (*(pctx->prev_fd) != -1)
		close(*(pctx->prev_fd));
	if (pctx->has_next)
	{
		close(pctx->pipefd[1]);
		*(pctx->prev_fd) = pctx->pipefd[0];
	}
	else
		*(pctx->prev_fd) = -1;
}
