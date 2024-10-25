/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:54:06 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 18:54:07 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	g_exit_code = 0;

void	ft_handle_child(int signal)
{
	(void)signal;
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	ft_stop_heredoc(int signal)
{
	(void)signal;
	g_exit_code = 130;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	ft_handle_signal(int signal)
{
	(void)signal;
	g_exit_code = 130;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_config_child(t_shell *shell)
{
	(void)shell;
	signal(SIGINT, ft_handle_child);
	signal(SIGPIPE, SIG_IGN);
}

void	ft_config_signals(t_shell *shell)
{
	(void)shell;
	signal(SIGINT, ft_handle_signal);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
}
