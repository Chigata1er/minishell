/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:11:05 by ibyeo             #+#    #+#             */
/*   Updated: 2025/04/03 10:09:06 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	fill_in_env(t_env *envv, char **str)
{
	int		i;
	t_node	*new_node;

	i = 0;
	while (str[i])
	{
		new_node = malloc(sizeof(t_node));
		if (!new_node)
			return ;
		new_node->value = ft_strdup(str[i]);
		new_node->next = envv->top;
		envv->top = new_node;
		envv->size++;
		i++;
	}
}

t_env	*init_env_struct(void)
{
	t_env	*env;
	int		j;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->size = 0;
	env->exit_status = 0;
	env->top = NULL;
	env->key = NULL;
	env->value = NULL;
	env->next = NULL;
	env->arg_count = 0;
	env->args = NULL;
	env->file_count = 0;
	j = 0;
	while (j < 100)
	{
		env->file[j] = -1;
		env->file_arg[j] = NULL;
		j++;
	}
	return (env);
}

t_env	*create_env_list(char **envp)
{
	t_env	*env;

	env = init_env_struct();
	if (!env)
		return (NULL);
	fill_in_env(env, envp);
	return (env);
}
