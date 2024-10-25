/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:49:06 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 18:49:07 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include <stdlib.h>

void	ft_free_env(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell->env)
	{
		while (shell->env[i])
		{
			free(shell->env[i]);
			shell->env[i] = NULL;
			i++;
		}
		free(shell->env);
		shell->env = NULL;
	}
}

void	ft_free_path_list(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell->path_list)
	{
		while (shell->path_list[i])
		{
			free(shell->path_list[i]);
			shell->path_list[i] = NULL;
			i++;
		}
		free(shell->path_list);
		shell->path_list = NULL;
	}
}

void	ft_free_env_list(t_shell *shell)
{
	t_env	*temp_env;

	temp_env = shell->env_list;
	while (shell->env_list)
	{
		temp_env = shell->env_list;
		shell->env_list = shell->env_list->next;
		if (temp_env->env)
		{
			free(temp_env->env);
			temp_env->env = NULL;
		}
		if (temp_env->exp)
		{
			free(temp_env->exp);
			temp_env->exp = NULL;
		}
		if (temp_env)
		{
			free(temp_env);
			temp_env = NULL;
		}
	}
	shell->env_list = NULL;
}

void	ft_exit(t_shell *shell, char *msg)
{
	ft_free_env_list(shell);
	ft_free_path_list(shell);
	ft_free_env(shell);
	ft_free_loop(shell);
	if (shell->path)
		free(shell->path);
	if (shell->pwd)
		free(shell->pwd);
	if (shell->old_pwd)
		free(shell->old_pwd);
	if (shell->cm_buf)
		free(shell->cm_buf);
	if (shell->home)
		free(shell->home);
	if (shell->hdoc_line)
	{
		free(shell->hdoc_line);
	}
	rl_clear_history();
	if (msg)
		ft_putstr_fd(msg, 2);
	exit(shell->exit_code);
}
