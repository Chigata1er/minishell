/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes2.c                                      	:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:11:05 by ibyeo             #+#    #+#             */
/*   Updated: 2025/04/03 10:09:06 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	wait_all(pid_t *pids, int count, t_env *envv)
{
	int	status;
	int	j;

	j = 0;
	while (j < count)
	{
		waitpid(pids[j], &status, 0);
		if (j == count - 1)
		{
			if (WIFEXITED(status))
				envv->exit_status = WEXITSTATUS(status);
			else
			{
				envv->exit_status = 1;
			}
		}
		j++;
	}
}

#define BUFFER_SIZE 1024

void	copy_strings(char *dest, char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		dest[i++] = s2[j++];
	}
	dest[i] = '\0';
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joined;
	int		len1;
	int		len2;

	len1 = 0;
	len2 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	joined = malloc(len1 + len2 + 1);
	if (!joined)
		return (NULL);
	copy_strings(joined, s1, s2);
	free(s1);
	return (joined);
}

char	*get_next_line(int fd)
{
	char	*line;
	char	buffer[BUFFER_SIZE + 1];
	int		n;

	line = NULL;
	n = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (n > 0)
	{
		n = read(fd, buffer, BUFFER_SIZE);
		if (n < 0)
			return (NULL);
		buffer[n] = '\0';
		line = ft_strjoin_free(line, buffer);
		if (!line)
			return (NULL);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (line);
}

int	write_heredoc_lines(int write_fd, char *delim)
{
	char	*line;
	char	*newline;

	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		newline = ft_strchr(line, '\n');
		if (newline)
			*newline = '\0';
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	return (0);
}
