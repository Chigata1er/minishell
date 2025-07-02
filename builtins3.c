/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:11:05 by ibyeo             #+#    #+#             */
/*   Updated: 2025/05/19 16:03:58 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_strcpy3(char *dest, const char *s1, const char *s2, const char *s3)
{
	size_t	i;

	i = 0;
	if (s1)
		while (*s1)
			dest[i++] = *s1++;
	if (s2)
		while (*s2)
			dest[i++] = *s2++;
	if (s3)
		while (*s3)
			dest[i++] = *s3++;
	dest[i] = '\0';
}

char	*ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
	size_t	len1;
	size_t	len2;
	size_t	len3;
	size_t	total_len;
	char	*result;

	len1 = 0;
	len2 = 0;
	len3 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	if (s3)
		len3 = ft_strlen(s3);
	total_len = len1 + len2 + len3;
	result = malloc(total_len + 1);
	if (!result)
		return (NULL);
	ft_strcpy3(result, s1, s2, s3);
	return (result);
}

char	*export_with_plus(char *str, t_env *env)
{
	char	*key;
	char	*new_val;
	char	*old_val;
	char	*result;
	int		key_len;

	key_len = 0;
	while (str[key_len] && str[key_len] != '+' && str[key_len] != '=')
		key_len++;
	key = ft_substr(str, 0, key_len);
	old_val = get_env_value(key, env);
	if (!old_val)
		old_val = ft_strdup("");
	new_val = ft_strdup(ft_strchr(str, '=') + 1);
	result = ft_strjoin3(key, "=", ft_strjoin(old_val, new_val));
	free(new_val);
	return (result);
}

void	add_new_var(t_env *env, char *str)
{
	t_node	*new_node;
	char	*dup;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return ;
	dup = ft_strdup(str);
	if (!dup)
	{
		free(new_node);
		return ;
	}
	new_node->value = dup;
	new_node->next = env->top;
	env->top = new_node;
	env->size++;
}

int	is_valid_export_identifier(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	if (str[0] == '=')
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i + 1] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			if (str[i] == '+' && str[i + 1] == '=')
				return (2);
			return (0);
		}
		i++;
	}
	return (1);
}
