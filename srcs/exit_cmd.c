/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:49:13 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 18:49:14 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_exit_empty(t_shell *shell, char *group)
{
	if (ft_strlen(group) == 0)
	{
		ft_putstr_fd("Warning: numeric argument required\n", 2);
		shell->exit_code = 2;
		ft_exit(shell, NULL);
	}
}

void	ft_exit_numeric_number(t_shell *shell, char *group)
{
	int	i;
	int	check;

	check = 0;
	i = 0;
	ft_exit_empty(shell, group);
	while (group[i])
	{
		if ((group[0] == '+' || group[0] == '-') && check == 0)
		{
			check = -1;
			i++;
		}
		if (!ft_isdigit(group[i]))
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("Warning: numeric argument required\n", 2);
			shell->exit_code = 2;
			ft_exit(shell, NULL);
		}
		i++;
	}
}

void	ft_exit_cmd(t_shell *shell, char **group)
{
	if (!group[1])
	{
		ft_putstr_fd("exit\n", 2);
		shell->exit_code = 0;
		ft_exit(shell, NULL);
	}
	if (group[1])
		ft_exit_numeric_number(shell, group[1]);
	if (group[2])
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("Warning: too many arguments\n", 2);
		shell->exit_code = 1;
	}
	else
	{
		ft_putstr_fd("exit\n", 2);
		shell->exit_code = ft_atoi(group[1]) % 256;
		ft_exit(shell, NULL);
	}
}
