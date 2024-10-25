/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:46:34 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 18:46:39 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	ft_execute_command(t_shell *shell, t_group_args *temp);
static void	ft_execute_absolute_path(t_shell *shell, t_group_args *temp);
static void	ft_execute_relative_path(t_shell *shell, t_group_args *temp, int i);
static void	ft_execute_current_path(t_shell *shell, t_group_args *temp);

void	ft_childs(t_shell *shell, t_group_args *temp)
{
	int	i;

	i = -1;
	if (ft_is_absolute_path(temp) == 0)
		ft_execute_absolute_path(shell, temp);
	else if (shell->path_list[0])
		ft_execute_relative_path(shell, temp, i);
	else
		ft_execute_current_path(shell, temp);
}

static void	ft_execute_command(t_shell *shell, t_group_args *temp)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
	if ((execve(shell->execve_path, temp->group, shell->env)) == -1)
	{
		free(shell->execve_path);
		shell->execve_path = NULL;
		ft_exit(shell, NULL);
	}
	free(shell->execve_path);
	ft_exit(shell, NULL);
}

static void	ft_execute_absolute_path(t_shell *shell, t_group_args *temp)
{
	shell->execve_path = ft_strdup(temp->group[0]);
	if (!shell->execve_path)
		ft_exit(shell, "ft_strdup() failed in child\n");
	if (!access(shell->execve_path, F_OK))
	{
		if (!access(shell->execve_path, X_OK))
			ft_execute_command(shell, temp);
		else
			ft_handle_execution_errors(shell, temp);
	}
	else
	{
		free(shell->execve_path);
		perror(temp->group[0]);
		shell->exit_code = 127;
		ft_exit(shell, NULL);
	}
	free(shell->execve_path);
}

static void	ft_execute_relative_path(t_shell *shell, t_group_args *temp, int i)
{
	while (shell->path_list[++i])
	{
		shell->remove = ft_strjoin(shell->path_list[i], "/");
		if (!shell->remove)
			ft_exit(shell, "ft_strjoin() failed in child\n");
		shell->execve_path = ft_strjoin(shell->remove, temp->group[0]);
		if (!shell->execve_path)
		{
			free(shell->remove);
			ft_exit(shell, NULL);
		}
		free(shell->remove);
		if (!access(shell->execve_path, F_OK) && ft_strlen(temp->group[0]))
		{
			if (!access(shell->execve_path, X_OK))
				ft_execute_command(shell, temp);
			else
				ft_handle_execution_errors(shell, temp);
		}
		free(shell->execve_path);
	}
	ft_print_cmd_not_found(shell, temp);
	ft_exit(shell, NULL);
}

static void	ft_execute_current_path(t_shell *shell, t_group_args *temp)
{
	shell->execve_path = ft_strjoin("./", temp->group[0]);
	if (!shell->execve_path)
		ft_exit(shell, "ft_strdup() failed in child\n");
	if (!access(shell->execve_path, F_OK) && ft_strlen(temp->group[0]) != 0)
	{
		if (!access(shell->execve_path, X_OK))
			ft_execute_command(shell, temp);
		else
			ft_handle_execution_errors(shell, temp);
	}
	else
	{
		free(shell->execve_path);
		perror(temp->group[0]);
		shell->exit_code = 127;
		ft_exit(shell, NULL);
	}
}
