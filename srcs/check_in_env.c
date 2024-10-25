/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:08:35 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/31 16:08:38 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	ft_item_found_in_env_merge(t_shell *shell)
{
	shell->remove = shell->temp_cm_buf;
	shell->temp_cm_buf = ft_strjoin(shell->temp_cm_buf, shell->remove2);
	if (!shell->temp_cm_buf)
	{
		free(shell->temp_substr);
		shell->temp_substr = NULL;
		ft_malloc_check(shell, shell->temp_cm_buf, shell->remove,
			shell->remove2);
	}
	free(shell->remove);
	shell->remove = NULL;
	free(shell->remove2);
	shell->remove2 = NULL;
	if (shell->check == 1)
		ft_add_space(shell);
}

void	ft_item_found_in_env(t_shell *shell)
{
	shell->remove2 = ft_substr(shell->temp_env_list->env, shell->len + 1,
			ft_strlen(shell->temp_env_list->env) - shell->len - 1);
	ft_malloc_check(shell, shell->remove2, shell->temp_substr,
		shell->temp_cm_buf);
	if (shell->remove2[0] == ' ' || shell->remove2[0] == '\t')
	{
		shell->remove = shell->temp_cm_buf;
		shell->temp_cm_buf = ft_strjoin(shell->temp_cm_buf, " ");
		ft_malloc_check(shell, shell->temp_cm_buf, shell->remove, NULL);
		free(shell->remove);
	}
	if (shell->remove2[ft_strlen(shell->remove2) - 1] == ' '
		|| shell->remove2[ft_strlen(shell->remove2) - 1] == '\t')
		shell->check++;
	ft_update_env_value(shell);
	ft_item_found_in_env_merge(shell);
}

void	ft_check_item_in_env(t_shell *shell)
{
	while (shell->cm_buf[shell->i]
		&& ft_strchr(" ?.$/\'\"\t", shell->cm_buf[shell->i]) == NULL)
	{
		shell->i++;
		shell->len++;
	}
	shell->temp_substr = ft_substr(shell->cm_buf, shell->start, shell->len);
	ft_malloc_check(shell, shell->temp_substr, shell->temp_cm_buf, NULL);
	while (shell->temp_env_list)
	{
		if (!ft_strncmp(shell->temp_env_list->env,
				shell->temp_substr, shell->len)
			&& shell->temp_env_list->env[shell->len] == '='
			&& shell->temp_env_list->env[shell->len + 1])
		{
			ft_item_found_in_env(shell);
			break ;
		}
		shell->temp_env_list = shell->temp_env_list->next;
	}
	shell->len = 0;
	free(shell->temp_substr);
}
