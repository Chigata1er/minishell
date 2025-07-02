/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:11:05 by ibyeo             #+#    #+#             */
/*   Updated: 2025/04/03 10:09:06 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_remove_env_node(t_env *env, char *str, size_t len)
{
	t_node	*curr;
	t_node	*prev;

	curr = env->top;
	prev = NULL;
	while (curr)
	{
		if (ft_strncmp(curr->value, str, len) == 0
			&& (curr->value[len] == '=' || curr->value[len] == '\0'))
		{
			if (!prev)
				env->top = curr->next;
			else
				prev->next = curr->next;
			free(curr->value);
			free(curr);
			env->size--;
			return (1);
		}
		prev = curr;
		curr = curr->next;
	}
	return (0);
}

void	ft_drop(t_env *env, char *str)
{
	size_t	len;

	if (ft_drop_error_if_invalid(env, str))
		return ;
	len = ft_strlen(str);
	if (ft_remove_env_node(env, str, len))
		env->exit_status = 0;
	else
		env->exit_status = 1;
}
/*
void	free_path(char **path)
{
	int	i;

	if (!path)
		return ;
	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}
*/

void	free_path(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
}

int	handle_export(char **argv, t_env *env)
{
	int	i;

	i = 1;
	if (ft_strlenn(argv) >= 2)
	{
		while (argv[i])
		{
			ft_push(env, argv[i]);
			i++;
		}
		env->exit_status = 0;
	}
	else
	{
		ft_printf_env(env, 1);
		env->exit_status = 0;
	}
	return (1);
}

int	handle_unset(char **argv, t_env *envv, char ***path)
{
	if (argv[1])
	{
		ft_drop(envv, argv[1]);
		if (ft_strncmp(argv[1], "PATH", 4) == 0)
		{
			free_path(*path);
			*path = NULL;
		}
	}
	envv->exit_status = 0;
	return (1);
}
/*
int	handle_unset(char **argv, t_env *envv, char ***path)
{
	if (argv[1])
	{
		ft_drop(envv, argv[1]);
		if (ft_strcmp(argv[1], "PATH") == 0)
		{
			free_path(*path);
			*path = malloc(2 * sizeof(char *));
			if (*path == NULL)
			{
				perror("malloc");
				return (1);
			}
			(*path)[0] = ft_strdup("/usr/");
			if (!(*path)[0])
			{
				free(*path);
				perror("ft_strdup");
				return (1);
			}
			(*path)[1] = NULL;
		}
	}
	envv->exit_status = 0;
	return (1);
}
*/
