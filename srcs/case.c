/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:46:04 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 18:46:08 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static int	ft_handle_pipe_creation(t_group_args *temp);
static int	ft_execute_group_list(t_shell *shell, t_group_args *temp, int i);
static int	ft_handle_redirection_and_process(t_shell *shell, \
	t_group_args *temp, int i);
void		ft_wait_for_children(t_shell *shell);

int	ft_case(t_shell *shell)
{
	int				i;
	t_group_args	*temp;

	i = -1;
	temp = shell->group_list;
	if (ft_execute_group_list(shell, temp, i) == 1)
		return (1);
	ft_wait_for_children(shell);
	if (shell->redir_flag == 1)
		shell->exit_code = shell->redir_flag;
	shell->redir_flag = 0;
	shell->count_childs = 0;
	shell->count_args = 0;
	return (0);
}

static int	ft_handle_pipe_creation(t_group_args *temp)
{
	if (temp->next && temp->next->group[0] && temp->next->num == PIPE)
		if (pipe(temp->fd) == -1)
			return (1);
	return (0);
}

static int	ft_execute_group_list(t_shell *shell, t_group_args *temp, int i)
{
	int	redir_status;

	while (temp)
	{
		if (ft_handle_pipe_creation(temp) == 1)
			return (1);
		redir_status = ft_handle_redirection_and_process(shell, temp, i);
		if (redir_status == 1)
			return (1);
		else if (redir_status == -1)
		{
			shell->count_args++;
			temp = temp->next;
			continue ;
		}
		ft_increment_child_count_and_start_process(shell, temp);
		if (ft_reset_redirections(shell) == 1)
			return (1);
		temp = temp->next;
	}
	return (0);
}

static int	\
	ft_handle_redirection_and_process(t_shell *shell, t_group_args *temp, int i)
{
	int	redir_status;

	if (temp->fd_str[0])
	{
		redir_status = ft_setup_redirection(shell, temp, i);
		if (redir_status == 1)
			return (1);
		else if (redir_status == -1)
		{
			temp = temp->next;
			return (-1);
		}
	}
	return (0);
}

void	ft_wait_for_children(t_shell *shell)
{
	int				i;
	t_group_args	*temp;

	i = -1;
	temp = shell->group_list;
	while (temp && temp->next)
		temp = temp->next;
	if (ft_check_if_wait_for_child(shell) == 1)
		return ;
	while (++i < shell->count_childs)
	{
		if (temp->group[0] && temp->num == PIPE)
			temp = temp->prev;
		ft_close_prev_pipes(temp);
		ft_wait_and_exit_status(shell, temp);
		if (temp->prev)
			temp = temp->prev;
	}
	if (shell->exit_code == 131)
		write(1, "Quit (core dumped)\n", 20);
	else if (shell->exit_code == 130)
		write(1, "\n", 1);
}
