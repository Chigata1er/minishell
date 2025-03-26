/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:04:01 by thitran           #+#    #+#             */
/*   Updated: 2024/11/04 09:04:25 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
/*
int	main(void)
{
	char	c = 'A';

	if (ft_isascii(c))
	{
		printf("%c is an ASCII character.\n", c);
	}
	else
	{
		printf("%c is not an ASCII character.\n", c);
	}
	return (0);
}
*/
