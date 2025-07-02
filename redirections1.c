/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:11:05 by ibyeo             #+#    #+#             */
/*   Updated: 2025/04/03 10:09:06 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	open_output_file(t_redir *r)
{
	if (ft_strcmp(r->mode, ">") == 0)
		return (open(r->argv[*r->i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else if (ft_strcmp(r->mode, ">>") == 0)
		return (open(r->argv[*r->i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644));
	errno = EINVAL;
	return (-1);
}

void	clear_redir_args(t_redir *r)
{
	r->argv[*r->i][0] = '\0';
	r->argv[*r->i + 1][0] = '\0';
	*r->i += 2;
}

int	handle_output_redir(t_redir *r)
{
	int	fd;

	if (!r->argv[*r->i + 1] || r->argv[*r->i + 1][0] == '\0')
	{
		r->envv->exit_status = 2;
		return (-1);
	}
	if (*r->out_fd != -1)
		close(*r->out_fd);
	r->mode = r->argv[*r->i];
	fd = open_output_file(r);
	if (fd == -1)
	{
		perror("open output");
		r->envv->exit_status = 1;
		return (-1);
	}
	*r->out_fd = fd;
	clear_redir_args(r);
	return (0);
}

int	handle_input_redir(t_redir *r)
{
	int	fd;

	fd = open(r->argv[*r->i + 1], O_RDONLY);
	if (fd == -1)
	{
		perror("open input");
		r->envv->exit_status = 1;
		return (-1);
	}
	if (*r->in_fd != -1)
		close(*r->in_fd);
	*r->in_fd = fd;
	r->argv[*r->i][0] = '\0';
	r->argv[*r->i + 1][0] = '\0';
	*r->i += 2;
	return (0);
}

int	process_redirection(t_redir *r)
{
	if ((ft_strcmp(r->argv[*r->i], ">") == 0
			|| ft_strcmp(r->argv[*r->i], ">>") == 0)
		&& r->argv[*r->i + 1] && r->argv[*r->i + 1][0] != '\0')
	{
		if (handle_output_redir(r) == -1)
			return (-1);
	}
	else if (ft_strcmp(r->argv[*r->i], "<") == 0
		&& r->argv[*r->i + 1] && r->argv[*r->i + 1][0] != '\0')
	{
		if (handle_input_redir(r) == -1)
			return (-1);
	}
	else
		return (0);
	return (1);
}
