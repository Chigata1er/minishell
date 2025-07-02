/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                      	:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:11:05 by ibyeo             #+#    #+#             */
/*   Updated: 2025/04/03 10:09:06 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	append_segment(const char **input, char **result, size_t len)
{
	char	*segment;
	char	*tmp;

	segment = ft_strndup(*input, len);
	if (!segment)
		return (0);
	tmp = ft_strjoin(*result, segment);
	free(segment);
	free(*result);
	*result = tmp;
	if (!*result)
		return (0);
	*input += len;
	return (1);
}

int	handle_single_quotes(const char **input, char **result)
{
	const char	*start;
	size_t		len;

	(*input)++;
	start = *input;
	while (**input && **input != '\'')
		(*input)++;
	len = *input - start;
	if (!append_segment(&start, result, len))
		return (0);
	if (**input == '\'')
		(*input)++;
	return (1);
}

int	handle_quoted_expansion(const char **input, t_env *envv,
		char **result, char quote)
{
	size_t		i;
	const char	*start;

	(*input)++;
	while (**input && **input != quote)
	{
		if (**input == '$')
		{
			if (!handle_dollar_sign(input, envv, result))
				return (0);
		}
		else
		{
			start = *input;
			i = 0;
			while (start[i] && start[i] != '$' && start[i] != quote)
				i++;
			if (!append_segment(input, result, i))
				return (0);
		}
	}
	if (**input == quote)
		(*input)++;
	return (1);
}

int	handle_plain_text(const char **input, char **result)
{
	const char	*start;
	size_t		i;

	start = *input;
	i = 0;
	while (start[i] && start[i] != '$'
		&& start[i] != '\''
		&& start[i] != '"'
		&& !(start[i] == ' '
			|| ((unsigned char)start[i] >= 9
				&& (unsigned char)start[i] <= 13)))
	{
		i++;
	}
	return (append_segment(input, result, i));
}

int	process_remaining_text(const char **input, char **result)
{
	if (**input && **input != '\'' && **input != '"' && **input != '$')
	{
		if (!handle_plain_text(input, result))
			return (0);
	}
	return (1);
}
