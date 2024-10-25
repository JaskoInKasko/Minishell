/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:52:58 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 18:53:00 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_minishell_loop(t_shell *shell)
{
	while (1)
	{
		ft_config_signals(shell);
		shell->cm_buf = readline("minishell$ ");
		if (shell->cm_buf)
		{
			if (ft_strlen(shell->cm_buf) > 0)
				add_history(shell->cm_buf);
			if (shell->cm_buf[0])
			{
				if (ft_init_argv(shell) == true)
				{
					ft_case(shell);
					ft_wait_for_children(shell);
				}
				ft_free_loop(shell);
				g_exit_code = 0;
			}
			free(shell->cm_buf);
		}
		else
			ft_exit(shell, "exit\n");
	}
}

int	main(int a, char **b, char **e)
{
	t_shell	shell;

	if (a != 1)
		return (ft_putstr_fd("\nError:\
		wrong number of argumeents !!!\n\n", 2), -1);
	ft_init_variables(&shell, b, e);
	ft_minishell_loop(&shell);
	return (0);
}
