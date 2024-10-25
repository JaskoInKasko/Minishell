/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:49:20 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 18:49:25 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_check_input_msg(t_shell *shell, char *str)
{
	ft_putstr_fd("Warning: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" is not valid!\n", 2);
	shell->exit_code = 1;
}

int	ft_check_input(t_shell *shell, char *str)
{
	shell->t = 1;
	if (str[0] == '-')
	{
		ft_putstr_fd("Warning: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		shell->exit_code = 2;
		return (1);
	}
	if (ft_isalpha(str[0]) == 0 && str[0] != '_')
		return (ft_check_input_msg(shell, str), 1);
	while (str[shell->t] && str[shell->t] != '=')
	{
		if (ft_isalnum(str[shell->t]) == 0 && str[shell->t] != '_')
			return (ft_check_input_msg(shell, str), 1);
		shell->t++;
	}
	shell->t = 0;
	while (str[shell->t])
	{
		if (str[shell->t] == '=')
			return (0);
		shell->t++;
	}
	return (-1);
}

void	ft_print_export(t_shell *shell)
{
	shell->temp_env_list = shell->env_list;
	while (shell->temp_env_list)
	{
		ft_putstr_fd(shell->temp_env_list->exp, 1);
		ft_putstr_fd("\n", 1);
		shell->temp_env_list = shell->temp_env_list->next;
	}
}

void	ft_export(t_shell *shell, char **group)
{
	int	i;
	int	check;

	i = 1;
	check = 0;
	if (!group[1])
		ft_print_export(shell);
	else
	{
		while (group[i])
		{
			check = ft_check_input(shell, group[i]);
			if (check == 0)
				ft_add_env(shell, group[i]);
			else if (check == 1)
				return ;
			i++;
		}
	}
	shell->exit_code = 0;
}
