/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarquestion1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:11:05 by ibyeo             #+#    #+#             */
/*   Updated: 2025/04/03 10:09:06 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_is_directory_error(char *arg, t_env *env)
{
	write(2, "minishell: ", 11);
	write(2, arg, ft_strlen(arg));
	write(2, ": Is a directory\n", 17);
	env->exit_status = 126;
	return (1);
}

int	is_path_directory(char *arg, t_env *env)
{
	struct stat		st;

	if (!arg)
		return (0);
	if (arg[0] == '/' || (arg[0] == '.' && (arg[1] == '/'
				|| (arg[1] == '.' && arg[2] == '/'))))
	{
		if (stat(arg, &st) == 0 && S_ISDIR(st.st_mode))
			return (print_is_directory_error(arg, env));
	}
	return (0);
}

void	print_command_not_found_or_no_file(char *arg, t_env *env)
{
	if (!ft_strchr(arg, '/'))
	{
		write(2, "minishell: ", 11);
		write(2, arg, ft_strlen(arg));
		write(2, ": command not found\n", 21);
	}
	else
	{
		write(2, "minishell: ", 11);
		write(2, arg, ft_strlen(arg));
		write(2, ": No such file or directory\n", 29);
	}
	env->exit_status = 127;
}

int	check_command_accessibility(char *cmd_path, char *arg, t_env *env)
{
	struct stat	st;

	if (stat(cmd_path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		print_is_directory_error(arg, env);
		free(cmd_path);
		return (0);
	}
	if (access(cmd_path, X_OK) != 0)
	{
		perror("minishell");
		env->exit_status = 126;
		free(cmd_path);
		return (0);
	}
	return (1);
}

int	handle_command_errors(char *cmd_path, char *arg, t_env *env)
{
	if (!cmd_path)
	{
		print_command_not_found_or_no_file(arg, env);
		return (0);
	}
	return (check_command_accessibility(cmd_path, arg, env));
}
