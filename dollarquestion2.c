/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarquestion2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:11:05 by ibyeo             #+#    #+#             */
/*   Updated: 2025/04/03 10:09:06 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	fork_and_run_child(char *cmd_path, char **argv)
{
	extern char	**environ;
	int			err;

	execve(cmd_path, argv, environ);
	err = errno;
	if (err == ENOENT)
	{
		write(2, "minishell: ", 11);
		write(2, argv[0], ft_strlen(argv[0]));
		write(2, ": No such file or directory\n", 29);
		exit(127);
	}
	else if (err == EACCES || err == ENOEXEC || err == EPERM)
	{
		write(2, "minishell: ", 11);
		write(2, argv[0], ft_strlen(argv[0]));
		write(2, ": Permission denied\n", 21);
		exit(126);
	}
	else
	{
		perror("minishell");
		exit(1);
	}
}

void	handle_child_status(pid_t pid, t_env *env)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		env->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		env->exit_status = 128 + WTERMSIG(status);
	else
	{
		env->exit_status = 1;
	}
}

void	run_child_process(char *cmd_path, char **argv, t_env *env)
{
	pid_t		pid;

	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork failed");
		env->exit_status = 1;
		free(cmd_path);
		return ;
	}
	if (pid == 0)
	{
		fork_and_run_child(cmd_path, argv);
	}
	else
	{
		handle_child_status(pid, env);
		free(cmd_path);
	}
}

char	*find_command_path(char **path, char **argv)
{
	int		k;
	char	*str;
	char	*str1;

	if (!path)
		return (NULL);
	k = 0;
	while (path[k])
	{
		str1 = ft_strjoin(path[k], "/");
		if (!str1)
			return (NULL);
		str = ft_strjoin(str1, argv[0]);
		free(str1);
		if (!str)
			return (NULL);
		if (!access(str, X_OK))
			return (str);
		free(str);
		k++;
	}
	return (NULL);
}

void	execute_external_command(char **argv, char **path, t_env *env)
{
	char	*command_path;

	if (argv[0] == NULL)
	{
		env->exit_status = 0;
		return ;
	}
	if (argv[0][0] == '\0')
	{
		write(2, "minishell: command not found\n", 30);
		env->exit_status = 127;
		return ;
	}
	if (is_path_directory(argv[0], env))
		return ;
	if (ft_strchr(argv[0], '/'))
		command_path = ft_strdup(argv[0]);
	else
		command_path = find_command_path(path, argv);
	if (!handle_command_errors(command_path, argv[0], env))
		return ;
	run_child_process(command_path, argv, env);
}
