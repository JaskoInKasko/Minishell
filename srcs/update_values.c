/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_values.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:54:29 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 18:54:30 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	if (split)
	{
		while (split[i])
		{
			free(split[i]);
			split[i] = NULL;
			i++;
		}
		free(split);
		split = NULL;
	}
}

void	ft_local_free(t_shell *shell)
{
	ft_free_split(shell->split);
	free(shell->remove3);
	shell->remove3 = NULL;
	ft_malloc_check(shell, shell->remove2, shell->temp_cm_buf,
		shell->temp_substr);
}

void	ft_add_quote(t_shell *shell)
{
	shell->remove3 = shell->remove2;
	shell->remove2 = ft_strjoin(shell->remove2, "'");
	if (!shell->remove2)
	{
		ft_free_split(shell->split);
		free(shell->remove3);
		shell->remove3 = NULL;
		ft_malloc_check(shell, shell->remove2, shell->temp_cm_buf,
			shell->temp_substr);
	}
	free(shell->remove3);
	shell->remove3 = NULL;
}

void	ft_init_split(t_shell *shell)
{
	shell->split = ft_split_modified(shell->remove2, ' ', '\t');
	if (!shell->split)
	{
		free(shell->remove2);
		shell->remove2 = NULL;
		ft_malloc_check(shell, shell->remove2, shell->temp_cm_buf,
			shell->temp_substr);
	}
	free(shell->remove2);
	shell->remove2 = NULL;
	shell->remove2 = ft_strdup("");
	if (!shell->remove2)
	{
		ft_free_split(shell->split);
		ft_malloc_check(shell, shell->remove2, shell->temp_cm_buf,
			shell->temp_substr);
	}
}

void	ft_update_env_value(t_shell *shell)
{
	int	i;

	i = -1;
	ft_init_split(shell);
	while (shell->split[++i])
	{
		ft_add_quote(shell);
		shell->remove3 = shell->remove2;
		shell->remove2 = ft_strjoin(shell->remove2, shell->split[i]);
		if (!shell->remove2)
			ft_local_free(shell);
		free(shell->remove3);
		shell->remove3 = NULL;
		ft_add_quote(shell);
		if (shell->split[i + 1])
		{
			shell->remove3 = shell->remove2;
			shell->remove2 = ft_strjoin(shell->remove2, " ");
			if (!shell->remove2)
				ft_local_free(shell);
			free(shell->remove3);
			shell->remove3 = NULL;
		}
	}
	ft_free_split(shell->split);
}
