/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:49:31 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 18:49:33 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_free_loop(t_shell *shell)
{
	ft_free_argv_list(shell);
	ft_free_group_list(shell);
	shell->i = 0;
	shell->len = 0;
	shell->start = 0;
	shell->m = 0;
	shell->n = 0;
}

void	ft_free_argv_list(t_shell *shell)
{
	t_mini_argv	*temp;

	while (shell->argv_list)
	{
		temp = shell->argv_list;
		shell->argv_list = shell->argv_list->next;
		free(temp->mini_argv);
		temp->mini_argv = NULL;
		free(temp);
		temp = NULL;
	}
	shell->argv_list = NULL;
}

void	ft_free_group_list(t_shell *shell)
{
	t_group_args	*temp;

	while (shell->group_list)
	{
		temp = shell->group_list;
		shell->group_list = shell->group_list->next;
		if (temp->group)
		{
			free(temp->group);
			temp->group = NULL;
		}
		if (temp->fd_str)
		{
			free(temp->fd_str);
			temp->fd_str = NULL;
		}
		if (temp)
		{
			free(temp);
			temp = NULL;
		}
	}
	shell->group_list = NULL;
}
