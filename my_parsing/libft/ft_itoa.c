/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaithadd <younessaithadou9@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:07:19 by yaithadd          #+#    #+#             */
/*   Updated: 2024/11/07 10:51:15 by yaithadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_len(int num)
{
	int	count;

	count = 0;
	if (num == 0)
		return (count + 1);
	if (num < 0)
	{
		num = num * -1;
		count++;
	}
	while (num != 0)
	{
		num = num / 10;
		count++;
	}
	return (count);
}

static void	fill_allocated_result(char *result, long num, int len)
{
	if (num == 0)
	{
		result[0] = '0';
	}
	if (num < 0)
	{
		fill_allocated_result(result, num * -1, len);
		result[0] = '-';
	}
	else if (num > 0)
	{
		len--;
		fill_allocated_result(result, num / 10, len);
		result[len] = (num % 10) + 48;
	}
}

char	*ft_itoa(int n)
{
	char	*result;
	int		len;

	len = num_len(n);
	result = (char *)malloc((sizeof(char) * len) + 1);
	if (!result)
		return (0);
	fill_allocated_result(result, n, len);
	result[len] = '\0';
	return (result);
}
