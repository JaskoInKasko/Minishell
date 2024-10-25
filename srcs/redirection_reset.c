/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_reset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:53:44 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 18:53:46 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_reset_redirections(t_shell *shell)
{
	if (shell->stdout_fd != -1)
	{
		if (dup2(shell->stdout_fd, STDOUT_FILENO) == -1)
			if (dup2(shell->stdout_fd, STDOUT_FILENO) == 1)
				return (perror("shell->stdout_fd"), 1);
		close(shell->stdout_fd);
		shell->stdout_fd = -1;
	}
	if (shell->stdin_fd != -1)
	{
		if (dup2(shell->stdin_fd, STDIN_FILENO) == -1)
			if (dup2(shell->stdin_fd, STDIN_FILENO) == -1)
				return (perror("shell->stdin_fd"), 1);
		close(shell->stdin_fd);
		shell->stdin_fd = -1;
	}
	return (0);
}

int	ft_reset_stdout(t_shell *shell)
{
	if (shell->stdout_fd != -1)
	{
		if (dup2(shell->stdout_fd, STDOUT_FILENO) == -1)
			if (dup2(shell->stdout_fd, STDOUT_FILENO) == 1)
				return (perror("shell->stdout_fd"), 1);
		close(shell->stdout_fd);
		shell->stdout_fd = -1;
	}
	return (0);
}

int	ft_reset_stdin(t_shell *shell)
{
	if (shell->stdin_fd != -1)
	{
		if (dup2(shell->stdin_fd, STDIN_FILENO) == -1)
			if (dup2(shell->stdin_fd, STDIN_FILENO) == -1)
				return (perror("shell->stdin_fd"), 1);
		close(shell->stdin_fd);
		shell->stdin_fd = -1;
	}
	return (0);
}
