/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:22:47 by thitran           #+#    #+#             */
/*   Updated: 2024/11/04 09:23:12 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t				i;
	const unsigned char	*char_str;

	i = 0;
	char_str = (const unsigned char *)str;
	while (i < n)
	{
		if (char_str[i] == (unsigned char)c)
		{
			return ((void *)(char_str + i));
		}
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	char	str[] = "Hello World";
	char	c = 'W';
	char	*ptr;

	ptr = ft_memchr(str, c, 11);
	if (ptr)
	{
		printf("Position of %c is: %d\n", c, ptr - str);
	}
	else
	{
		printf("%c is not found.\n", c);
	}
	return (0);
}
*/
