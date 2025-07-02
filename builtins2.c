/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:11:05 by ibyeo             #+#    #+#             */
/*   Updated: 2025/04/03 10:09:06 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env_array(char **str, int size, int o)
{
	int	i;

	i = size - 1;
	if (o == 1)
		str = put_char_in_order(str);
	while (i >= 0)
	{
		if (o == 1)
			printf("declare -x %s\n", str[i]);
		else
			printf("%s\n", str[i]);
		free(str[i]);
		i--;
	}
	free(str);
}

void	ft_printf_env(t_env *env, int o)
{
	char	**str;

	str = copy_env_to_array(env);
	if (!str)
	{
		perror("malloc failed");
		return ;
	}
	print_env_array(str, env->size, o);
}

int	handle_builtin_commands1_extra(char **argv, t_env *envv)
{
	if (ft_strcmp(argv[0], "pwd") == 0)
	{
		handle_pwd(envv);
		envv->exit_status = 0;
		return (1);
	}
	else if (ft_strcmp(argv[0], "env") == 0)
	{
		ft_printf_env(envv, 0);
		envv->exit_status = 0;
		return (1);
	}
	return (0);
}

int	handle_builtin_commands1(char **argv, t_env *envv)
{
	if (!argv[0])
		return (0);
	else if (ft_strcmp(argv[0], "cd") == 0)
	{
		handle_cd(envv, argv);
		return (1);
	}
	return (handle_builtin_commands1_extra(argv, envv));
}

int	update_existing_var(t_node *current, char *str, size_t key_len)
{
	while (current)
	{
		if (!str || !current)
			return (0);
		if (ft_strncmp(current->value, str, key_len) == 0
			&& current->value[key_len] == '=')
		{
			free(current->value);
			current->value = ft_strdup(str);
			if (!current->value)
				return (0);
			return (1);
		}
		current = current->next;
	}
	return (0);
}
