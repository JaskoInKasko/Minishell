/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   side.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:54:00 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 18:54:01 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	if (S_ISDIR(path_stat.st_mode))
		return (1);
	else
		return (0);
}

void	ft_handle_error(t_shell *shell, char **group)
{
	if (!ft_strncmp(".\0", group[0], 2))
	{
		ft_putstr_fd("Warning: ", 2);
		ft_putstr_fd(group[0], 2);
		ft_putstr_fd(": filename argument required\n", 2);
		shell->exit_code = 127;
	}
	if (!ft_strncmp("..\0", group[0], 3))
	{
		ft_putstr_fd("Warning: ", 2);
		ft_putstr_fd(group[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		shell->exit_code = 127;
	}
}
