/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:01:55 by thitran           #+#    #+#             */
/*   Updated: 2024/11/04 09:03:07 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>

int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}
/*
int	main(void)
{
	char	c1 = 'A';
	char	c2 = '1';
	char	c3 = 'g';

	printf("Is '%c' alphabetic? %d\n", c1, ft_isalpha(c1));
	printf("Is '%c' alphabetic? %d\n", c2, ft_isalpha(c2));
	printf("Is '%c' alphabetic? %d\n", c3, ft_isalpha(c3));
	return (0);
}
*/
