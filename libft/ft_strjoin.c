/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:35:13 by thitran           #+#    #+#             */
/*   Updated: 2024/11/04 11:37:53 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

static char	*ft_strcat(char *dest, char const *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

static int	calculate_total_len(char const *s1, char const *s2)
{
	int	len;

	len = 0;
	if (s1 != NULL)
		len += ft_strlen(s1);
	if (s2 != NULL)
		len += ft_strlen(s2);
	return (len);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;
	int		total_len;

	total_len = calculate_total_len(s1, s2);
	result = (char *)malloc(total_len + 1);
	if (result == NULL)
		return (NULL);
	result[0] = '\0';
	if (s1 != NULL)
		ft_strcat(result, (char *)s1);
	if (s2 != NULL)
		ft_strcat(result, (char *)s2);
	return (result);
}
/*
int	main(void)
{
	char	*s1 = "Hello world!";
	char	*s2 = " What are you doing today?";
	char	*result;

	result = ft_strjoin(s1, s2);
	if (result != NULL)
	{
		printf("The result string is: %s\n", result);
		free(result);
	}
	return (0);
}
*/
