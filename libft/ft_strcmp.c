/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:36:29 by thitran           #+#    #+#             */
/*   Updated: 2024/09/18 17:16:19 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] != '\0' && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}
/*
int	main(void)
{
	char	s1[] = "Hello world";
	char	s2[] = "I love you";
	int		result;

	result = ft_strcmp(s1, s2);
	if (result > 0)
	{
		printf("S1 is greater than S2 (%d)\n", result);
	}
	else if (result < 0)
	{
		printf("S1 is smaller than S2 (%d)\n", result);
	}
	else
	{
		printf("S1 and S2 are equal (%d)\n", result);
	}
	return (0);
}
*/
