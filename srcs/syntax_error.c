/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:54:13 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 18:54:15 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

bool	ft_syntax_error_msg(t_shell *shell)
{
	ft_putstr_fd("Warning: syntax error\n", 2);
	shell->exit_code = 2;
	return (false);
}

bool	ft_check_syntax(t_shell *shell)
{
	shell->temp = shell->argv_list;
	while (shell->temp)
	{
		if (shell->temp->num == REDIR)
		{
			if (shell->temp->next == NULL)
				return (ft_syntax_error_msg(shell));
			else if (shell->temp->next->num == PIPE
				|| shell->temp->next->num == REDIR
				|| shell->temp->next->num == SKIP)
				return (ft_syntax_error_msg(shell));
		}
		else if ((shell->temp->num == PIPE || (shell->temp->num == SKIP
					&& shell->temp->mini_argv[0] == ';'))
			&& (shell->temp->prev == NULL || shell->temp->prev->num == SKIP))
			return (ft_syntax_error_msg(shell));
		else if (shell->temp->next != NULL && (shell->temp->num == PIPE
				|| (shell->temp->num == SKIP
					&& shell->temp->mini_argv[0] == ';'))
			&& (shell->temp->next->num == PIPE
				|| shell->temp->next->num == SKIP))
			return (ft_syntax_error_msg(shell));
		shell->temp = shell->temp->next;
	}
	return (true);
}
