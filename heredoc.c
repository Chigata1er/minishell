/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                      	:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:11:05 by ibyeo             #+#    #+#             */
/*   Updated: 2025/04/03 10:09:06 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	handle_input_loop(int pipe_fd[2], char *delimiter)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (!input || ft_strcmp(input, delimiter) == 0)
		{
			free(input);
			break ;
		}
		write(pipe_fd[1], input, ft_strlen(input));
		write(pipe_fd[1], "\n", 1);
		free(input);
	}
	close(pipe_fd[1]);
}

int	start_heredoc_process(char *delimiter)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		close(pipe_fd[0]);
		handle_input_loop(pipe_fd, delimiter);
		exit(EXIT_SUCCESS);
	}
	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(pipe_fd[0]);
		return (-2);
	}
	return (pipe_fd[0]);
}

void	free_env_list(t_env *head)
{
	t_env	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

int	ft_strlenn(char **c)
{
	int	i;

	i = 0;
	while (c[i])
		i++;
	return (i);
}
