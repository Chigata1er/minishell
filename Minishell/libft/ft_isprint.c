/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:06:36 by thitran           #+#    #+#             */
/*   Updated: 2024/11/04 09:06:59 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}
/*
int	main(void)
{
	char	c = '@';

	if (ft_isprint(c))
	{
		printf("%c is printable.\n", c);
	}
	else
	{
		printf("%c is not printable.\n", c);
	}
	return (0);
}
*/
