/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:33:17 by thitran           #+#    #+#             */
/*   Updated: 2024/11/07 16:08:18 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>

char	*ft_strchr(const char *str, int c)
{
	unsigned char	ch;

	ch = (unsigned char)c;
	while (*str)
	{
		if ((unsigned char)*str == ch)
		{
			return ((char *)str);
		}
		str++;
	}
	if (ch == '\0')
		return ((char *)str);
	return (NULL);
}
/*
int	main(void)
{
	const char	str[] = "Hello, World";
	char		*ptr;

	ptr = ft_strchr(str, 'W');
	if (ptr != NULL)
	{
		printf("Character found at position: %td\n", ptr - str);
	}
	else
	{
		printf("Character not found.\n");
	}
	return (0);
}
*/
