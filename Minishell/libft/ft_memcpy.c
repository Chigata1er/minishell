/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:28:21 by thitran           #+#    #+#             */
/*   Updated: 2024/11/04 09:28:52 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*char_dest;
	const unsigned char	*char_src;

	char_dest = (unsigned char *)dest;
	char_src = (const unsigned char *)src;
	if (dest == NULL && src == NULL)
		return (dest);
	i = 0;
	while (i < n)
	{
		char_dest[i] = char_src[i];
		i++;
	}
	return (dest);
}
/*
int	main(void)
{
	char	dest[6] = "";
	char	src[] = "Hello";

	ft_memcpy(dest, src, 6);
	printf("Result after copying: %s\n", dest);
	return (0);
}
*/
