/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaithadd <younessaithadou9@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 22:00:31 by yaithadd          #+#    #+#             */
/*   Updated: 2024/11/05 09:42:04 by yaithadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_contain_ch(char *str, char ch)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ch)
			return (1);
		i++;
	}
	return (0);
}

static char	*allocate_str(char *str, int len)
{
	char	*result;
	int		i;

	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*result;
	char	*str;
	char	*str_trim;

	if (!s1 || !set)
		return (NULL);
	str = (char *)s1;
	str_trim = (char *)set;
	start = 0;
	end = ft_strlen((char *)str) - 1;
	while (str[start] && is_contain_ch(str_trim, str[start]) == 1)
		start++;
	while (str[end] && end >= start && is_contain_ch(str_trim, str[end]) == 1)
		end--;
	result = allocate_str(str + start, end - start + 1);
	return (result);
}
