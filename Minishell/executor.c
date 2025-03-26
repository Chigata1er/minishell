/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:10:22 by thitran           #+#    #+#             */
/*   Updated: 2025/03/20 09:10:47 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>

// Global variable for the signal handler
volatile sig_atomic_t g_signal_status = 0;
/*
// Signal handler
void signal_handler(int sig)
{
    if (sig == SIGINT)
    {
        write(1, "\n", 1);  // New line on ctrl-C
        g_signal_status = 1; // Set signal flag
    }
    else if (sig == SIGQUIT)
    {
        // Ignore ctrl-\ (SIGQUIT)
    }
}
*/
// Display the prompt
void display_prompt(void)
{
    if (g_signal_status)
    {
        printf("\n"); // Handle signal by printing a new prompt line
        g_signal_status = 0;
    }
    printf("minishell$ ");
}

// Handle environment variables ($var)
void expand_env_variables(t_shell *shell)
{
    int i = 0;
    while (shell->args[i])
    {
        char *arg = shell->args[i];
        if (arg[0] == '$')
        {
            char *var = getenv(arg + 1); // Get environment variable value
            if (var)
                shell->args[i] = strdup(var); // Replace with the actual value
            else
                shell->args[i] = strdup(""); // If not found, replace with empty string
        }
        i++;
    }
}

void parse_quotes(t_shell *shell)
{
    int i = 0;
    while (shell->args[i])
    {
        char *arg = shell->args[i];
        char *new_arg = malloc(strlen(arg) + 1); // Allocate space for the new string.
        if (!new_arg) // Check for memory allocation failure.
        {
            perror("malloc");
            return;
        }
        int j = 0;
        int in_single_quote = 0;
        int in_double_quote = 0;

        // Loop through each character of the argument
        for (int k = 0; arg[k] != '\0'; k++)
        {
            char ch = arg[k];
            
            // Toggle single quote handling
            if (ch == '\'' && !in_double_quote)
                in_single_quote = !in_single_quote;
            // Toggle double quote handling
            else if (ch == '"' && !in_single_quote)
                in_double_quote = !in_double_quote;
            else
            {
                if (in_single_quote || in_double_quote || (ch != '\'' && ch != '"'))
                    new_arg[j++] = ch; // Only copy non-quote characters.
            }
        }
        new_arg[j] = '\0';

        // Free the old argument and replace it with the new one
        free(shell->args[i]);
        shell->args[i] = new_arg;

        i++;
    }
}

void handle_redirections(t_shell *shell)
{
    int i = 0;
    while (shell->args[i])
    {
        if (strcmp(shell->args[i], ">") == 0) // Output redirection
        {
            int fd = open(shell->args[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
            if (fd == -1)
            {
                perror("open");
            }
            else
            {
                printf("Redirecting output to: %s\n", shell->args[i + 1]); // Debug print
                dup2(fd, STDOUT_FILENO);  // Redirect stdout
                close(fd);
                shell->args[i] = NULL;    // Remove redirection part from args
                break; // Once redirection is handled, exit loop
            }
        }
        else if (strcmp(shell->args[i], ">>") == 0) // Append mode
        {
            int fd = open(shell->args[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
            if (fd == -1)
            {
                perror("open");
            }
            else
            {
                printf("Appending output to: %s\n", shell->args[i + 1]); // Debug print
                dup2(fd, STDOUT_FILENO);  // Redirect stdout in append mode
                close(fd);
                shell->args[i] = NULL;    // Remove redirection part from args
                break; // Once redirection is handled, exit loop
            }
        }
        else if (strcmp(shell->args[i], "<") == 0) // Input redirection
        {
            int fd = open(shell->args[i + 1], O_RDONLY);
            if (fd == -1)
            {
                perror("open");
            }
            else
            {
                printf("Redirecting input from: %s\n", shell->args[i + 1]); // Debug print
                dup2(fd, STDIN_FILENO);  // Redirect stdin
                close(fd);
                shell->args[i] = NULL;    // Remove redirection part from args
                break; // Once redirection is handled, exit loop
            }
        }
        else if (strcmp(shell->args[i], "<<") == 0) // Here-document
        {
            char *delimiter = shell->args[i + 1];
            int pipefd[2];
            pipe(pipefd);

            // Debug print for delimiter
            printf("Starting here-document with delimiter: '%s'\n", delimiter); // Debug print

            char *line;
            while ((line = readline("> ")) != NULL)
            {
                // Remove trailing newline from line before comparison
                line[strcspn(line, "\n")] = 0;

                // Compare the trimmed line with the delimiter
                if (strcmp(line, delimiter) == 0)
                    break;  // Break when the delimiter is matched

                // Write the input line to the pipe
                write(pipefd[1], line, strlen(line));  
                write(pipefd[1], "\n", 1);  // Add newline after each line
                free(line);
            }

            close(pipefd[1]);  // Close the pipe's writing end
            dup2(pipefd[0], STDIN_FILENO);  // Redirect stdin from the pipe's reading end
            close(pipefd[0]);  // Close the pipe's reading end
            shell->args[i] = NULL;    // Remove here-doc part from args
            break; // Once here-document redirection is handled, exit loop
        }

        i++;
    }
}

// Function to execute built-in commands
void execute_builtin(t_shell *shell)
{
    if (ft_strcmp(shell->args[0], "exit") == 0)
        exit(0);
    else if (ft_strcmp(shell->args[0], "cd") == 0)
        ft_cd(shell, shell->args);
    else if (ft_strcmp(shell->args[0], "pwd") == 0)
        ft_pwd();
    else if (ft_strcmp(shell->args[0], "export") == 0)
        ft_export(shell, shell->args);
    else if (ft_strcmp(shell->args[0], "unset") == 0)
        ft_unset(shell, shell->args);
    else if (ft_strcmp(shell->args[0], "env") == 0)
        ft_env(shell->env);
    else if (ft_strcmp(shell->args[0], "echo") == 0)      
	ft_echo(shell->args);
}

void execute_command(t_shell *shell)
{
    if (!shell->args || !shell->args[0])
        return;

    // Check if it's a built-in command
    if (is_builtin(shell->args[0]))
    {
        // Execute the corresponding built-in command
        execute_builtin(shell);
    }
    else
    {
        // Handle redirections before execution
        handle_redirections(shell);

        pid_t pid = fork();
        if (pid == 0)
        {
            // Execute external command
            execvp(shell->args[0], shell->args);
            perror("minishell");
            exit(127);
        }
        else
            waitpid(pid, NULL, 0);
    }
}

void execute_pipeline(t_shell *shell, char **cmds)
{
    int i = 0, fd[2], in_fd = 0;
    pid_t pid;

    while (cmds[i])
    {
        pipe(fd);  // Create a pipe for the current command
        if ((pid = fork()) == 0)  // Child process
        {
            dup2(in_fd, STDIN_FILENO);  // Redirect stdin to previous pipe output (if any)
            if (cmds[i + 1])  // If there's another command in the pipeline
                dup2(fd[1], STDOUT_FILENO);  // Redirect stdout to the current pipe

            close(fd[0]);  // Close the read end of the pipe in the child
            execute_command(shell);  // Execute the current command
            exit(0);  // Child process exits
        }
        else  // Parent process
        {
            close(fd[1]);  // Close the write end of the current pipe
            in_fd = fd[0];  // Update in_fd to read from the current pipe for the next command
            i++;
        }
    }
    while (wait(NULL) > 0);  // Wait for all child processes to terminate
}
