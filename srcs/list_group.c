/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_group.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 23:39:54 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 19:17:40 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include <stdlib.h>

void	ft_update_str(t_shell *shell)
{
	if (shell->len != 0)
	{
		shell->temp_substr = ft_substr(shell->old_temp->mini_argv,
				shell->start, shell->len);
		if (!shell->temp_substr)
		{
			ft_malloc_free(shell->temp_substr, shell->t_sjoin, NULL);
			ft_malloc_group(shell, shell->group->group, shell->group->fd_str,
				shell->group);
		}
		shell->remove = shell->t_sjoin;
		shell->t_sjoin = ft_strjoin(shell->t_sjoin,
				shell->temp_substr);
		if (!shell->t_sjoin)
		{
			ft_malloc_free(shell->t_sjoin, shell->remove, shell->temp_substr);
			ft_malloc_group(shell, shell->group->group, shell->group->fd_str,
				shell->group);
		}
		free(shell->temp_substr);
		shell->temp_substr = NULL;
		free(shell->remove);
		shell->remove = NULL;
		shell->len = 0;
	}
}

void	ft_quote_detected(t_shell *shell)
{
	ft_update_str(shell);
	shell->c = shell->old_temp->mini_argv[shell->i];
	shell->i++;
	shell->start = shell->i;
	while (shell->old_temp->mini_argv[shell->i]
		&& shell->old_temp->mini_argv[shell->i] != shell->c)
	{
		shell->len++;
		shell->i++;
	}
	ft_update_str(shell);
	if (shell->old_temp->mini_argv[shell->i] == shell->c)
		shell->i++;
	else
		ft_putstr_fd("You forgot to close quote. But that is fine,\
 I forgive you. I closed it for you!\n", 1);
	shell->start = shell->i;
}

void	ft_check_args(t_shell *shell)
{
	shell->i = 0;
	shell->start = 0;
	shell->len = 0;
	shell->t_sjoin = ft_strdup("");
	if (!shell->t_sjoin)
		ft_malloc_group(shell, shell->group->group, shell->group->fd_str,
			shell->group);
	while (shell->old_temp->mini_argv[shell->i])
	{
		if (shell->old_temp->mini_argv[shell->i] == '"'
			|| shell->old_temp->mini_argv[shell->i] == '\'')
			ft_quote_detected(shell);
		else if (shell->old_temp->mini_argv[shell->i])
		{
			shell->len++;
			shell->i++;
		}
	}
	ft_update_str(shell);
	shell->remove = shell->old_temp->mini_argv;
	shell->old_temp->mini_argv = shell->t_sjoin;
	free(shell->remove);
	shell->remove = NULL;
}

void	ft_create_group(t_shell *shell)
{
	if (shell->old_temp->num != REDIR)
	{
		ft_check_args(shell);
		shell->group->group[shell->m] = shell->old_temp->mini_argv;
		shell->group->num = COMMAND;
		shell->m++;
	}
	else
	{
		ft_check_args(shell);
		shell->group->fd_str[shell->n] = shell->old_temp->mini_argv;
		shell->n++;
		if (shell->old_temp->next && shell->old_temp->next->num != PIPE)
		{
			shell->old_temp = shell->old_temp->next;
			ft_check_args(shell);
			shell->group->fd_str[shell->n] = shell->old_temp->mini_argv;
			if (shell->old_temp->quote_found == 1)
				shell->group->quote_found = 1;
			shell->n++;
		}
	}
}

t_group_args	*ft_lstnew_group(t_shell *shell)
{
	shell->m = 0;
	shell->n = 0;
	shell->group = (t_group_args *)malloc(sizeof(t_group_args));
	if (!shell->group)
		ft_exit(shell, "\nMalloc failed\n\n");
	shell->group->group = (char **)malloc((shell->cmd + 1) * sizeof(char *));
	if (!shell->group->group)
		ft_malloc_group(shell, NULL, NULL, shell->group);
	shell->group->fd_str = (char **)malloc((shell->fd + 1) * sizeof(char *));
	if (!shell->group->fd_str)
		ft_malloc_group(shell, shell->group->group, NULL, shell->group);
	shell->group->quote_found = 0;
	while (shell->old_temp && (shell->old_temp->num == COMMAND
			|| shell->old_temp->num == REDIR))
	{
		ft_create_group(shell);
		shell->old_temp = shell->old_temp->next;
	}
	shell->group->group[shell->m] = NULL;
	shell->group->fd_str[shell->n] = NULL;
	shell->group->next = NULL;
	shell->group->prev = NULL;
	return (shell->group);
}
