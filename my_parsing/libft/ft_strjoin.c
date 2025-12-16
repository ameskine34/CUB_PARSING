/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaithadd <younessaithadou9@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:51:10 by yaithadd          #+#    #+#             */
/*   Updated: 2024/11/05 09:31:37 by yaithadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str_joined;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str_joined = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str_joined)
		return (0);
	while (((char *)s1)[i])
	{
		str_joined[i] = ((char *)s1)[i];
		i++;
	}
	while (((char *)s2)[j])
	{
		str_joined[i] = ((char *)s2)[j];
		i++;
		j++;
	}
	str_joined[i] = '\0';
	return (str_joined);
}
