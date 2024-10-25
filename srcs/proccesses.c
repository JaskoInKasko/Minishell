/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccesses.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:53:13 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 18:53:14 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	ft_start_process(t_shell *shell, t_group_args *temp);
static void	ft_handle_single_process(t_shell *shell, t_group_args *temp);
static void	ft_handle_multiple_processes(t_shell *shell, t_group_args *temp);

static void	ft_start_process(t_shell *shell, t_group_args *temp)
{
	if (shell->lst_size == 1)
		ft_handle_single_process(shell, temp);
	else
		ft_handle_multiple_processes(shell, temp);
}

static void	ft_handle_single_process(t_shell *shell, t_group_args *temp)
{
	if (ft_handle_builtins(shell, temp) == false)
	{
		if (temp->pid != 0)
		{
			ft_config_child(shell);
			temp->pid = fork();
			if (temp->pid == -1)
			{
				perror("temp->pid");
				return ;
			}
		}
		if (temp->pid == 0)
			ft_childs(shell, temp);
	}
}

static void	ft_handle_multiple_processes(t_shell *shell, t_group_args *temp)
{
	if (temp->pid != 0)
	{
		ft_config_child(shell);
		temp->pid = fork();
		if (temp->pid == -1)
		{
			perror("temp->pid");
			return ;
		}
	}
	if (temp->pid == 0)
	{
		ft_handle_both_pipes(shell, temp);
		ft_close_prev_pipes(temp);
		if (ft_handle_builtins(shell, temp) == true)
			ft_exit(shell, NULL);
		else
			ft_childs(shell, temp);
	}
}

void	ft_increment_child_count_and_start_process(t_shell *shell, \
	t_group_args *temp)
{
	if (temp->group[0] && temp->num != PIPE)
	{
		shell->count_args++;
		shell->count_childs++;
		ft_start_process(shell, temp);
	}
}
