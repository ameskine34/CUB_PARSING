/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaithadd <younessaithadou9@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:10:04 by yaithadd          #+#    #+#             */
/*   Updated: 2024/11/05 14:58:40 by yaithadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			count++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (count);
}

static char	**free_all(char **result, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (NULL);
}

static char	*malloc_word(const char *str, int start, int len)
{
	char	*word;
	int		i;

	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = str[start + i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

static char	**split_words(char **result, const char *str, char c)
{
	int	i;
	int	len;
	int	word_index;

	i = 0;
	word_index = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
		{
			len = 0;
			while (str[i + len] && str[i + len] != c)
				len++;
			result[word_index] = malloc_word(str, i, len);
			if (!result[word_index])
				return (free_all(result, word_index));
			word_index++;
			i = i + len;
		}
	}
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		words_num;

	if (!s)
		return (NULL);
	words_num = count_words((char *)s, c);
	result = (char **)malloc(sizeof(char *) * (words_num + 1));
	if (!result)
		return (NULL);
	if (!split_words(result, s, c))
		return (NULL);
	result[words_num] = NULL;
	return (result);
}
