/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_found_in_double_quote.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:48:09 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 18:48:11 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_item_found_in_env_quote(t_shell *shell)
{
	shell->remove2 = ft_substr(shell->temp_env_list->env, shell->len + 1,
			ft_strlen(shell->temp_env_list->env) - shell->len - 1);
	ft_malloc_check(shell, shell->remove2, shell->temp_substr,
		shell->temp_cm_buf);
	shell->remove = shell->temp_cm_buf;
	shell->temp_cm_buf = ft_strjoin(shell->temp_cm_buf, shell->remove2);
	if (!shell->temp_cm_buf)
	{
		free(shell->temp_substr);
		shell->temp_substr = NULL;
		ft_malloc_check(shell, shell->temp_cm_buf, shell->remove,
			shell->remove2);
	}
	free(shell->remove2);
	shell->remove2 = NULL;
	free(shell->remove);
	shell->remove = NULL;
}

void	ft_check_item_in_env_quote(t_shell *shell)
{
	while (shell->cm_buf[shell->i]
		&& ft_strchr(" ?.$/'\"\t", shell->cm_buf[shell->i]) == NULL)
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
			&& shell->temp_env_list->env[shell->len] == '=')
		{
			ft_item_found_in_env_quote(shell);
			break ;
		}
		shell->temp_env_list = shell->temp_env_list->next;
	}
	shell->len = 0;
	free(shell->temp_substr);
	shell->temp_substr = NULL;
}

void	ft_dollar_found_in_double_quote(t_shell *shell)
{
	if (ft_heredoc_check(shell) == false)
		return ;
	shell->temp_env_list = shell->env_list;
	ft_update_cm_buf(shell);
	shell->i++;
	shell->start = shell->i;
	if (shell->cm_buf[shell->i] == '?')
		ft_question_mark_found(shell);
	else if (shell->cm_buf[shell->i] == '$')
		ft_second_dollar_found(shell);
	else
		ft_check_item_in_env_quote(shell);
	shell->start = shell->i;
}
