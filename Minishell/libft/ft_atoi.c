/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 08:58:18 by thitran           #+#    #+#             */
/*   Updated: 2024/11/07 14:51:31 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>

static int	skip_whitespace_and_sign(char const *str, int *sign)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
	{
		i++;
	}
	if (str[i] == '-')
	{
		*sign = -1;
		i++;
	}
	else if (str[i] == '+')
	{
		i++;
	}
	return (i);
}

int	ft_atoi(char const *str)
{
	int	i;
	int	result;
	int	sign;

	sign = 1;
	result = 0;
	i = skip_whitespace_and_sign(str, &sign);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}
/*
int	main(void)
{
	char	str[] = "   --++---123456";

	printf("The integer value is %d\n", ft_atoi(str));
	return (0);
}
*/
