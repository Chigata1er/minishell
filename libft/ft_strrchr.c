/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:37:11 by thitran           #+#    #+#             */
/*   Updated: 2024/11/04 09:37:34 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>

char	*ft_strrchr(const char *str, int c)
{
	char			*last_occurrence;
	unsigned char	ch;

	ch = (unsigned char)c;
	last_occurrence = NULL;
	while (*str)
	{
		if ((unsigned char)*str == ch)
		{
			last_occurrence = (char *)str;
		}
		str++;
	}
	if (ch == '\0')
	{
		return ((char *)str);
	}
	return (last_occurrence);
}
/*
int	main(void)
{
	const char	str[] = "Hello, World";
	char		*ptr;

	ptr = ft_strrchr(str, 'o');
	if (ptr != NULL)
	{
		printf("Last occurrence of 'o' found at position: %td\n", ptr - str);
	}
	else
	{
		printf("Character not found.\n");
	}
	return (0);
}
*/
