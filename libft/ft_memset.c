/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:31:09 by thitran           #+#    #+#             */
/*   Updated: 2024/11/04 09:31:24 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>

void	*ft_memset(void *ptr, int value, size_t num)
{
	size_t		i;
	char		*char_ptr;

	i = 0;
	char_ptr = (char *)ptr;
	while (i < num)
	{
		char_ptr[i] = (unsigned char)value;
		i++;
	}
	return (ptr);
}
/*
int	main(void)
{
	char	str[6] = "";
	char	*ptr;

	ptr = ft_memset(str, '0', 5);
	printf("Result after initilization: %s\n", ptr);
	return (0);
}
*/
