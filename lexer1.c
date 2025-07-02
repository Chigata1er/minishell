/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                       	:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:11:05 by ibyeo             #+#    #+#             */
/*   Updated: 2025/04/03 10:09:06 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(const char *key, t_env *env)
{
	t_node	*node;
	size_t	key_len;

	node = env->top;
	key_len = ft_strlen(key);
	while (node)
	{
		if (ft_strncmp(node->value, key, key_len) == 0
			&& node->value[key_len] == '=')
			return (node->value + key_len + 1);
		node = node->next;
	}
	return (NULL);
}

char	*extract_variable_name(const char *input, size_t *i)
{
	size_t	start;
	size_t	var_len;
	char	*var_name;

	start = *i;
	while (ft_isalnum(input[*i]) || input[*i] == '_')
		(*i)++;
	var_len = *i - start;
	var_name = ft_strndup(&input[start], var_len);
	return (var_name);
}

char	*expand_variable(const char *input, size_t *i,
	t_env *envv, char *result)
{
	char	*var_name;
	char	*value;
	char	*tmp;

	var_name = extract_variable_name(input, i);
	if (!var_name)
		return (NULL);
	if (var_name[0] == '\0')
	{
		free(var_name);
		return (result);
	}
	value = get_env_value(var_name, envv);
	if (value)
		tmp = ft_strjoin(result, value);
	else
		tmp = ft_strjoin(result, "");
	free(var_name);
	if (!tmp)
	{
		free(result);
		return (NULL);
	}
	free(result);
	return (tmp);
}

char	*str_append_char(char *str, char c)
{
	size_t		len;
	char		*new_str;

	if (!str)
		len = 0;
	else
		len = ft_strlen(str);
	new_str = malloc(len + 2);
	if (!new_str)
		return (NULL);
	if (str)
		ft_memcpy(new_str, str, len);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	free(str);
	return (new_str);
}

int	handle_dollar_sign(const char **input, t_env *envv, char **result)
{
	size_t		i;
	const char	*start;

	(*input)++;
	if (**input == '?')
	{
		(*input)++;
		*result = handle_exit_status(*result, envv->exit_status);
	}
	else if (**input == '\0' || (!ft_isalnum(**input) && **input != '_'))
	{
		*result = str_append_char(*result, '$');
	}
	else
	{
		i = 0;
		start = *input;
		*result = expand_variable(start, &i, envv, *result);
		*input += i;
	}
	return (*result != NULL);
}
