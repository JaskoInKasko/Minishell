/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:51:07 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 18:51:08 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_is_redirection(t_group_args *temp, int i)
{
	if (temp->fd_str[i])
	{
		if (ft_strncmp(temp->fd_str[i], ">\0", 2) == 0
			|| ft_strncmp(temp->fd_str[i], ">>\0", 3) == 0)
			return (0);
		if (ft_strncmp(temp->fd_str[i], "<\0", 2) == 0
			|| ft_strncmp(temp->fd_str[i], "<<\0", 3) == 0)
			return (2);
	}
	return (1);
}

int	ft_is_absolute_path(t_group_args *temp)
{
	int	i;

	i = -1;
	while (temp->group[0][++i] != '\0')
		if (temp->group[0][i] == '/')
			return (0);
	return (1);
}

void	ft_print_cmd_not_found(t_shell *shell, t_group_args *temp)
{
	write(2, temp->group[0], ft_strlen(temp->group[0]));
	write(2, ": command not found\n", 20);
	shell->exit_code = 127;
}

void	ft_handle_execution_errors(t_shell *shell, t_group_args *temp)
{
	free(shell->execve_path);
	perror(temp->group[0]);
	shell->exit_code = 126;
	ft_exit(shell, NULL);
}
