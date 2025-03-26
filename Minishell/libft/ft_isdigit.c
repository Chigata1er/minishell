/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:05:13 by thitran           #+#    #+#             */
/*   Updated: 2024/11/04 09:05:40 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h> 

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
/*
int	main(void)
{
	printf("Is '1' a digit? %d\n", ft_isdigit('1'));
	printf("Is '2' a digit? %d\n", ft_isdigit('2'));
	printf("Is '3' a digit? %d\n", ft_isdigit('3'));
	printf("Is 'a' a digit? %d\n", ft_isdigit('a'));
	printf("Is '@' a digit? %d\n", ft_isdigit('@'));
	return (0);
}
*/
