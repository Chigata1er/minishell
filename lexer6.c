/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer6.c                                       	:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:11:05 by ibyeo             #+#    #+#             */
/*   Updated: 2025/04/03 10:09:06 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_invalid_or_sequence(const char **p)
{
	int	or_count;

	or_count = 0;
	while (**p == '|')
	{
		or_count++;
		(*p)++;
	}
	if (or_count >= 2)
	{
		*p = skip_spacess(*p);
		if (**p == '\0' || **p == '|' || **p == '&')
			return (1);
		return (1);
	}
	return (0);
}

int	has_invalid_or_usage(const char *line)
{
	const char	*p;

	p = skip_spacess(line);
	while (*p)
	{
		if (*p == '|')
		{
			if (is_invalid_or_sequence(&p))
				return (2);
		}
		else
			p++;
	}
	return (0);
}

int	is_invalid_pipe_context(const char *line, int i)
{
	int	j;

	j = i + 1;
	while (line[j] && ft_isspace(line[j]))
		j++;
	if (line[j] == '\0' || line[j] == '|')
		return (1);
	if (i > 0 && (line[i - 1] == '>' || line[i - 1] == '<'))
		return (1);
	if (line[j] == '>' || line[j] == '<')
		return (1);
	return (0);
}

void	update_quote_state(char c, char *quote)
{
	if ((c == '\'' || c == '"'))
	{
		if (*quote == 0)
			*quote = c;
		else if (*quote == c)
			*quote = 0;
	}
}

int	has_invalid_pipe_syntax(const char *line)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] == '|')
		return (1);
	while (line[i])
	{
		update_quote_state(line[i], &quote);
		if (line[i] == '|' && quote == 0)
		{
			if (is_invalid_pipe_context(line, i))
				return (1);
		}
		i++;
	}
	return (0);
}
