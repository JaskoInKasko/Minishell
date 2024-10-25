/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:48:56 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 18:48:58 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_remove_env(t_shell *shell)
{
	if (!ft_strncmp(shell->temp_env_list->env, "_=", 2))
	{
		shell->temp_env_list = shell->temp_env_list->next;
		return ;
	}
	shell->remove_env_list = shell->temp_env_list;
	if (shell->temp_env_list->prev)
		shell->temp_env_list->prev->next = shell->temp_env_list->next;
	if (shell->temp_env_list->next)
		shell->temp_env_list->next->prev = shell->temp_env_list->prev;
	if (shell->temp_env_list->prev == NULL && shell->env_list->next)
	{
		shell->env_list = shell->env_list->next;
		shell->env_list->prev = NULL;
	}
	if (shell->temp_env_list->next == NULL && shell->temp_env_list->prev)
		shell->temp_env_list->prev->next = NULL;
	shell->temp_env_list = shell->temp_env_list->next;
	free(shell->remove_env_list->env);
	free(shell->remove_env_list->exp);
	free(shell->remove_env_list);
	shell->remove_env_list = NULL;
}

void	ft_add_env_if_exist(t_shell *shell, char *str)
{
	t_env	*node;

	shell->env_len = 0;
	shell->env_check = 0;
	shell->temp_env_list = shell->env_list;
	while (shell->temp_env_list)
	{
		while (str[shell->env_len] != '=')
			shell->env_len++;
		if (!ft_strncmp(shell->temp_env_list->env, str, shell->env_len)
			&& shell->temp_env_list->env[shell->env_len] == '=')
		{
			ft_remove_env(shell);
			shell->env_check = 1;
		}
		else
			shell->temp_env_list = shell->temp_env_list->next;
	}
	if (shell->env_check == 1)
	{
		node = ft_lstnew_env(shell, str);
		ft_lstadd_back_modified(&shell->env_list, node);
		ft_update_env(shell);
		ft_update_path(shell);
	}
}

void	ft_add_env(t_shell *shell, char *str)
{
	t_env	*node;
	int		len;

	len = 0;
	shell->temp_env_list = shell->env_list;
	while (shell->temp_env_list)
	{
		while (str[len] != '=')
			len++;
		if (!ft_strncmp(shell->temp_env_list->env, str, len)
			&& shell->temp_env_list->env[len] == '=')
			ft_remove_env(shell);
		else
			shell->temp_env_list = shell->temp_env_list->next;
	}
	node = ft_lstnew_env(shell, str);
	ft_lstadd_back_modified(&shell->env_list, node);
	ft_update_env(shell);
	ft_update_path(shell);
}

bool	ft_update_env(t_shell *shell)
{
	t_env	*temp;
	int		len;
	int		i;

	len = 0;
	i = 0;
	temp = shell->env_list;
	while (temp)
	{
		len++;
		temp = temp->next;
	}
	ft_free_env(shell);
	shell->env = (char **)malloc((len + 1) * sizeof(char *));
	ft_update_env_malloc(shell);
	temp = shell->env_list;
	while (temp)
	{
		shell->env[i] = ft_strdup(temp->env);
		ft_malloc_check(shell, shell->env[i], NULL, NULL);
		i++;
		temp = temp->next;
	}
	shell->env[i] = NULL;
	return (true);
}

bool	ft_update_path(t_shell *shell)
{
	int	i;

	i = 0;
	free(shell->path);
	shell->path = NULL;
	shell->path = ft_strdup("");
	ft_malloc_check(shell, shell->path, NULL, NULL);
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], "PATH=", 5))
		{
			shell->remove = shell->path;
			shell->path = ft_substr(shell->env[i],
					5, ft_strlen(shell->env[i]) - 5);
			ft_malloc_check(shell, shell->path, shell->remove, NULL);
			free(shell->remove);
			shell->remove = NULL;
		}
		i++;
	}
	ft_free_path_list(shell);
	shell->path_list = ft_split(shell->path, ':');
	if (!shell->path_list)
		ft_exit(shell, "\nError: Malloc failed\n\n");
	return (true);
}
