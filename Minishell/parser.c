/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:09:34 by thitran           #+#    #+#             */
/*   Updated: 2025/03/20 09:09:55 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void expand_variables(t_shell *shell)
{
    for (int i = 0; shell->args[i]; i++)
    {
        if (shell->args[i][0] == '$') // Check for variable prefix
        {
            char *var_name = shell->args[i] + 1; // Skip '$'
            char *value = NULL;

            if (var_name[0] == '?' && var_name[1] == '\0') // Special case for $?
            {
                asprintf(&value, "%d", shell->last_exit_status); // Convert exit status to string
            }
            else
            {
                value = getenv(var_name); // Get environment variable value
            }

            if (value)
            {
                free(shell->args[i]);         // Free old memory
                shell->args[i] = strdup(value); // Replace with expanded value
            }
        }
    }
}

void parse_input(t_shell *shell)
{
    int i = 0, j = 0, k = 0;
    char **args;
    char *input = shell->input;

    args = malloc(sizeof(char *) * 100);  // Allocate space for 100 arguments
    if (!args)
    {
        perror("malloc");
        return;
    }

    while (input[i])
    {
        while (input[i] == ' ') // Skip spaces
            i++;
        
        if (!input[i]) // End of input
            break;

        args[j] = malloc(sizeof(char) * 256); // Adjust buffer size as needed
        if (!args[j])
        {
            perror("malloc");
            return;
        }

        k = 0;
        while (input[i] && input[i] != ' ') // Copy argument until space
            args[j][k++] = input[i++];

        args[j][k] = '\0'; // Null-terminate argument
        j++;
    }

    args[j] = NULL; // Null-terminate argument list
    shell->args = args;

    expand_variables(shell); // Expand environment variables
}

