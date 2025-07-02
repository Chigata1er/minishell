/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 08:38:51 by thitran           #+#    #+#             */
/*   Updated: 2024/11/07 08:39:17 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}
/*
int	main(void)
{
	char	c = 'H';
	int		fd;	

	ft_putchar_fd(c, 1);
	fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		printf("Error opening file");
		return (1);
	}	
	ft_putchar_fd(c, fd);
	close (fd);
	return (0);
}
*/
