/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_groups.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:52:52 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 18:52:53 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_make_group_list(t_shell *shell)
{
	t_group_args	*node;

	if (shell->cmd != 0 || shell->fd != 0)
	{
		node = ft_lstnew_group(shell);
		ft_lstadd_back_group(&shell->group_list, node);
	}
	if (shell->temp->num == PIPE)
	{
		node = ft_lstnew_pipe(shell);
		ft_lstadd_back_group(&shell->group_list, node);
	}
	shell->cmd = 0;
	shell->fd = 0;
	shell->old_temp = shell->temp->next;
}

void	ft_make_groups(t_shell *shell)
{
	shell->temp = shell->argv_list;
	shell->old_temp = shell->argv_list;
	while (shell->temp)
	{
		if (shell->temp->num != PIPE && shell->temp->num != SKIP)
		{
			if (shell->temp->num != REDIR)
				shell->cmd++;
			else
			{
				shell->fd++;
				if (shell->temp->next && shell->temp->next->num != PIPE)
					shell->fd++;
			}
		}
		if (shell->temp->num == PIPE || shell->temp->num == SKIP
			|| shell->temp->next == NULL)
			ft_make_group_list(shell);
		shell->temp = shell->temp->next;
	}
}
