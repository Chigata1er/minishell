/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 08:37:34 by thitran           #+#    #+#             */
/*   Updated: 2024/11/07 15:17:20 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <stdio.h>

static int	get_num_length(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
	{
		len = 1;
	}
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*allocate(int n)
{
	int		len;
	int		i;
	char	*s;

	len = get_num_length(n);
	s = (char *)malloc((len + 1) * sizeof(char));
	i = 0;
	if (s)
	{
		while (i <= len)
		{
			s[i] = '\0';
			i++;
		}
	}
	return (s);
}

static void	fill_str(char *str, long nb, int len)
{
	str[len] = '\0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	while (len-- > 0 && nb > 0)
	{
		if (str[len] == '-')
			break ;
		str[len] = (nb % 10) + '0';
		nb /= 10;
	}
}

char	*ft_itoa(int n)
{
	long	nb;
	char	*str;
	int		len;

	nb = n;
	len = get_num_length(nb);
	str = allocate(n);
	if (!str)
		return (NULL);
	if (nb == 0)
	{
		str[0] = '0';
		str[1] = '\0';
	}
	else
		fill_str(str, nb, len);
	return (str);
}
/*
int	main(void)
{
	int		n = 20;	
	char	*str;

	str = ft_itoa(n);
	if (str != NULL)
	{
		printf("The string is: %s\n", str);
		free(str);
	}
	return (0);
}
*/
