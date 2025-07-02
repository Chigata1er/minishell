/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 08:39:51 by thitran           #+#    #+#             */
/*   Updated: 2024/11/07 08:40:14 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	if (s == NULL)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		write (fd, &s[i], 1);
		i++;
	}
	write (fd, "\n", 1);
}
/*
int	main(void)
{
	char	*s = "Hello world";
	int		fd;

	ft_putendl_fd(s, 1);
	fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		printf("Error opening file");
		return (1);
	}
	ft_putendl_fd(s, fd);
	close (fd);
	return (0);
}
*/
