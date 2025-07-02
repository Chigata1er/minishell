/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:11:05 by ibyeo             #+#    #+#             */
/*   Updated: 2025/04/03 10:09:06 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_invalid_identifier(t_env *env, char *str)
{
	write(2, "minishell: export: `", 21);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 27);
	env->exit_status = 1;
	return (1);
}

void	process_valid_export(t_env *env, char *str)
{
	t_node	*current;
	char	*equal_sign;
	size_t	key_len;
	int		found;

	current = env->top;
	equal_sign = ft_strchr(str, '=');
	if (!equal_sign)
		key_len = ft_strlen(str);
	else
		key_len = equal_sign - str;
	found = update_existing_var(current, str, key_len);
	if (!found)
		add_new_var(env, str);
}

void	ft_push(t_env *env, char *str)
{
	char	*updated_str;

	if (ft_strcmp(str, "\"\"") == 0 || ft_strcmp(str, "''") == 0)
	{
		printf("minishell: export: `': not a valid identifier\n");
		return ;
	}
	if (!str || str[0] == '\0' || !is_valid_export_identifier(str))
	{
		handle_invalid_identifier(env, str);
		return ;
	}
	if ((is_valid_export_identifier(str) == 2))
	{
		updated_str = export_with_plus(str, env);
		str = ft_strdup(updated_str);
		free(updated_str);
	}
	process_valid_export(env, str);
}

int	is_valid_unset_identifier(const char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

int	ft_drop_error_if_invalid(t_env *env, char *str)
{
	if (!str || !*str || !is_valid_unset_identifier(str))
	{
		write(2, "minishell: unset: `", 19);
		write(2, str, ft_strlen(str));
		write(2, "': not a valid identifier\n", 27);
		env->exit_status = 1;
		return (1);
	}
	return (0);
}
