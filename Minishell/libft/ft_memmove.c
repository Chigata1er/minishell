/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:29:34 by thitran           #+#    #+#             */
/*   Updated: 2024/11/04 09:29:59 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*char_dest;
	const char	*char_src;

	if (dest == NULL && src == NULL)
		return (NULL);
	if (n == 0)
		return (dest);
	char_dest = (char *)dest;
	char_src = (const char *)src;
	if (char_dest > char_src)
	{
		while (n--)
		{
			char_dest[n] = char_src[n];
		}
	}
	else
	{
		while (n--)
		{
			*char_dest++ = *char_src++;
		}
	}
	return (dest);
}
/*
int	main(void)
{
	char	dest[] = "Hello World";
	char	src[] = "Hi";

	ft_memmove(dest, src, 2);
	printf("Result after moving: %s\n", dest);
	return (0);
}
*/
