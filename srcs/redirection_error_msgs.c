/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_error_msgs.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:53:36 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 18:53:39 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	\
ft_print_error_message(t_group_args *temp, int slash_flag, int slash_position);

void	ft_get_correct_err_msg(t_shell *shell, t_group_args *temp)
{
	int	i;
	int	slash_flag;
	int	slash_position;

	i = -1;
	slash_flag = 0;
	slash_position = 0;
	while (temp->fd_str[1][++i] != '\0')
	{
		if (temp->fd_str[1][i] == '/')
			slash_flag++;
	}
	while (i >= 0)
	{
		if (temp->fd_str[1][i] == '/')
		{
			slash_position = i;
			break ;
		}
		i--;
	}
	ft_print_error_message(temp, slash_flag, slash_position);
	shell->exit_code = 1;
}

static void	ft_print_error_message(t_group_args *temp, \
	int slash_flag, int slash_position)
{
	if (temp->fd_str[1][0] == '/' && slash_flag == 1)
	{
		ft_putstr_fd("Warning: ", STDERR_FILENO);
		ft_putstr_fd(temp->fd_str[1], STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	}
	else if (slash_flag >= 1 && slash_position > 1
		&& temp->fd_str[1][slash_position + 1] != '\0')
	{
		ft_putstr_fd("Warning: ", STDERR_FILENO);
		ft_putstr_fd(temp->fd_str[1], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd("Warning: ", STDERR_FILENO);
		ft_putstr_fd(temp->fd_str[1], STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
	}
}
