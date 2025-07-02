/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:11:05 by ibyeo             #+#    #+#             */
/*   Updated: 2025/04/03 10:09:06 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	handle_redirection_iteration(t_redir *redir, char **new_argv,
		int *i, int *j)
{
	int	res;

	res = process_redirection(redir);
	if (res == -1)
		return (-1);
	else if (res == 0 && redir->argv[*i][0] != '\0')
		new_argv[(*j)++] = ft_strdup(redir->argv[(*i)++]);
	else if (res == 0)
		(*i)++;
	else if (res == 1)
		(*i) += 2;
	*redir->i = *i;
	return (0);
}

char	**handle_redirection_loop(t_redir *redir, char **new_argv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	*redir->i = i;
	while (redir->argv[i])
	{
		if (handle_redirection_iteration(redir, new_argv, &i, &j) == -1)
		{
			while (j > 0)
				free(new_argv[--j]);
			free(new_argv);
			return (NULL);
		}
	}
	new_argv[j] = NULL;
	return (new_argv);
}

/*
char	**handle_redirection_loop(t_redir *redir, char **new_argv)
{
	int	i;
	int	j;
	int	res;

	i = 0;
	j = 0;
	*redir->i = i;
	while (redir->argv[i])
	{
		res = process_redirection(redir);
		if (res == -1)
		{
			while (j > 0)
				free(new_argv[--j]);
			free(new_argv);
			return (NULL);
		}
		else if (res == 0 && redir->argv[i][0] != '\0')
			new_argv[j++] = ft_strdup(redir->argv[i++]);
		else if (res == 0)
			i++;
		else if (res == 1)
			i += 2;
		*redir->i = i;
	}
	new_argv[j] = NULL;
	return (new_argv);
}
*/
char	**handle_redirection(char **argv, int *in_fd, int *out_fd, t_env *envv)
{
	t_redir	redir;
	char	**new_argv;
	int		i;

	redir.argv = argv;
	redir.in_fd = in_fd;
	redir.out_fd = out_fd;
	redir.envv = envv;
	redir.i = &i;
	new_argv = malloc(sizeof(char *) * 1024);
	if (!new_argv)
		return (NULL);
	return (handle_redirection_loop(&redir, new_argv));
}
