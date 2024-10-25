/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:48:23 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 18:48:26 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_echo_minus_n(t_shell *shell, char **group)
{
	int	k;

	k = 2;
	while (group[shell->u] && !ft_strncmp("-n", group[shell->u], 2))
	{
		k = 2;
		while (group[shell->u][k] == 'n')
			k++;
		if (group[shell->u][k] == '\0')
		{
			shell->check_sign = 1;
			shell->u++;
		}
		else
			break ;
	}
}

void	ft_echo_print(t_shell *shell, char **group)
{
	int	j;

	j = 0;
	while (group[shell->u])
	{
		while (group[shell->u][j])
		{
			ft_putchar_fd(group[shell->u][j], 1);
			j++;
		}
		j = 0;
		shell->u++;
		if (group[shell->u])
			ft_putstr_fd(" ", 1);
	}
}

void	ft_echo(t_shell *shell, char **group)
{
	shell->u = 1;
	shell->check_sign = 0;
	if (!group[shell->u])
	{
		ft_putstr_fd("\n", 1);
		shell->exit_code = 0;
		return ;
	}
	ft_echo_minus_n(shell, group);
	ft_echo_print(shell, group);
	if (shell->check_sign == 0)
		ft_putstr_fd("\n", 1);
	shell->exit_code = 0;
}
