/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:11:02 by thitran           #+#    #+#             */
/*   Updated: 2024/11/04 09:11:21 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	str_len;

	i = 0;
	str_len = 0;
	while (src[str_len] != '\0')
	{
		str_len++;
	}
	if (size > 0)
	{
		while (src[i] != '\0' && i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (str_len);
}
/*
int	main(void)
{
	size_t		result;
	const char	src[] = "Hello world";                     
	char		dest[6];

	result = ft_strlcpy(dest, src, 6);
	printf("The source string: %s\n", src);
	printf("The destination string of 6 characters: %s\n", dest);
	printf("The length of source string is: %ld\n", result);
	return (0);
}
*/
