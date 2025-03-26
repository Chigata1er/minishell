/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:33:12 by thitran           #+#    #+#             */
/*   Updated: 2024/11/07 13:27:50 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

static char	*allocate_substr(size_t len)
{
	char	*substr;

	substr = (char *)malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	substr[len] = '\0';
	return (substr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*substr;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		return (ft_strdup(""));
	}
	if (len > s_len - start)
		len = s_len - start;
	substr = allocate_substr(len);
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
/*
int	main(void)
{
	const char	*s = "Hello world! Welcome to 42 Nice";
	char	*result;
	unsigned int		start;
	size_t		len;

	start = 13;
	len = 7;
	result = ft_substr(s, start, len);
	if (result)
	{
		printf("The result is: %s\n", result);
		free(result);
	}
	else
	{
		printf("Failed to create substring.\n");
	}
	return (0);
}
*/
