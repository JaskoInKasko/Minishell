/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:16:34 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/31 19:16:36 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_empty_env(t_shell *shell)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return ;
	}
	shell->env[0] = ft_strjoin("PWD=", cwd);
	ft_malloc_check(shell, shell->env[0], NULL, NULL);
	shell->env[1] = ft_strdup("_=/usr/bin/env");
	ft_malloc_check(shell, shell->env[1], NULL, NULL);
	shell->env[2] = NULL;
}

void	ft_make_env(t_shell *shell, char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		shell->env[i] = ft_strdup(env[i]);
		if (!shell->env[i])
		{
			shell->exit_code = EXIT_FAILURE;
			ft_exit(shell, "\nError: Malloc failed\n\n");
		}
		i++;
	}
	if (!env[0])
	{
		ft_empty_env(shell);
		return ;
	}
	shell->env[i] = NULL;
}

void	ft_copy_env(t_shell *shell, char **env)
{
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (env[i++])
		len++;
	if (len == 0)
		len = 2;
	shell->env = (char **)malloc((len + 1) * sizeof(char *));
	if (!shell->env)
	{
		shell->exit_code = EXIT_FAILURE;
		ft_exit(shell, "\nError: Malloc failed\n\n");
	}
	ft_make_env(shell, env);
}
