/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 13:56:41 by esormune          #+#    #+#             */
/*   Updated: 2021/04/29 01:59:52 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*fresult;
	t_list	*nlist;

	if (!lst || !f)
		return (NULL);
	fresult = f(lst);
	new = ft_lstnew(fresult->content, fresult->content_size);
	if (!(new))
		return (NULL);
	nlist = new;
	lst = lst->next;
	while (lst)
	{
		fresult = f(lst);
		nlist->next = ft_lstnew(fresult->content, fresult->content_size);
		if (!(nlist->next))
			return (NULL);
		lst = lst->next;
		nlist = nlist->next;
	}
	return (new);
}
