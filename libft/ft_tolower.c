/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:15:59 by thitran           #+#    #+#             */
/*   Updated: 2024/11/04 09:16:22 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
	{
		c = c + 32;
	}
	return (c);
}
/*
int	main(void)
{
	char	upper = 'A';
	char	lower = ft_tolower(upper);

	printf("The lowercase of '%c' is '%c'.\n", upper, lower);
	upper = 'a';
	lower = ft_tolower(upper);
	printf("The lowercase of '%c' is '%c'.\n", upper, lower);
	return (0);
}
*/
