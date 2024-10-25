/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:51:41 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 18:51:43 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_make_list(t_shell *shell, char *str)
{
	t_mini_argv	*node;

	if (str[0] != '\0')
	{
		node = ft_lstnew_argv(shell, str);
		ft_lstadd_back_argv(&shell->argv_list, node);
	}
	else
	{
		free(str);
		str = NULL;
	}
}

void	ft_find_redirections(t_shell *shell)
{
	char	*temp_substr;

	while (shell->cm_buf[shell->i]
		&& ft_strchr("<>|;\n", shell->cm_buf[shell->i]) != NULL)
	{
		shell->c = shell->cm_buf[shell->i];
		if (shell->cm_buf[shell->i] != ';'
			&& shell->cm_buf[shell->i + 1] == shell->c)
		{
			temp_substr = ft_substr(shell->cm_buf, shell->i, 2);
			ft_malloc_check(shell, temp_substr, NULL, NULL);
			shell->i++;
		}
		else
		{
			temp_substr = ft_substr(shell->cm_buf, shell->i, 1);
			ft_malloc_check(shell, temp_substr, NULL, NULL);
		}
		ft_make_list(shell, temp_substr);
		shell->i++;
	}
}

void	ft_find_command_loop(t_shell *shell)
{
	if (shell->cm_buf[shell->i] == '"' || shell->cm_buf[shell->i] == '\'')
	{
		shell->c = shell->cm_buf[shell->i];
		shell->i++;
		shell->len++;
		while (shell->cm_buf[shell->i]
			&& shell->cm_buf[shell->i] != shell->c)
		{
			shell->len++;
			shell->i++;
		}
	}
	if (shell->cm_buf[shell->i])
	{
		shell->len++;
		shell->i++;
	}
}

void	ft_find_command(t_shell *shell)
{
	char	*temp_substr;

	shell->start = shell->i;
	shell->len = 0;
	while (shell->cm_buf[shell->i]
		&& ft_strchr(" \t<>|;\n", shell->cm_buf[shell->i]) == NULL)
	{
		ft_find_command_loop(shell);
	}
	temp_substr = ft_substr(shell->cm_buf, shell->start, shell->len);
	ft_malloc_check(shell, temp_substr, NULL, NULL);
	ft_make_list(shell, temp_substr);
}

bool	ft_init_argv(t_shell *shell)
{
	if (g_exit_code != 0)
		shell->exit_code = g_exit_code;
	if (ft_strchr(shell->cm_buf, '$') || ft_strchr(shell->cm_buf, '~'))
		ft_dollar_check(shell);
	shell->i = 0;
	shell->start = 0;
	shell->len = 0;
	while (shell->cm_buf[shell->i])
	{
		while (shell->cm_buf[shell->i] == ' '
			|| shell->cm_buf[shell->i] == '\t')
			shell->i++;
		if (ft_strchr("<>|;\n", shell->cm_buf[shell->i]) == NULL)
			ft_find_command(shell);
		else
			ft_find_redirections(shell);
	}
	if (ft_check_syntax(shell) == false)
		return (false);
	ft_make_groups(shell);
	ft_init_pipe_values(shell);
	return (true);
}
