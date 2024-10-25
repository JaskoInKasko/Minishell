/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 23:39:54 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 19:17:28 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_lstnew_argv_sign(t_shell *shell, t_mini_argv *new, char *argv_str)
{
	if (argv_str[0] == '|')
		new->num = PIPE;
	else if (argv_str[0] == ';' || argv_str[0] == '\n')
		new->num = SKIP;
	else if (argv_str[0] == '>' || argv_str[0] == '<')
	{
		new->num = REDIR;
		shell->quote_found = 1;
	}
	else
		new->num = COMMAND;
}

void	ft_lstnew_argv_malloc(t_shell *shell, char *argv_str)
{
	if (argv_str)
	{
		free(argv_str);
		argv_str = NULL;
	}
	shell->exit_code = EXIT_FAILURE;
	ft_exit(shell, "\nError: Malloc failed\n\n");
}

t_mini_argv	*ft_lstnew_argv(t_shell *shell, char *argv_str)
{
	t_mini_argv	*new;

	new = (t_mini_argv *)malloc(sizeof(t_mini_argv));
	if (!new)
		ft_lstnew_argv_malloc(shell, argv_str);
	new->mini_argv = argv_str;
	if (shell->quote_found == 1)
	{
		if (ft_strchr(argv_str, '"') != NULL
			|| ft_strchr(argv_str, '\'') != NULL)
			new->quote_found = 1;
		else
		{
			new->quote_found = 0;
			shell->quote_found = 0;
		}
	}
	else
		new->quote_found = 0;
	ft_lstnew_argv_sign(shell, new, argv_str);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_mini_argv	*ft_lstlast_argv(t_mini_argv *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_argv(t_mini_argv **lst, t_mini_argv *node)
{
	t_mini_argv	*tmp;

	tmp = ft_lstlast_argv(*lst);
	if (!tmp)
		*lst = node;
	else
	{
		tmp->next = node;
		node->prev = tmp;
	}
}
