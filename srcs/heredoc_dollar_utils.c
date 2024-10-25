/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_dollar_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:51:29 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 18:51:32 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_item_found_in_env_heredoc(t_shell *shell)
{
	shell->remove2 = ft_substr(shell->temp_env_list->env,
			shell->len + 1,
			ft_strlen(shell->temp_env_list->env) - shell->len - 1);
	ft_malloc_check(shell, shell->remove2, shell->temp_substr,
		shell->temp_hdoc_line);
	shell->remove = shell->temp_hdoc_line;
	shell->temp_hdoc_line = ft_strjoin(shell->temp_hdoc_line,
			shell->remove2);
	if (!shell->temp_hdoc_line)
	{
		free(shell->temp_substr);
		shell->temp_substr = NULL;
		ft_malloc_check(shell, shell->temp_hdoc_line,
			shell->remove, shell->remove2);
	}
	free(shell->remove2);
	shell->remove2 = NULL;
	free(shell->remove);
	shell->remove = NULL;
}

void	ft_check_item_in_env_heredoc(t_shell *shell)
{
	while (shell->hdoc_line[shell->z]
		&& ft_strchr(" $/'\"\t", shell->hdoc_line[shell->z]) == NULL)
	{
		shell->z++;
		shell->len++;
	}
	shell->temp_substr = ft_substr(shell->hdoc_line,
			shell->start, shell->len);
	ft_malloc_check(shell, shell->temp_substr, shell->temp_hdoc_line, NULL);
	while (shell->temp_env_list)
	{
		if (!ft_strncmp(shell->temp_env_list->env,
				shell->temp_substr, shell->len)
			&& shell->temp_env_list->env[shell->len] == '=')
		{
			ft_item_found_in_env_heredoc(shell);
			break ;
		}
		shell->temp_env_list = shell->temp_env_list->next;
	}
	shell->len = 0;
	free(shell->temp_substr);
	shell->temp_substr = NULL;
}

void	ft_question_mark_found_heredoc(t_shell *shell)
{
	shell->z++;
	shell->remove2 = ft_itoa(shell->exit_code);
	ft_malloc_check(shell, shell->remove2, shell->temp_hdoc_line, NULL);
	shell->remove = shell->temp_hdoc_line;
	shell->temp_hdoc_line = ft_strjoin(shell->temp_hdoc_line,
			shell->remove2);
	ft_malloc_check(shell, shell->temp_hdoc_line,
		shell->remove, shell->remove2);
	free(shell->remove2);
	shell->remove2 = NULL;
	free(shell->remove);
	shell->remove = NULL;
}

void	ft_second_dollar_found_heredoc(t_shell *shell)
{
	shell->z++;
	shell->pid = ft_getpid();
	if (shell->pid == 0)
		ft_putstr_fd("\nFailed to get PID\n\n", 2);
	shell->remove2 = ft_itoa(shell->pid);
	ft_malloc_check(shell, shell->remove2, shell->temp_hdoc_line, NULL);
	shell->remove = shell->temp_hdoc_line;
	shell->temp_hdoc_line = ft_strjoin(shell->temp_hdoc_line,
			shell->remove2);
	ft_malloc_check(shell, shell->temp_hdoc_line,
		shell->remove, shell->remove2);
	free(shell->remove2);
	shell->remove2 = NULL;
	free(shell->remove);
	shell->remove = NULL;
}

void	ft_dollar_found_heredoc(t_shell *shell, char *deliminer,
	int quote_found)
{
	if (ft_heredoc_check_heredoc(shell, deliminer) == false || quote_found == 1)
	{
		shell->z++;
		shell->len++;
		return ;
	}
	shell->temp_env_list = shell->env_list;
	ft_update_cm_buf_heredoc(shell);
	shell->z++;
	shell->start = shell->z;
	if (shell->hdoc_line[shell->z] == '?')
		ft_question_mark_found_heredoc(shell);
	else if (shell->hdoc_line[shell->z] == '$')
		ft_second_dollar_found_heredoc(shell);
	else
		ft_check_item_in_env_heredoc(shell);
	shell->start = shell->z;
}
