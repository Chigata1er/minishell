/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes5.c                                      	:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:11:05 by ibyeo             #+#    #+#             */
/*   Updated: 2025/04/03 10:09:06 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	handle_command(t_cmd_ctx *ctx)
{
	char	**argv;
	t_io	io;
	pid_t	pid;

	ctx->pctx->has_next = (ctx->cmds[ctx->i + 1] != NULL);
	io.in_fd = -1;
	io.out_fd = -1;
	io.prev_fd = *(ctx->pctx->prev_fd);
	io.pipefd = NULL;
	io.heredoc_fd = -1;
	argv = prepare_argv(ctx->cmds[ctx->i], &io, ctx->ectx->envv);
	if (!argv)
		return ;
	pid = execute_with_pipe(argv, ctx->pctx, &io, ctx->ectx);
	ctx->pinfo->pids[(ctx->pinfo->pid_index)++] = pid;
	update_fds(ctx->pctx);
	if (io.heredoc_fd != -1)
		close(io.heredoc_fd);
	free_split(argv);
}

void	init_pipeline_ctx(t_pipeline_ctx *ctx, t_env *envv, char **path)
{
	ctx->prev_fd = -1;
	ctx->pid_index = 0;
	ctx->pctx.pipefd = ctx->pipefd;
	ctx->pctx.prev_fd = &ctx->prev_fd;
	ctx->pinfo.pids = ctx->pids;
	ctx->pinfo.pid_index = ctx->pid_index;
	ctx->ectx.envv = envv;
	ctx->ectx.path = path;
}

void	execute_pipeline(char **cmds, t_env *envv, char **path)
{
	int				i;
	t_pipeline_ctx	ctx;
	t_cmd_ctx		cmd_ctx;

	i = 0;
	init_pipeline_ctx(&ctx, envv, path);
	while (cmds[i])
	{
		cmd_ctx.cmds = cmds;
		cmd_ctx.i = i;
		cmd_ctx.pctx = &ctx.pctx;
		cmd_ctx.pinfo = &ctx.pinfo;
		cmd_ctx.ectx = &ctx.ectx;
		handle_command(&cmd_ctx);
		i++;
	}
	wait_all(ctx.pinfo.pids, ctx.pinfo.pid_index, envv);
}
