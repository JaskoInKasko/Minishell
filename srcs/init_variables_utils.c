/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_variables_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:52:07 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 18:52:08 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_malloc_free(char *ptr, char *check1, char *check2)
{
	if (!ptr)
	{
		if (check1)
		{
			free(check1);
			check1 = NULL;
		}
		if (check2)
		{
			free(check2);
			check2 = NULL;
		}
	}
}

void	ft_malloc_group(t_shell *shell, char **check1, char **check2,
		t_group_args *check3)
{
	if (check1)
	{
		free(check1);
		check1 = NULL;
	}
	if (check2)
	{
		free(check2);
		check2 = NULL;
	}
	if (check3)
	{
		free(check3);
		check3 = NULL;
	}
	shell->exit_code = EXIT_FAILURE;
	ft_exit(shell, "\nError: Malloc failed\n\n");
}

void	ft_malloc_env(t_shell *shell, char *check1, char *check2, t_env *check3)
{
	if (check1)
	{
		free(check1);
		check1 = NULL;
	}
	if (check2)
	{
		free(check2);
		check2 = NULL;
	}
	if (check3)
	{
		free(check3);
		check3 = NULL;
	}
	shell->exit_code = EXIT_FAILURE;
	ft_exit(shell, "\nError: Malloc failed\n\n");
}

void	ft_malloc_check(t_shell *shell, char *ptr, char *check1, char *check2)
{
	if (!ptr)
	{
		if (check1)
		{
			free(check1);
			check1 = NULL;
		}
		if (check2)
		{
			free(check2);
			check2 = NULL;
		}
		shell->exit_code = EXIT_FAILURE;
		ft_exit(shell, "\nError: Malloc failed\n\n");
	}
}

void	ft_update_env_malloc(t_shell *shell)
{
	if (!shell->env)
	{
		shell->exit_code = EXIT_FAILURE;
		ft_exit(shell, "\nMalloc Failed\n\n");
	}
}
