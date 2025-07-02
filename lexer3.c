/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                       	:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:11:05 by ibyeo             #+#    #+#             */
/*   Updated: 2025/04/03 10:09:06 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// These are the helper functions of 'ft_drop_quotes' function

int	process_quote_or_dollar(const char **input, t_env *envv,
		char **result)
{
	if (**input == '\'')
	{
		if (!handle_single_quotes(input, result))
			return (0);
	}
	else if (**input == '$' && *(*input + 1) == '"')
	{
		(*input)++;
	}
	else if (**input == '"')
	{
		if (!handle_quoted_expansion(input, envv, result, '"'))
			return (0);
	}
	else if (**input == '$')
	{
		if (!handle_dollar_sign(input, envv, result))
			return (0);
	}
	return (1);
}

int	process_expansion_loop(const char *input, t_env *envv,
		char **result)
{
	while (*input)
	{
		if (!process_quote_or_dollar(&input, envv, result))
			return (0);
		if (!process_remaining_text(&input, result))
			return (0);
	}
	return (1);
}

char	*expand_variables(const char *input, t_env *envv)
{
	char	*result;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	if (!process_expansion_loop(input, envv, &result))
		return (NULL);
	return (result);
}

char	**ft_drop_quotes(char **arg, t_env *env)
{
	int		i;
	char	*expanded;

	if ((ft_strcmp(arg[0], "export") == 0) && (arg[1] && (ft_strcmp(arg[1],
					"\"\"") == 0 || ft_strcmp(arg[1], "''") == 0)))
	{
		return (arg);
	}
	if (!arg)
		return (NULL);
	i = 0;
	while (arg[i])
	{
		expanded = expand_variables(arg[i], env);
		free(arg[i]);
		arg[i] = expanded;
		i++;
	}
	return (arg);
}
