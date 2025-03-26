/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:08:00 by thitran           #+#    #+#             */
/*   Updated: 2024/11/04 09:08:29 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		len;
	int		i;
	char	*dup;

	len = ft_strlen(src);
	dup = (char *)malloc((len + 1) * sizeof(char));
	if (dup == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
/*
int	main(void)
{
	char	src[] = "Hello, world";
	char	*dest;

	dest = ft_strdup(src);
	if (dest != NULL)
	{
		printf("Destination string is: %s\n", dest);
	}
	else
	{
		printf("Memory allocation failed\n");
	}
	return (0);
}
*/
