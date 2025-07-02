/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:11:05 by ibyeo             #+#    #+#             */
/*   Updated: 2025/04/03 10:09:06 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	count_non_empty_args(char **argv)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (argv[i])
	{
		if (argv[i][0] != '\0')
			count++;
		i++;
	}
	return (count);
}

void	copy_non_empty_args(char **argv, char **result)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (argv[i])
	{
		if (argv[i][0] != '\0')
			result[j++] = ft_strdup(argv[i]);
		i++;
	}
	result[j] = NULL;
}

char	**remove_empty_args(char **argv)
{
	char	**result;
	int		count;

	count = count_non_empty_args(argv);
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	copy_non_empty_args(argv, result);
	return (result);
}

int	has_unquoted_pipe(const char *str)
{
	char	quote;
	size_t	i;

	quote = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && quote == 0)
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		else if (str[i] == '|' && quote == 0)
			return (1);
		i++;
	}
	return (0);
}

int	open_infile(char **argv, int *i, int *last_fd)
{
	int	fd;

	fd = open(argv[*i + 1], O_RDONLY);
	if (fd < 0)
	{
		printf("minishell: %s: %s\n", argv[*i + 1], strerror(errno));
		return (-1);
	}
	if (*last_fd != -1)
		close(*last_fd);
	*last_fd = fd;
	argv[*i][0] = '\0';
	argv[*i + 1][0] = '\0';
	*i += 2;
	return (0);
}
