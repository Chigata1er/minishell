/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                      	:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:11:05 by ibyeo             #+#    #+#             */
/*   Updated: 2025/04/03 10:09:06 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

size_t	skip_spaces(const char *input, size_t i)
{
	while (input[i] == ' ' || input[i] == '\t' || input[i] == '\n'
		|| input[i] == '\v' || input[i] == '\f' || input[i] == '\r')
		i++;
	return (i);
}

size_t	handle_quotes(const char *input, size_t i, char *quote)
{
	while (input[i])
	{
		if (!*quote && (input[i] == '\'' || input[i] == '"'))
			*quote = input[i++];
		else if (*quote && input[i] == *quote)
		{
			i++;
			*quote = 0;
		}
		else if (!*quote && input[i] == ' ')
			break ;
		else
			i++;
	}
	return (i);
}

char	*extract_argument(const char *input, size_t start, size_t end)
{
	return (ft_strndup(&input[start], end - start));
}

char	**ft_split_args(const char *input)
{
	size_t		i;
	size_t		k;
	char		**args;
	char		quote;
	size_t		start;

	i = 0;
	k = 0;
	args = malloc(256 * sizeof(char *));
	quote = 0;
	if (!args)
		return (NULL);
	while (input[i])
	{
		i = skip_spaces(input, i);
		if (!input[i])
			break ;
		start = i;
		i = handle_quotes(input, i, &quote);
		args[k++] = extract_argument(input, start, i);
	}
	args[k] = NULL;
	return (args);
}
