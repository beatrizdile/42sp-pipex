/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:46:39 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/05/16 15:38:20 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*head;
	t_list	*map;

	if (!lst)
		return (NULL);
	map = NULL;
	temp = lst;
	while (temp != NULL)
	{
		head = ft_lstnew(f(temp->content));
		if (head)
			ft_lstadd_back(&map, head);
		else
			ft_lstclear(&head, del);
		temp = temp->next;
	}
	return (map);
}
