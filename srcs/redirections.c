/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:53:51 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 18:53:52 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static int	handle_redirection(t_shell *shell, t_group_args *temp, int i);
static int	ft_handle_redir_out(t_shell *shell, t_group_args *temp, int i);
static int	ft_handle_redir_out_append(t_shell *shell, \
	t_group_args *temp, int i);
static int	ft_handle_redir_in(t_shell *shell, t_group_args *temp, int i);

int	ft_setup_redirection(t_shell *shell, t_group_args *temp, int i)
{
	i = -1;
	while (temp->fd_str[++i] != NULL)
	{
		if (ft_is_redirection(temp, i) == 0 || ft_is_redirection(temp, i) == 2)
		{
			if (temp->fd_str[i + 1])
			{
				shell->redirs_i = i;
				if (ft_is_redirection(temp, i) == 0)
				{
					if (ft_reset_stdout(shell) == 1)
						return (1);
				}
				else if (ft_is_redirection(temp, i) == 2)
				{
					if (ft_reset_stdin(shell) == 1)
						return (1);
				}
				if (handle_redirection(shell, temp, i) == 1)
					return (-1);
			}
		}
	}
	return (0);
}

static int	handle_redirection(t_shell *shell, t_group_args *temp, int i)
{
	if (ft_strncmp(temp->fd_str[i], ">\0", 2) == 0)
	{
		if (ft_handle_redir_out(shell, temp, i) == 1)
			return (1);
	}
	else if (ft_strncmp(temp->fd_str[i], ">>\0", 3) == 0)
	{
		if (ft_handle_redir_out_append(shell, temp, i) == 1)
			return (1);
	}
	else if (ft_strncmp(temp->fd_str[i], "<\0", 2) == 0)
	{
		if (ft_handle_redir_in(shell, temp, i) == 1)
			return (1);
	}
	else if (ft_strncmp(temp->fd_str[i], "<<\0", 3) == 0)
	{
		if (ft_handle_heredoc(shell, temp) == 1)
			return (1);
	}
	return (0);
}

static int	ft_handle_redir_out(t_shell *shell, t_group_args *temp, int i)
{
	temp->file_fd = open(temp->fd_str[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (temp->file_fd == -1)
	{
		ft_get_correct_err_msg(shell, temp);
		if (!temp->next
			|| (temp->next && temp->next->group[0] && temp->next->num != PIPE))
			shell->redir_flag = 1;
		return (1);
	}
	shell->stdout_fd = dup(STDOUT_FILENO);
	if (shell->stdout_fd == -1)
		return (perror("STDOUT_FILENO"), 1);
	if (dup2(temp->file_fd, STDOUT_FILENO) == -1)
		return (perror("temp->file_fd"), 1);
	close(temp->file_fd);
	return (0);
}

static int	ft_handle_redir_out_append(t_shell *shell, \
	t_group_args *temp, int i)
{
	temp->file_fd = open(temp->fd_str[i + 1], \
		O_RDWR | O_CREAT | O_APPEND, 0666);
	if (temp->file_fd == -1)
	{
		ft_get_correct_err_msg(shell, temp);
		if (!temp->next
			|| (temp->next && temp->next->group[0] && temp->next->num != PIPE))
			shell->redir_flag = 1;
		return (1);
	}
	shell->stdout_fd = dup(STDOUT_FILENO);
	if (shell->stdout_fd == -1)
		return (perror("STDOUT_FILENO"), 1);
	if (dup2(temp->file_fd, STDOUT_FILENO) == -1)
		return (perror("STDOUT_FILENO"), 1);
	close(temp->file_fd);
	return (0);
}

static int	ft_handle_redir_in(t_shell *shell, t_group_args *temp, int i)
{
	temp->file_fd = open(temp->fd_str[i + 1], O_RDWR);
	if (temp->file_fd == -1)
	{
		if (access(temp->fd_str[1], F_OK) != 0)
		{
			ft_putstr_fd("Warning: ", STDERR_FILENO);
			ft_putstr_fd(temp->fd_str[1], STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		}
		if (!temp->next
			|| (temp->next && temp->next->group[0] && temp->next->num != PIPE))
			shell->redir_flag = 1;
		return (1);
	}
	shell->stdin_fd = dup(STDIN_FILENO);
	if (shell->stdin_fd == -1)
		return (perror("STDIN_FILENO"), 1);
	if (dup2(temp->file_fd, STDIN_FILENO) == -1)
		return (perror("STDIN_FILENO"), 1);
	close(temp->file_fd);
	return (0);
}
