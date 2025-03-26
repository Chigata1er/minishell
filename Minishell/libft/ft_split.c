/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thitran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:31:53 by thitran           #+#    #+#             */
/*   Updated: 2024/11/04 09:32:30 by thitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static char	*allocate_word(char const *s, int start, int end)
{
	int		k;
	char	*word;

	word = (char *)malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	k = 0;
	while (start < end)
		word[k++] = s[start++];
	word[k] = '\0';
	return (word);
}

static char	**allocate_result(char const *s, char c, int *count)
{
	int		i;
	int		in_word;
	char	**result;

	*count = 0;
	in_word = 0;
	i = 0;
	while (s[i])
	{
		if ((s[i] != c) && !in_word)
		{
			in_word = 1;
			(*count)++;
		}
		else if (s[i] == c)
			in_word = 0;
		i++;
	}
	result = (char **)malloc((*count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	return (result);
}

static void	free_result(char **result, int words_allocated)
{
	int	i;

	i = 0;
	while (i < words_allocated)
	{
		free(result[i]);
		i++;
	}
	free(result);
}

static int	fill_result(char **result, char const *s, char c)
{
	int		i;
	int		j;
	int		start;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] != '\0' && (s[i] == c))
			i++;
		start = i;
		while (s[i] != '\0' && (s[i] != c))
			i++;
		if (i > start)
		{
			result[j] = allocate_word((char *)s, start, i);
			if (!result[j++])
			{
				free_result(result, j);
				return (0);
			}
		}
	}
	result[j] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**result;

	result = allocate_result(s, c, &words);
	if (!result)
		return (NULL);
	if (!fill_result(result, s, c))
		return (NULL);
	return (result);
}
/*
int	main(void)
{
	int		i;
	char	*s = "Hello world! Welcome to 42 Nice";
	char	c = ' ';
	char	**result;

	result = ft_split(s, c);
	i = 0;
	while (result[i] != NULL)
	{
		printf("%s\n", result[i]);
		free(result[i]);
		i++;
	}
	free(result);
	return (0);
}
*/
