/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaithadd <younessaithadou9@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:01:17 by yaithadd          #+#    #+#             */
/*   Updated: 2024/11/07 13:29:00 by yaithadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	char	*allocated_str;
	int		i;

	i = 0;
	str = (char *)s;
	allocated_str = (char *)malloc((ft_strlen(str) * sizeof(char)) + 1);
	if (!allocated_str)
		return (NULL);
	while (str[i])
	{
		allocated_str[i] = str[i];
		i++;
	}
	allocated_str[i] = '\0';
	return (allocated_str);
}
