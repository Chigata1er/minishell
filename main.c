/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                      	:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:11:05 by ibyeo             #+#    #+#             */
/*   Updated: 2025/04/03 10:09:06 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_shell(char **envp, t_env **envv, char ***path)
{
	char	*path_env;

	*envv = create_env_list(envp);
	if (!*envv)
	{
		ft_putendl_fd("Failed to initialize environment list.", 2);
		return (0);
	}
	disable_echoctl();
	handle_signal();
	path_env = getenv("PATH");
	if (path_env)
		*path = ft_split(path_env, ':');
	else
		*path = NULL;
	return (1);
}

void	shell_loop(char **argv, t_env *envv, char **path)
{
	char	*inputt;

	while (1)
	{
		inputt = read_full_line(envv);
		if (g_sigint_received)
		{
			envv->exit_status = 130;
			g_sigint_received = 0;
		}
		if (!inputt)
			continue ;
		if (inputt[0] != '\0')
			handle_user_input(inputt, argv, envv, path);
		free(inputt);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*envv;
	char	**path;

	(void)argc;
	if (!init_shell(envp, &envv, &path))
		return (1);
	shell_loop(argv, envv, path);
	free_split(path);
	free_env_list(envv);
	return (0);
}
