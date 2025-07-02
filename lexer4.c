/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer4.c                                       	:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:11:05 by ibyeo             #+#    #+#             */
/*   Updated: 2025/04/03 10:09:06 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_unclosed_quote(const char *str)
{
	char	quote;

	quote = 0;
	while (*str)
	{
		if (!quote && (*str == '\'' || *str == '"'))
			quote = *str;
		else if (quote && *str == quote)
			quote = 0;
		str++;
	}
	return (quote != 0);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;

	dup = malloc(n + 1);
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s, n);
	dup[n] = '\0';
	return (dup);
}

int	ft_isspace(char c)
{
	return (
		c == ' '
		|| c == '\t'
		|| c == '\n'
		|| c == '\v'
		|| c == '\f'
		|| c == '\r'
	);
}

const char	*skip_spacess(const char *str)
{
	while (*str && ft_isspace(*str))
		str++;
	return (str);
}

char	*handle_exit_status(char *result, int exit_status)
{
	char	*exit_str;
	char	*tmp;

	exit_str = ft_itoa(exit_status);
	if (!exit_str)
	{
		free(result);
		return (NULL);
	}
	tmp = ft_strjoin(result, exit_str);
	free(exit_str);
	if (!tmp)
	{
		free(result);
		return (NULL);
	}
	free(result);
	return (tmp);
}
