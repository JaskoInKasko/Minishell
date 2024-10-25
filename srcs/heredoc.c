/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:51:15 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 18:51:16 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static int	ft_heredoc(t_shell *shell, t_group_args *temp);
static int	ft_handle_after_heredoc(t_shell *shell, t_group_args *temp);
static void	ft_heredoc_first_read(t_shell *shell, t_group_args *temp);

int	ft_handle_heredoc(t_shell *shell, t_group_args *temp)
{
	temp->file_fd = open("Heredoc.hdoc", O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (temp->file_fd == -1)
	{
		ft_get_correct_err_msg(shell, temp);
		if (!temp->next
			|| (temp->next && temp->next->group[0] && temp->next->num != PIPE))
			shell->redir_flag = 1;
		return (1);
	}
	ft_heredoc(shell, temp);
	temp->file_fd = open("Heredoc.hdoc", O_RDWR, 0666);
	if (temp->file_fd == -1)
	{
		ft_get_correct_err_msg(shell, temp);
		if (!temp->next
			|| (temp->next && temp->next->group[0] && temp->next->num != PIPE))
			shell->redir_flag = 1;
		return (1);
	}
	if (ft_handle_after_heredoc(shell, temp) == 1)
		return (1);
	return (0);
}

static void	ft_heredoc_first_read(t_shell *shell, t_group_args *temp)
{
	if (g_exit_code != 130)
	{
		shell->hdoc_line = readline("> ");
		if (shell->hdoc_line && ft_strchr(shell->hdoc_line, '$'))
			ft_dollar_check_heredoc(shell, temp->fd_str[1], temp->quote_found);
		if (!shell->hdoc_line)
		{
			ft_putstr_fd("Warning: heredoc delimited by EOF\n", STDOUT_FILENO);
		}
	}
}

static int	ft_heredoc(t_shell *shell, t_group_args *temp)
{
	signal(SIGINT, ft_stop_heredoc);
	ft_heredoc_first_read(shell, temp);
	while (g_exit_code != 130 && shell->hdoc_line
		&& ft_strcmp(shell->hdoc_line, temp->fd_str[1]) != 0)
	{
		ft_putstr_fd(shell->hdoc_line, temp->file_fd);
		ft_putstr_fd("\n", temp->file_fd);
		free(shell->hdoc_line);
		shell->hdoc_line = NULL;
		shell->hdoc_line = readline("> ");
		if (shell->hdoc_line && ft_strchr(shell->hdoc_line, '$'))
			ft_dollar_check_heredoc(shell, temp->fd_str[1], temp->quote_found);
		if (!shell->hdoc_line)
		{
			ft_putstr_fd("Warning: heredoc delimited by EOF\n", STDOUT_FILENO);
		}
	}
	signal(SIGINT, ft_handle_signal);
	if (shell->hdoc_line && g_exit_code != 130)
	{
		free(shell->hdoc_line);
		shell->hdoc_line = NULL;
	}
	close(temp->file_fd);
	return (0);
}

static int	ft_handle_after_heredoc(t_shell *shell, t_group_args *temp)
{
	shell->stdin_fd = dup(STDIN_FILENO);
	if (shell->stdin_fd == -1)
		return (perror("dup() function failed at line 174\
		(redirection.c)\n"), 1);
	if (dup2(temp->file_fd, STDIN_FILENO) == -1)
		return (perror("dup2() function failed at line 177\
		(redirection.c)\n"), 1);
	close(temp->file_fd);
	unlink("Heredoc.hdoc");
	return (0);
}
