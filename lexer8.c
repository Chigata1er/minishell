/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer8.c                                       	:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:11:05 by ibyeo             #+#    #+#             */
/*   Updated: 2025/04/03 10:09:06 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_logic_operator_syntax(char *line, t_env *env)
{
	if (has_invalid_or_usage(line))
	{
		printf("minishell: syntax error near unexpected token `||'\n");
		env->exit_status = 2;
		return (free_and_null(line), 1);
	}
	if (has_invalid_pipe_syntax(line))
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		env->exit_status = 2;
		return (free_and_null(line), 1);
	}
	if (has_invalid_and_usage(line))
	{
		printf("minishell: syntax error near unexpected token `&&'\n");
		env->exit_status = 2;
		return (free_and_null(line), 1);
	}
	return (0);
}

char	*read_full_line(t_env *env)
{
	char	*line;

	line = readline("minishell$ ");
	if (!line)
		return (handle_null_line(env));
	if (ft_strcmp(line, ":") == 0 || ft_strcmp(line, "!") == 0)
		return (free_and_null(line));
	if (check_redirection_syntax(line))
		return (NULL);
	if (check_quote_and_special_tokens(line, env))
		return (NULL);
	if (check_logic_operator_syntax(line, env))
		return (NULL);
	return (line);
}
