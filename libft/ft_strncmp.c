/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:13:24 by thitran           #+#    #+#             */
/*   Updated: 2024/11/04 09:14:02 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i] && i < n - 1)
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
/*
int	main(void)
{
	const char	s1[] = "Hello world";
	const char	s2[] = "I love you";
	int		result;
	size_t		n = 6;

	result = ft_strncmp(s1, s2, n);
	if (result > 0)
	{
		printf("S1 is greater than S2 compared %ld letters: %d\n", n, result);
	}
	else if (result < 0)
	{
		printf("S1 is smaller than S2 compared %ld letters: %d\n", n, result);
	}
	else
	{
		printf("S1 and S2 are equal compared %ld letters: %d\n", n, result);
	}
	return (0);
}
*/
