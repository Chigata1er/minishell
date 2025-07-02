/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:11:05 by ibyeo             #+#    #+#             */
/*   Updated: 2025/04/03 10:09:06 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit((unsigned char)str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	exit_shell(char **argv, t_env *envv)
{
	int	status;

	status = 0;
	printf("exit\n");
	if (argv[1])
	{
		if (!is_numeric(argv[1]))
		{
			printf("exit: %s: numeric argument required\n", argv[1]);
			exit(2);
		}
		if (argv[2])
		{
			printf("exit: too many arguments\n");
			envv->exit_status = 1;
			return (1);
		}
		status = ft_atoi(argv[1]) % 256;
		exit(status);
	}
	exit(envv->exit_status);
}

int	handle_builtin_commands2(char **argv, t_env *envv, char ***path)
{
	if (ft_strcmp(argv[0], "export") == 0)
		return (handle_export(argv, envv));
	if (ft_strcmp(argv[0], "unset") == 0)
		return (handle_unset(argv, envv, path));
	if (ft_strcmp(argv[0], "exit") == 0)
	{
		exit_shell(argv, envv);
		return (1);
	}
	return (0);
}

void	execute_command_based_on_input(char **argv, t_env *envv, char **path)
{
	if (argv[0] == NULL)
		return ;
	if (handle_builtin_commands1(argv, envv))
		return ;
	if (handle_builtin_commands2(argv, envv, &path))
		return ;
	execute_external_command(argv, path, envv);
}

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
