/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:00:46 by thitran           #+#    #+#             */
/*   Updated: 2024/11/04 09:01:08 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>

int	ft_isalnum(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9'));
}
/*
int	main(void)
{
	char	c1 = 'A';
	char	c2 = '1';
	char	c3 = 'g';
	char	c4 = '@';

	printf("Is '%c' alphanumeric? %d\n", c1, ft_isalnum(c1));
	printf("Is '%c' alphanumeric? %d\n", c2, ft_isalnum(c2));
	printf("Is '%c' alphanumeric? %d\n", c3, ft_isalnum(c3));
	printf("Is '%c' alphanumeric? %d\n", c4, ft_isalnum(c4));
	return (0);
}
*/
