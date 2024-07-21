/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 21:41:40 by likong            #+#    #+#             */
/*   Updated: 2024/07/19 08:53:27 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*res;

	if (!lst || !(*lst) || !del)
		return ;
	while (*lst)
	{
		res = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(res, del);
	}
}
