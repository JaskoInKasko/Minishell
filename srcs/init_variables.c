/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_variables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:52:00 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 18:52:01 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_env_list(t_shell *shell)
{
	t_env	*node;
	int		i;

	i = 0;
	if (!shell->env[0])
	{
		node = ft_lstnew_env(shell, "");
		if (!node)
		{
			shell->exit_code = EXIT_FAILURE;
			ft_exit(shell, "\nError: Malloc failed\n\n");
		}
		ft_lstadd_back_modified(&shell->env_list, node);
	}
	while (shell->env[i])
	{
		node = ft_lstnew_env(shell, shell->env[i]);
		ft_lstadd_back_modified(&shell->env_list, node);
		i++;
	}
}

void	ft_init_link(t_shell *shell, char **link, char *env, int len)
{
	*link = ft_substr(env, len, ft_strlen(env) - len);
	ft_malloc_check(shell, *link, NULL, NULL);
}

void	ft_find_links(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], "PWD=", 4))
			ft_init_link(shell, &shell->pwd, shell->env[i], 4);
		if (!ft_strncmp(shell->env[i], "PATH=", 5))
		{
			free(shell->path);
			shell->path = NULL;
			ft_init_link(shell, &shell->path, shell->env[i], 5);
		}
		if (!ft_strncmp(shell->env[i], "OLDPWD=", 7))
			ft_init_link(shell, &shell->old_pwd, shell->env[i], 7);
		if (!ft_strncmp(shell->env[i], "HOME=", 5))
			ft_init_link(shell, &shell->home, shell->env[i], 5);
		i++;
	}
}

bool	ft_init_variables(t_shell *shell, char **argv, char **env)
{
	ft_bzero(shell, sizeof(t_shell));
	shell->argv = argv;
	shell->path = ft_strdup("");
	ft_malloc_check(shell, shell->path, NULL, NULL);
	ft_copy_env(shell, env);
	ft_env_list(shell);
	ft_find_links(shell);
	if (shell->path)
	{
		shell->path_list = ft_split(shell->path, ':');
		if (!shell->path_list)
		{
			shell->exit_code = EXIT_FAILURE;
			ft_exit(shell, "\nError: Malloc failed\n\n");
		}
	}
	return (true);
}
