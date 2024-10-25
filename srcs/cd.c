/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:46:17 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 18:46:20 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*ft_find_in_env(t_shell *shell, char *var, int len)
{
	t_env	*temp;
	char	*remove;

	remove = NULL;
	temp = shell->env_list;
	while (temp)
	{
		if (!ft_strncmp(temp->env, var, len))
		{
			remove = ft_substr(temp->env, len, ft_strlen(temp->env) - len);
			ft_malloc_check(shell, remove, NULL, NULL);
			break ;
		}
		temp = temp->next;
	}
	if (!remove)
	{
		ft_putstr_fd("Warning: variable not set\n", 2);
		shell->exit_code = 1;
		return (NULL);
	}
	return (remove);
}

void	ft_chdir(t_shell *shell, char *dir)
{
	ft_update_oldpwd(shell);
	if (chdir(dir) != 0)
	{
		perror("cd");
		shell->exit_code = 1;
		return ;
	}
	ft_update_pwd(shell);
	shell->exit_code = 0;
}

void	ft_cd_change(t_shell *shell, char *var)
{
	char	*remove;

	remove = ft_find_in_env(shell, var, ft_strlen(var));
	if (remove == NULL)
		return ;
	ft_chdir(shell, remove);
	free(remove);
	remove = NULL;
}

bool	ft_cd_minus(t_shell *shell, char **group)
{
	if (!ft_strncmp("--\0", group[1], 3))
	{
		if (!group[2])
			ft_cd_change(shell, "HOME=");
		else if (!group[3])
			ft_chdir(shell, group[2]);
		else
			return (false);
		return (true);
	}
	if (!ft_strncmp("-\0", group[1], 2))
	{
		if (!group[2])
		{
			ft_cd_change(shell, "OLDPWD=");
			if (shell->exit_code == 0)
				ft_pwd(shell);
			return (true);
		}
	}
	return (false);
}

void	ft_cd(t_shell *shell, char **group)
{
	if (group[1] && ft_strncmp("-\0", group[1], 2))
	{
		ft_update_oldpwd_if_exist(shell);
	}
	if (!group[1])
	{
		ft_cd_change(shell, "HOME=");
		return ;
	}
	if (ft_cd_minus(shell, group) == true)
		return ;
	if (group[2])
	{
		ft_putstr_fd("Warning: too many arguments\n", 2);
		shell->exit_code = 1;
		return ;
	}
	ft_chdir(shell, group[1]);
}
