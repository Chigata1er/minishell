/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer5.c                                       	:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:11:05 by ibyeo             #+#    #+#             */
/*   Updated: 2025/04/03 10:09:06 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_double_gt(const char *line, int *i)
{
	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		*i += 2;
		while (line[*i] && ft_isspace(line[*i]))
			(*i)++;
		if (line[*i] == '>' && line[*i + 1] == '>')
			return (1);
	}
	return (0);
}

int	check_single_gt(const char *line, int *i, int *count)
{
	while (line[*i])
	{
		if (line[*i] == '>' && line[*i + 1] != '>')
		{
			(*count)++;
			(*i)++;
			while (line[*i] && ft_isspace(line[*i]))
				(*i)++;
			if (line[*i] == '>' && line[*i + 1] != '>')
				return (1);
		}
		else
			break ;
	}
	return (0);
}

int	check_single_gtt(const char *line, int *i, int *count)
{
	while (line[*i])
	{
		if (line[*i] == '<' && line[*i + 1] != '<')
		{
			(*count)++;
			(*i)++;
			while (line[*i] && ft_isspace(line[*i]))
				(*i)++;
			if (line[*i] == '<' && line[*i + 1] != '<')
				return (1);
		}
		else
			break ;
	}
	return (0);
}

int	redirection_syntax_error_token(const char *line)
{
	int	i;
	int	single_gt_count;

	i = 0;
	single_gt_count = 0;
	while (line[i])
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (check_double_gt(line, &i))
			return (2);
		else if (check_single_gt(line, &i, &single_gt_count))
			return (1);
		else if (check_single_gtt(line, &i, &single_gt_count))
			return (3);
		else
		{
			single_gt_count = 0;
			i++;
		}
	}
	return (0);
}

int	has_invalid_heredoc(const char *line)
{
	int	i;
	int	count;

	i = 0;
	while (line[i])
	{
		if (line[i] == '<')
		{
			count = 0;
			while (line[i] == '<')
			{
				count++;
				i++;
			}
			if (count >= 3)
				return (1);
		}
		else
			i++;
	}
	return (0);
}
