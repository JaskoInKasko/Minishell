/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:46:55 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 18:47:35 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_quote_found(t_shell *shell)
{
	shell->quote_found = 1;
	shell->c = shell->cm_buf[shell->i];
	shell->i++;
	shell->len++;
	while (shell->cm_buf[shell->i] && shell->cm_buf[shell->i] != shell->c)
	{
		if (shell->c == '"' && shell->cm_buf[shell->i] == '$'
			&& ft_strchr(" /'\"\t\0", shell->cm_buf[shell->i + 1]) == NULL)
			ft_dollar_found_in_double_quote(shell);
		else
		{
			shell->len++;
			shell->i++;
		}
	}
	if (shell->cm_buf[shell->i] == shell->c)
	{
		shell->len++;
		shell->i++;
	}
}

void	ft_home_found(t_shell *shell)
{
	ft_update_cm_buf(shell);
	shell->i++;
	shell->start = shell->i;
	shell->remove = shell->temp_cm_buf;
	shell->temp_cm_buf = ft_strjoin(shell->temp_cm_buf, shell->home);
	ft_malloc_check(shell, shell->temp_cm_buf, shell->remove, NULL);
	free(shell->remove);
	shell->remove = NULL;
}

void	ft_dollar_check_loop(t_shell *shell)
{
	if (ft_strchr("\"'", shell->cm_buf[shell->i]) != NULL)
		ft_quote_found(shell);
	else if (shell->cm_buf[shell->i] == '$'
		&& ft_strchr(" /\t\0", shell->cm_buf[shell->i + 1]) == NULL)
		ft_dollar_found(shell);
	else if (shell->cm_buf[shell->i] == '~'
		&& ft_strchr(" /\t\0", shell->cm_buf[shell->i + 1]) != NULL)
		ft_home_found(shell);
	else
	{
		shell->len++;
		shell->i++;
	}
}

void	ft_dollar_check(t_shell *shell)
{
	shell->i = 0;
	shell->start = 0;
	shell->len = 0;
	shell->temp_cm_buf = ft_strdup("");
	ft_malloc_check(shell, shell->temp_cm_buf, NULL, NULL);
	while (shell->cm_buf[shell->i])
	{
		ft_dollar_check_loop(shell);
	}
	ft_update_cm_buf(shell);
	shell->remove = shell->cm_buf;
	shell->cm_buf = shell->temp_cm_buf;
	free(shell->remove);
	shell->remove = NULL;
	shell->i = 0;
	shell->start = 0;
	shell->len = 0;
}
