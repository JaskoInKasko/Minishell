/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_found_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:48:36 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 18:48:38 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_add_space(t_shell *shell)
{
	shell->remove = shell->temp_cm_buf;
	shell->temp_cm_buf = ft_strjoin(shell->temp_cm_buf, " ");
	ft_malloc_check(shell, shell->temp_cm_buf, shell->remove,
		shell->temp_substr);
	free(shell->remove);
	shell->remove = NULL;
}
