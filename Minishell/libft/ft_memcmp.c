/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:23:50 by thitran           #+#    #+#             */
/*   Updated: 2024/11/04 09:24:29 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	size_t				i;
	const unsigned char	*char_ptr1;
	const unsigned char	*char_ptr2;

	i = 0;
	char_ptr1 = (const unsigned char *)ptr1;
	char_ptr2 = (const unsigned char *)ptr2;
	while (i < num)
	{
		if (char_ptr1[i] != char_ptr2[i])
			return (char_ptr1[i] - char_ptr2[i]);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	char	str1[] = "Hello";
	char	str2[] = "Hello World";
	int		result;

	result = ft_memcmp(str1, str2, 5);
	if (result == 0)
	{
		printf("str1 and str2 are equal");
	}
	else if (result > 0)
	{
		printf("str1 greater than str2");
	}
	else
	{
		printf("str1 less than str2");
	}
	return (0);
}
*/
