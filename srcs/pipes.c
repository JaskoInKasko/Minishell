/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:53:06 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 18:53:07 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static int	ft_handle_middle_and_last_child(t_shell *shell, t_group_args *temp);

void	ft_handle_both_pipes(t_shell *shell, t_group_args *temp)
{
	if (shell->lst_size > 1)
	{
		if (shell->count_args == 1
			&& (ft_is_redirection(temp, shell->redirs_i) == 1
				|| ft_is_redirection(temp, shell->redirs_i) == 2))
		{
			if (temp->next)
			{
				if (temp->next->num == PIPE)
				{
					if (dup2(temp->fd[1], 1) == -1)
						return (perror(""));
					close(temp->fd[0]);
					close(temp->fd[1]);
				}
			}
		}
		else if (temp->prev)
			if (ft_handle_middle_and_last_child(shell, temp) == 1)
				return ;
	}
}

static int	ft_handle_middle_and_last_child(t_shell *shell, t_group_args *temp)
{
	if (temp->prev->num == PIPE)
	{
		if (temp->next)
		{
			if (temp->next->num == PIPE && (ft_is_redirection(temp, 0) == 1
					|| ft_is_redirection(temp, 0) == 2))
			{
				if (dup2(temp->fd[1], 1) == -1)
					return (perror("temp->fd[1]"), 1);
				close(temp->fd[0]);
				close(temp->fd[1]);
			}
		}
		if (ft_is_redirection(temp, 0) != 2)
			if (dup2(temp->prev->prev->fd[0], 0) == -1)
				ft_exit(shell, "dup2() failed in child\n");
	}
	return (0);
}

void	ft_close_prev_pipes(t_group_args *temp)
{
	if (temp->fd[0] != -2)
		close(temp->fd[0]);
	if (temp->fd[1] != -2)
		close(temp->fd[1]);
	while (temp->prev)
	{
		temp = temp->prev;
		if (temp->fd[0] != -2)
			close(temp->fd[0]);
		if (temp->fd[1] != -2)
			close(temp->fd[1]);
	}
}
