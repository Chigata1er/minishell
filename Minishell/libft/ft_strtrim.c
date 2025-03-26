/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 08:45:20 by thitran           #+#    #+#             */
/*   Updated: 2024/11/07 08:45:49 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

static int	is_in_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set++)
		{
			return (1);
		}
	}
	return (0);
}

static int	get_trim_start(char const *s1, char const *set)
{
	int	start;

	start = 0;
	while (s1[start] && is_in_set(s1[start], set))
		start++;
	return (start);
}

static int	get_trim_end(char const *s1, char const *set, int start)
{
	int	end;

	end = 0;
	while (s1[end])
		end++;
	end--;
	while (end > start && is_in_set(s1[end], set))
		end--;
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		i;
	char	*trimmed;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	start = get_trim_start(s1, set);
	end = get_trim_end(s1, set, start);
	trimmed = (char *)malloc((end - start + 2) * sizeof(char));
	if (!trimmed)
		return (NULL);
	i = 0;
	while (start <= end)
	{
		trimmed[i++] = s1[start++];
	}
	trimmed[i] = '\0';
	return (trimmed);
}
/*
int	main(void)
{
	char	*s1 = " ?Hello? ";
	char	*set = " ?";
	char	*strtrim;

	strtrim = ft_strtrim(s1, set);
	if (strtrim != NULL)
	{
		printf("The trimmed string is: %s\n", strtrim);
		free(strtrim);
	}
	return (0);
}
*/
