/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:14:46 by thitran           #+#    #+#             */
/*   Updated: 2024/11/04 09:15:05 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	if (*little == '\0')
	{
		return ((char *)big);
	}
	while (*big && len > 0)
	{
		if (*big == *little)
		{
			i = 0;
			while (little[i] != '\0' && big[i] == little[i] && i < len)
			{
				i++;
			}
			if (little[i] == '\0')
			{
				return ((char *)big);
			}
		}
		big++;
		len--;
	}
	return (NULL);
}
/*
int	main(void)
{
	char	str1[] = "Hope to see you again";
	char	str2[] = "Hope";
	char	*result;

	result = ft_strnstr(str1, str2, 4);
	if (result != NULL)
	{
		printf("The string found out is: %s", result);
	}
	else
	{
		printf("The string 2 is not found out in the string 1");
	}
	return (0);
}
*/
