/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaithadd <yaithadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:04:52 by yaithadd          #+#    #+#             */
/*   Updated: 2025/12/01 15:31:34 by yaithadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_head;

	if (*lst && new)
	{
		last_head = ft_lstlast(*lst);
		last_head->next = new;
		if (new)
			new->prev = last_head;
	}
	else
		*lst = new;
}
