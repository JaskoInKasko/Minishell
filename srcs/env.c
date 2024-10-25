/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:48:45 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 18:48:47 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_env(t_shell *shell, char **group)
{
	int	i;

	i = 0;
	if (group[1])
	{
		if (access(group[1], F_OK) != 0)
		{
			perror(group[1]);
			shell->exit_code = 127;
		}
		else
		{
			ft_putstr_fd(group[1], 2);
			ft_putstr_fd(": Permission denied\n", 2);
			shell->exit_code = 126;
		}
		return ;
	}
	while (shell->env[i])
	{
		ft_putstr_fd(shell->env[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	shell->exit_code = 0;
}
