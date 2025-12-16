/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaithadd <younessaithadou9@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:47:23 by yaithadd          #+#    #+#             */
/*   Updated: 2024/11/07 13:29:13 by yaithadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	char			*temp;
	unsigned char	ch;

	temp = (char *)s;
	ch = (unsigned char)c;
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (temp[i] == ch)
			return (temp + i);
		i--;
	}
	return (NULL);
}
