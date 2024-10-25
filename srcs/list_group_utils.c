/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_group_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 23:39:54 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 19:17:47 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_lstsize_group_args(t_group_args *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_group_args	*ft_lstnew_pipe(t_shell *shell)
{
	t_group_args	*new;

	new = (t_group_args *)malloc(sizeof(t_group_args));
	if (!new)
		ft_exit(shell, "\nMalloc failed\n\n");
	new->group = (char **)malloc((1 + 1) * sizeof(char *));
	if (!new->group)
		ft_malloc_group(shell, NULL, NULL, new);
	new->fd_str = (char **)malloc((1 + 1) * sizeof(char *));
	if (!new->fd_str)
		ft_malloc_group(shell, new->group, NULL, new);
	new->group[0] = shell->temp->mini_argv;
	new->group[1] = NULL;
	new->fd_str[0] = "PIPE";
	new->fd_str[1] = NULL;
	new->num = PIPE;
	new->quote_found = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_group_args	*ft_lstlast_group(t_group_args *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_group(t_group_args **lst, t_group_args *node)
{
	t_group_args	*tmp;

	tmp = ft_lstlast_group(*lst);
	if (!tmp)
		*lst = node;
	else
	{
		tmp->next = node;
		node->prev = tmp;
	}
}
