/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:09:25 by thitran           #+#    #+#             */
/*   Updated: 2024/11/07 09:31:09 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;

	i = 0;
	dest_len = 0;
	src_len = 0;
	while (dest[dest_len] != '\0')
		dest_len++;
	while (src[src_len] != '\0')
		src_len++;
	if (size <= dest_len)
		return (size + src_len);
	while (src[i] != '\0' && dest_len + i < size - 1)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}
/*
int	main(void)
{
	const char	src[] = "Lien";
	char		dest[20] = "Kim ";
	size_t		result;
	size_t		n;

	n = sizeof(dest);
	result = ft_strlcat(dest, src, n);
	printf("The destination string is: %s\n", dest);
	printf("The total length is: %zu\n", result);
	return (0);
}
*/
