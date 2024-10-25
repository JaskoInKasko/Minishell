/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_found.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:47:48 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 18:47:52 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_question_mark_found(t_shell *shell)
{
	shell->i++;
	shell->remove2 = ft_itoa(shell->exit_code);
	ft_malloc_check(shell, shell->remove2, shell->temp_cm_buf, NULL);
	shell->remove = shell->temp_cm_buf;
	shell->temp_cm_buf = ft_strjoin(shell->temp_cm_buf, shell->remove2);
	ft_malloc_check(shell, shell->temp_cm_buf, shell->remove, shell->remove2);
	free(shell->remove2);
	shell->remove2 = NULL;
	free(shell->remove);
	shell->remove = NULL;
}

void	ft_second_dollar_found(t_shell *shell)
{
	shell->i++;
	shell->pid = ft_getpid();
	if (shell->pid == 0)
		ft_putstr_fd("\nFailed to get PID\n\n", 2);
	shell->remove2 = ft_itoa(shell->pid);
	ft_malloc_check(shell, shell->remove2, shell->temp_cm_buf, NULL);
	shell->remove = shell->temp_cm_buf;
	shell->temp_cm_buf = ft_strjoin(shell->temp_cm_buf, shell->remove2);
	ft_malloc_check(shell, shell->temp_cm_buf, shell->remove, shell->remove2);
	free(shell->remove2);
	shell->remove2 = NULL;
	free(shell->remove);
	shell->remove = NULL;
}

void	ft_dollar_found(t_shell *shell)
{
	shell->check = 0;
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
		ft_check_item_in_env(shell);
	shell->start = shell->i;
}
