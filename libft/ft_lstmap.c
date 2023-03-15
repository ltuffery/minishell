/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njegat <njegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:27:44 by swotex            #+#    #+#             */
/*   Updated: 2022/10/16 02:16:04 by njegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list;
	t_list	*temp;
	void	*element;

	if (!(lst))
		return (lst);
	element = f(lst->content);
	list = ft_lstnew(element);
	if (!(list))
		return (NULL);
	lst = lst->next;
	while (lst->next)
	{
		element = f(lst->content);
		temp = ft_lstnew(element);
		if (!(temp))
			ft_lstclear(&list, del);
		if (!(temp))
			return (NULL);
		ft_lstadd_back(&list, temp);
		lst = lst->next;
	}
	element = f(lst->content);
	ft_lstadd_back(&list, ft_lstnew(element));
	return (list);
}
