/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaithadd <yaithadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:31:40 by yaithadd          #+#    #+#             */
/*   Updated: 2025/11/30 16:26:54 by yaithadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;
	size_t			s1_len;
	size_t			s2_len;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (n > s1_len || n > s2_len || n == 0)
	{
		if (s1_len > s2_len)
			n = s1_len;
		else
			n = s2_len;
	}
	i = 0;
	while (i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}
