/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 20:59:51 by iguliyev          #+#    #+#             */
/*   Updated: 2023/09/25 21:00:02 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*start_lst;
	t_list	*new_list;
	void	*new_content;

	start_lst = NULL;
	if (!f || !del)
		return (NULL);
	while (lst)
	{
		new_content = f(lst->content);
		new_list = ft_lstnew(new_content);
		if (!new_list)
		{
			del(new_content);
			ft_lstclear(&start_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&start_lst, new_list);
		lst = lst -> next;
	}
	return (start_lst);
}
