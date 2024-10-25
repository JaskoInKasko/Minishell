/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:54:20 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 18:54:21 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_unset_option_is_not_supported(t_shell *shell)
{
	ft_putstr_fd("Warning: unset does not support option\n", 2);
	shell->exit_code = 2;
}

void	ft_unset(t_shell *shell, char **group)
{
	int		i;
	int		len;

	i = 1;
	shell->temp_env_list = shell->env_list;
	if (group[i] && group[i][0] == '-')
		return (ft_unset_option_is_not_supported(shell));
	while (group[i])
	{
		shell->temp_env_list = shell->env_list;
		len = ft_strlen(group[i]);
		while (shell->temp_env_list)
		{
			if (!ft_strncmp(shell->temp_env_list->env, group[i],
					ft_strlen(group[i]))
				&& shell->temp_env_list->env[len] == '=')
				ft_remove_env(shell);
			else
				shell->temp_env_list = shell->temp_env_list->next;
		}
		i++;
	}
	ft_update_env(shell);
	ft_update_path(shell);
	shell->exit_code = 0;
}
