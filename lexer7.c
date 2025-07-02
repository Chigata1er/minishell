/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer7.c                                       	:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:11:05 by ibyeo             #+#    #+#             */
/*   Updated: 2025/04/03 10:09:06 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_invalid_and_usage(const char *line)
{
	const char	*p;
	int			and_count;

	p = skip_spacess(line);
	while (*p)
	{
		if (*p == '&')
		{
			and_count = 0;
			while (*p == '&')
			{
				and_count++;
				p++;
			}
			if (and_count >= 2)
			{
				p = skip_spacess(p);
				if (*p == '\0' || *p == '&' || *p == '|')
					return (1);
			}
		}
		else
			p++;
	}
	return (0);
}

char	*handle_null_line(t_env *env)
{
	printf("exit\n");
	rl_clear_history();
	env->exit_status = 0;
	exit(env->exit_status);
}

char	*free_and_null(char *line)
{
	free(line);
	return (NULL);
}

int	check_redirection_syntax(char *line)
{
	int	err;

	err = redirection_syntax_error_token(line);
	if (err == 1)
		printf("minishell: syntax error near unexpected token `>'\n");
	else if (err == 2)
		printf("minishell: syntax error near unexpected token `>>'\n");
	else if (err == 3)
		printf("minishell: syntax error near unexpected token `<'\n");
	if (err)
		return (free_and_null(line), 1);
	return (0);
}

int	check_quote_and_special_tokens(char *line, t_env *env)
{
	if (has_unclosed_quote(line))
	{
		printf("minishell: syntax error: unclosed quote\n");
		env->exit_status = 2;
		return (free_and_null(line), 1);
	}
	if (ft_strcmp(line, "<") == 0 || ft_strcmp(line, ">") == 0
		|| ft_strcmp(line, "<<") == 0 || ft_strcmp(line, ">>") == 0
		|| ft_strcmp(line, "<>") == 0)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		env->exit_status = 2;
		return (free_and_null(line), 1);
	}
	if (has_invalid_heredoc(line))
	{
		printf("minishell: syntax error near unexpected token `<<'\n");
		env->exit_status = 2;
		return (free_and_null(line), 1);
	}
	return (0);
}
