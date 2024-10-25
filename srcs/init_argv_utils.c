/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_argv_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:51:52 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 18:51:54 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

bool	ft_heredoc_check(t_shell *shell)
{
	int	index;

	index = shell->i;
	index--;
	while (index > 0)
	{
		if (ft_strchr(" \t", shell->cm_buf[index]) == NULL)
		{
			while (index > 0 && ft_strchr(" \t", shell->cm_buf[index]) == NULL)
				index--;
		}
		while (index > 0 && ft_strchr(" \t", shell->cm_buf[index]) != NULL)
			index--;
		if (shell->cm_buf[index] == '<')
		{
			if (index > 0 && shell->cm_buf[index - 1] == '<')
			{
				shell->i++;
				shell->len++;
				return (false);
			}
		}
		index--;
	}
	return (true);
}

void	ft_init_pipe_values(t_shell *shell)
{
	t_group_args	*temp;

	temp = shell->group_list;
	shell->lst_size = ft_lstsize_group_args(temp);
	while (temp)
	{
		temp->pid = -1;
		temp->fd[0] = -2;
		temp->fd[1] = -2;
		temp = temp->next;
	}
	shell->stdout_fd = -1;
	shell->stdin_fd = -1;
	shell->count_childs = 0;
}
