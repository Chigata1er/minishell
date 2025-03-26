/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:19:42 by thitran           #+#    #+#             */
/*   Updated: 2024/11/04 09:20:14 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>

void	ft_bzero(void *s, size_t n)
{
	size_t		i;
	char		*char_s;

	i = 0;
	char_s = (char *)s;
	while (i < n)
	{
		char_s[i] = '\0';
		i++;
	}
}
/*
int	main(void)
{
	char	str[] = "Hello";

	ft_bzero(str, 4);
	printf("Result after setting: %s\n", str);
	printf("Individual characters after setting:\n");
	for (int i = 0; i < 5; i++)
	{
		printf("str[%d] = %c (ASCII: %d)\n", i, str[i], str[i]);
	}	
	return (0);
}
*/
