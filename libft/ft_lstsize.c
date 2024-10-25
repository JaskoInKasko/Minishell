/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 19:26:12 by iguliyev          #+#    #+#             */
/*   Updated: 2023/09/24 19:29:23 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst -> next;
		i++;
	}
	return (i);
}
/*
int main()
{
    // Create a linked list with three elements
    t_list *element1 = malloc(sizeof(t_list));
    element1->content = "Element 1";
    element1->next = NULL;

    t_list *element2 = malloc(sizeof(t_list));
    element2->content = "Element 2";
    element2->next = NULL;

    t_list *element3 = malloc(sizeof(t_list));
    element3->content = "Element 3";
    element3->next = NULL;

    // Link the elements to form a linked list
    element1->next = element2;
    element2->next = element3;

    // Calculate the size of the linked list using ft_lstsize
    int size = ft_lstsize(element1);

    // Print the size of the linked list
    printf("Size of the linked list: %d\n", size);

    // Free the allocated memory
    free(element1);
    free(element2);
    free(element3);

    return 0;
}*/
