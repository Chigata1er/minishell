/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:11:05 by ibyeo             #+#    #+#             */
/*   Updated: 2025/04/03 10:09:06 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	process_heredoc(t_redirect_context *ctx, int *fd, int i)
{
	int	tmp_fd;

	tmp_fd = start_heredoc_process(ctx->argv[i + 1]);
	if (tmp_fd == -1)
	{
		perror("heredoc failed");
		return (-1);
	}
	if (tmp_fd == -2)
	{
		ctx->envv->exit_status = 130;
		return (-2);
	}
	if (*fd != -1)
		close(*fd);
	*fd = tmp_fd;
	ctx->argv[i][0] = '\0';
	ctx->argv[i + 1][0] = '\0';
	return (0);
}

int	open_heredoc(t_redirect_context *ctx)
{
	int	fd;
	int	i;
	int	result;

	fd = -1;
	i = *ctx->i;
	while (ctx->argv[i] && ctx->argv[i + 1])
	{
		if (ft_strcmp(ctx->argv[i], "<<") == 0)
		{
			result = process_heredoc(ctx, &fd, i);
			if (result != 0)
				return (result);
			i += 2;
		}
		else
			break ;
	}
	if (*ctx->last_fd != -1)
		close(*ctx->last_fd);
	*ctx->last_fd = fd;
	*ctx->i = i;
	return (0);
}

int	process_redirect_token(char **argv, t_redirect_context *ctx)
{
	int	result;

	if (ft_strcmp(argv[*ctx->i], "<") == 0 && argv[*ctx->i + 1])
	{
		result = open_infile(ctx->argv, ctx->i, ctx->last_fd);
		if (result < 0)
			return (-1);
	}
	else if (ft_strcmp(argv[*ctx->i], "<<") == 0 && argv[*ctx->i + 1])
	{
		result = open_heredoc(ctx);
		if (result < 0)
			return (result);
	}
	else
		(*ctx->i)++;
	return (0);
}

int	handle_input_redirect(char **argv, t_env *envv,
		char **path, int *last_fd)
{
	int					result;
	t_redirect_context	ctx;

	ctx.argv = argv;
	ctx.i = &(int){0};
	ctx.last_fd = last_fd;
	ctx.envv = envv;
	ctx.path = path;
	while (argv[*ctx.i])
	{
		result = process_redirect_token(argv, &ctx);
		if (result < 0)
			return (result);
	}
	return (0);
}

void	restore_fds(int in_fd, int out_fd,
		int stdin_copy, int stdout_copy)
{
	dup2(stdin_copy, STDIN_FILENO);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdin_copy);
	close(stdout_copy);
	if (in_fd != -1)
		close(in_fd);
	if (out_fd != -1)
		close(out_fd);
}
