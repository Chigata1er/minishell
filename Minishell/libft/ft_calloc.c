/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:20:43 by thitran           #+#    #+#             */
/*   Updated: 2024/11/04 09:21:47 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

void	*ft_calloc(size_t num_elements, size_t element_size)
{
	size_t			total_size;
	size_t			i;
	void			*ptr;
	unsigned char	*byte_ptr;

	if (num_elements != 0 && element_size > SIZE_MAX / num_elements)
	{
		return (NULL);
	}
	total_size = num_elements * element_size;
	ptr = malloc(total_size);
	if (ptr == NULL)
	{
		return (NULL);
	}
	byte_ptr = (unsigned char *)ptr;
	i = 0;
	while (i < total_size)
	{
		byte_ptr[i] = 0;
		i++;
	}
	return (ptr);
}
/*
int	main(void)
{
	int	*arr;
	int	num_elements;
	int	i;

	num_elements = 5;
	arr = (int *)ft_calloc(num_elements, sizeof(int));
	if (arr == NULL)
	{
		printf("Memory allocation failed!\n");
		return (1);
	}
	i = 0;
	while (i < num_elements)
	{
		printf("arr[%d] = %d\n", i, arr[i]);
		i++;
	}
	free(arr);
	return (0);
}
*/
