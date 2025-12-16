/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaithadd <younessaithadou9@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:58:35 by yaithadd          #+#    #+#             */
/*   Updated: 2024/11/07 13:31:27 by yaithadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	char			*temp;
	unsigned char	ch;

	temp = (char *)s;
	ch = (unsigned char)c;
	i = 0;
	if (ch == '\0')
		return (temp + ft_strlen(temp));
	while (temp[i])
	{
		if (temp[i] == ch)
			return (temp + i);
		i++;
	}
	return (0);
}
