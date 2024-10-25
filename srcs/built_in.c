/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:44:31 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 18:44:38 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static bool	ft_handle_builtins2(t_shell *shell, t_group_args *temp)
{
	if ((!ft_strncmp("cd", temp->group[0], 2)
			&& ft_strlen(temp->group[0]) == 2))
		return (ft_cd(shell, temp->group), true);
	else if ((!ft_strncmp("pwd", temp->group[0], 3)
			&& ft_strlen(temp->group[0]) == 3))
		return (ft_pwd(shell), true);
	else if ((!ft_strncmp(".\0", temp->group[0], 2))
		|| (!ft_strncmp("..\0", temp->group[0], 3)))
		return (ft_handle_error(shell, temp->group), true);
	else if (ft_is_directory(temp->group[0]) == 1)
	{
		ft_putstr_fd(temp->group[0], 2);
		ft_putstr_fd(": Is a directory\n", 2);
		shell->exit_code = 126;
		return (true);
	}
	return (false);
}

bool	ft_handle_builtins(t_shell *shell, t_group_args *temp)
{
	if ((!ft_strncmp("exit", temp->group[0], 4)
			&& ft_strlen(temp->group[0]) == 4))
		return (ft_exit_cmd(shell, temp->group), true);
	else if ((!ft_strncmp("env", temp->group[0], 3)
			&& ft_strlen(temp->group[0]) == 3))
		return (ft_env(shell, temp->group), true);
	else if ((!ft_strncmp("export", temp->group[0], 6)
			&& ft_strlen(temp->group[0]) == 6))
		return (ft_export(shell, temp->group), true);
	else if ((!ft_strncmp("unset", temp->group[0], 5)
			&& ft_strlen(temp->group[0]) == 5))
		return (ft_unset(shell, temp->group), true);
	else if ((!ft_strncmp("echo", temp->group[0], 4)
			&& ft_strlen(temp->group[0]) == 4))
		return (ft_echo(shell, temp->group), true);
	else
		if (ft_handle_builtins2(shell, temp) == true)
			return (true);
	return (false);
}

bool	ft_is_builtin(t_shell *shell)
{
	if (!ft_strncmp("exit\n", shell->group_list->group[0], 5))
		return (true);
	else if (!ft_strncmp("env\0", shell->group_list->group[0], 4))
		return (true);
	else if (!ft_strncmp("export\0", shell->group_list->group[0], 7))
		return (true);
	else if (!ft_strncmp("unset\0", shell->group_list->group[0], 6))
		return (true);
	else if (!ft_strncmp("echo\0", shell->group_list->group[0], 5))
		return (true);
	else if (!ft_strncmp("cd\0", shell->group_list->group[0], 3))
		return (true);
	else if (!ft_strncmp("pwd\0", shell->group_list->group[0], 4))
		return (true);
	else if (!ft_strncmp(".\0", shell->group_list->group[0], 2)
		|| (!ft_strncmp("..\0", shell->group_list->group[0], 3)))
		return (true);
	else if (ft_is_directory(shell->group_list->group[0]) == 1)
	{
		ft_putstr_fd(shell->group_list->group[0], 2);
		ft_putstr_fd(": Is a directory\n", 2);
		shell->exit_code = 126;
		return (true);
	}
	return (false);
}

int	ft_check_if_wait_for_child(t_shell *shell)
{
	t_group_args	*temp;

	temp = shell->group_list;
	while (temp && temp->next)
	{
		if (temp->num == PIPE)
			shell->is_pipe = 1;
		temp = temp->next;
	}
	if (shell->group_list != NULL && shell->group_list->group[0]
		&& shell->group_list->next == NULL
		&& ft_is_builtin(shell) == true && shell->is_pipe == 0)
		return (1);
	shell->is_pipe = 0;
	return (0);
}

void	ft_wait_and_exit_status(t_shell *shell, t_group_args *temp)
{
	int	status;

	if (waitpid(temp->pid, &status, 0) > 0)
	{
		if (temp && temp->next == NULL)
		{
			if (WIFEXITED(status))
				shell->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->exit_code = WTERMSIG(status) + 128;
		}
	}
}
