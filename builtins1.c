/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:11:05 by ibyeo             #+#    #+#             */
/*   Updated: 2025/04/03 10:09:06 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_cd(t_env *envv, char **argv)
{
	char	*home;

	if (!argv[1])
	{
		home = get_env_value("HOME", envv);
		if (!home || chdir(home) != 0)
		{
			perror("cd");
			envv->exit_status = 1;
			return ;
		}
	}
	else
	{
		if (chdir(argv[1]) != 0)
		{
			perror("cd");
			envv->exit_status = 1;
			return ;
		}
	}
	envv->exit_status = 0;
}

void	handle_pwd(t_env *envv)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		envv->exit_status = 0;
	}
	else
	{
		perror("pwd");
		envv->exit_status = 1;
	}
}

void	ft_echanger(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

char	**put_char_in_order(char **str)
{
	int	i;
	int	j;
	int	swapped;

	i = 0;
	while (i < (ft_strlenn(str) - 1))
	{
		j = 0;
		swapped = 0;
		while (j < ((ft_strlenn(str) - 1) - i))
		{
			if (ft_strcmp(str[j], str[j + 1]) < 0)
			{
				ft_echanger(&(str[j]), &(str[j + 1]));
				swapped = 1;
			}
			j++;
		}
		if (swapped == 0)
			break ;
		i++;
	}
	return (str);
}

char	**copy_env_to_array(t_env *env)
{
	char	**str;
	int		i;
	t_node	*node;

	str = malloc(sizeof(char *) * (env->size + 2));
	if (!str)
		return (NULL);
	i = 0;
	node = env->top;
	while (node)
	{
		str[i] = ft_strdup(node->value);
		if (!str[i])
		{
			perror("ft_strdup failed");
			while (i--)
				free(str[i]);
			free(str);
			return (NULL);
		}
		i++;
		node = node->next;
	}
	str[i] = NULL;
	return (str);
}
