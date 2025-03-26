/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:17:26 by thitran           #+#    #+#             */
/*   Updated: 2024/11/04 09:18:16 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		c = c - 32;
	}
	return (c);
}
/*
int	main(void)
{
	char	lower = 'a';
	char	upper = ft_toupper(lower);

	printf(" The uppercase of '%c' is '%c'.\n", lower, upper);
	lower = 'A';
	upper = ft_toupper(lower);

	printf("The uppercase of '%c' is '%c'.\n", lower, upper);
	return (0);
}
*/
