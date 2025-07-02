/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes3.c                                      	:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:11:05 by ibyeo             #+#    #+#             */
/*   Updated: 2025/04/03 10:09:06 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	handle_single_heredoc(char *delim, int *last_fd)
{
	int		pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		if (*last_fd != -1)
			close(*last_fd);
		return (-1);
	}
	if (write_heredoc_lines(pipefd[1], delim) == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (-1);
	}
	close(pipefd[1]);
	if (*last_fd != -1)
		close(*last_fd);
	*last_fd = pipefd[0];
	return (0);
}

int	handle_heredocs_multiple(char **argv, t_env *envv)
{
	int		i;
	int		last_fd;

	(void)envv;
	i = 0;
	last_fd = -1;
	while (argv[i])
	{
		if (ft_strcmp(argv[i], "<<") == 0 && argv[i + 1])
		{
			if (handle_single_heredoc(argv[i + 1], &last_fd) == -1)
				return (-1);
			i += 2;
		}
		else
			i++;
	}
	return (last_fd);
}

int	count_non_heredoc_tokens(char **argv)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (argv[i])
	{
		if (ft_strcmp(argv[i], "<<") == 0 && argv[i + 1])
			i += 2;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

void	copy_non_heredoc_tokens(char **dst, char **src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (ft_strcmp(src[i], "<<") == 0 && src[i + 1])
			i += 2;
		else
		{
			dst[j++] = ft_strdup(src[i]);
			i++;
		}
	}
	dst[j] = NULL;
}

char	**remove_heredoc_tokens(char **argv)
{
	int		count;
	char	**new_argv;

	count = count_non_heredoc_tokens(argv);
	new_argv = malloc(sizeof(char *) * (count + 1));
	if (!new_argv)
		return (NULL);
	copy_non_heredoc_tokens(new_argv, argv);
	return (new_argv);
}
