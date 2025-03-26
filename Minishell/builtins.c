/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:11:05 by thitran           #+#    #+#             */
/*   Updated: 2025/03/20 09:11:31 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include "libft/libft.h"
#include <stdlib.h>
#include <stdio.h>

int ft_echo(char **args)
{
    int i = 1;
    int newline = 1;
    if (args[1] && ft_strcmp(args[1], "-n") == 0)
    {
        newline = 0;
        i++;
    }
    while (args[i])
    {
        write(1, args[i], strlen(args[i]));
        if (args[i + 1])
            write(1, " ", 1);
        i++;
    }
    if (newline)
        write(1, "\n", 1);
    return 0;
}

// Change directory built-in command
int ft_cd(t_shell *shell, char **args)
{
    (void)shell;  // Suppress unused parameter warning for 'shell'
    // If 'args' is valid and contains a directory path, change directory
    if (args && args[1]) {
        if (chdir(args[1]) == -1) {
            perror("cd");
            return 1;  // Return non-zero for error
        }
    } else {
        // Handle the case where no arguments are passed to 'cd' (default to HOME)
        if (chdir(getenv("HOME")) == -1) {
            perror("cd");
            return 1;
        }
    }
    return 0;  // Success
}

// Print working directory built-in command
int ft_pwd(void)
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("pwd");
        return 1;
    }
    return 0;  // Success
}

// Export built-in command
int ft_export(t_shell *shell, char **args)
{
    (void)shell;  // Suppress unused parameter warning for 'shell'
    // Implement the export functionality (set an environment variable)
    if (args && args[1]) {
        if (putenv(args[1]) != 0) {
            perror("export");
            return 1;  // Return non-zero for error
        }
    }
    return 0;  // Success
}

// Unset built-in command
int ft_unset(t_shell *shell, char **args)
{
    (void)shell;  // Suppress unused parameter warning for 'shell'
    // Implement unset functionality (remove an environment variable)
    if (args && args[1]) {
        if (unsetenv(args[1]) != 0) {
            perror("unset");
            return 1;  // Return non-zero for error
        }
    }
    return 0;  // Success
}

// Environment built-in command
int ft_env(char **env)
{
    (void)env;  // Suppress unused parameter warning for 'env'
    // Print environment variables
    for (int i = 0; env[i]; i++) {
        printf("%s\n", env[i]);
    }
    return 0;  // Success
}

// Exit built-in command
int ft_exit(char **args)
{
    if (args && args[1]) {
        int exit_code = atoi(args[1]);
        exit(exit_code);
    }
    exit(0);  // Default exit code 0
}
int is_builtin(char *cmd)
{
    if (!cmd)
        return (0);
    if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0 ||
        ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0 ||
        ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0 ||
        ft_strcmp(cmd, "exit") == 0)
        return (1);
    return (0);
}


