/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:08:49 by thitran           #+#    #+#             */
/*   Updated: 2025/03/20 09:09:10 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

void signal_handler(int sig)
{
    if (sig == SIGINT)
    {
        rl_on_new_line();  // Move to a new line when Ctrl+C is pressed
        rl_replace_line("", 0);  // Clear the current line
        rl_redisplay();  // Redraw the prompt
        write(1, "\nminishell$ ", 12);  // Reprint the prompt after Ctrl+C
    }
    else if (sig == SIGQUIT)
    {
        // Ignore Ctrl+\ (SIGQUIT)
	printf("Ignoring SIGQUIT (Ctrl+\\)\n");
    }
}

void init_shell(t_shell *shell, char **env)
{
    shell->env = env;  // Store the environment variables
    shell->input = NULL;
    shell->args = NULL;  // Initialize args to NULL
    shell->last_exit_status = 0;  // Initialize last exit status to 0
}

int main(int argc, char **argv, char **env)
{
    t_shell shell;

    (void)argc;
    (void)argv;
    init_shell(&shell, env);

    // Set signal handlers
    signal(SIGINT, signal_handler);  // Handle Ctrl+C
    signal(SIGQUIT, SIG_IGN);        // Ignore Ctrl+slash

    // Main shell loop
    while (1)
    {
        // Display the prompt and get input from the user
        shell.input = readline("minishell$ ");
        
        if (!shell.input)  // If user enters EOF or exits
            break;

        if (*shell.input)  // If there is some input (non-empty)
            add_history(shell.input);  // Add to the history

        parse_input(&shell);  // Parse the user input into arguments
	handle_redirections(&shell);
        if (shell.args)
            execute_command(&shell);  // Execute the command if arguments exist

        free(shell.input);  // Free the input buffer after processing
        shell.input = NULL;  // Reset input for the next iteration
    }

    // Exit cleanly (optional: free memory if needed)
    return (0);
}
