/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:51:23 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 18:51:24 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_update_cm_buf_heredoc(t_shell *shell)
{
	if (shell->len != 0)
	{
		shell->temp_substr = ft_substr(shell->hdoc_line,
				shell->start, shell->len);
		ft_malloc_check(shell, shell->temp_substr, shell->temp_hdoc_line, NULL);
		shell->remove = shell->temp_hdoc_line;
		shell->temp_hdoc_line = ft_strjoin(shell->temp_hdoc_line,
				shell->temp_substr);
		ft_malloc_check(shell, shell->temp_hdoc_line, shell->temp_substr,
			shell->remove);
		free(shell->temp_substr);
		shell->temp_substr = NULL;
		free(shell->remove);
		shell->remove = NULL;
		shell->len = 0;
	}
}

void	ft_quote_found_heredoc(t_shell *shell, char *deliminer, int quote_found)
{
	shell->c = shell->hdoc_line[shell->z];
	shell->z++;
	shell->len++;
	while (shell->hdoc_line[shell->z] && shell->hdoc_line[shell->z] != shell->c)
	{
		if (shell->c == '"' && shell->hdoc_line[shell->z] == '$'
			&& ft_strchr(" /'\"\t\0", shell->hdoc_line[shell->z + 1]) == NULL)
			ft_dollar_found_heredoc(shell, deliminer, quote_found);
		else
		{
			shell->len++;
			shell->z++;
		}
	}
	if (shell->hdoc_line[shell->z] == shell->c)
	{
		shell->len++;
		shell->z++;
	}
}

bool	ft_heredoc_check_heredoc(t_shell *shell, char *deliminer)
{
	if (ft_strcmp(deliminer, shell->hdoc_line) == 0)
	{
		return (false);
	}
	return (true);
}

void	ft_make_zero(t_shell *shell)
{
	shell->z = 0;
	shell->start = 0;
	shell->len = 0;
}

void	ft_dollar_check_heredoc(t_shell *shell, char *deliminer,
	int quote_found)
{
	shell->z = 0;
	shell->start = 0;
	shell->len = 0;
	shell->temp_hdoc_line = ft_strdup("");
	ft_malloc_check(shell, shell->temp_hdoc_line, NULL, NULL);
	while (shell->hdoc_line[shell->z])
	{
		if (ft_strchr("\"'", shell->hdoc_line[shell->z]) != NULL)
			ft_quote_found_heredoc(shell, deliminer, quote_found);
		else if (shell->hdoc_line[shell->z] == '$'
			&& ft_strchr(" /\t\0", shell->hdoc_line[shell->z + 1]) == NULL)
			ft_dollar_found_heredoc(shell, deliminer, quote_found);
		else
		{
			shell->len++;
			shell->z++;
		}
	}
	ft_update_cm_buf_heredoc(shell);
	shell->remove = shell->hdoc_line;
	shell->hdoc_line = shell->temp_hdoc_line;
	free(shell->remove);
	shell->remove = NULL;
	ft_make_zero(shell);
}
