/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:54:35 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 18:54:36 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_update_cm_buf(t_shell *shell)
{
	if (shell->len != 0)
	{
		shell->temp_substr = ft_substr(shell->cm_buf, shell->start, shell->len);
		ft_malloc_check(shell, shell->temp_substr, shell->temp_cm_buf, NULL);
		shell->remove = shell->temp_cm_buf;
		shell->temp_cm_buf = ft_strjoin(shell->temp_cm_buf, shell->temp_substr);
		ft_malloc_check(shell, shell->temp_cm_buf, shell->temp_substr,
			shell->remove);
		free(shell->temp_substr);
		shell->temp_substr = NULL;
		free(shell->remove);
		shell->remove = NULL;
		shell->len = 0;
	}
}

pid_t	ft_getpid(void)
{
	DIR				*dir;
	struct dirent	*file;
	pid_t			pid;

	dir = opendir("/proc/self/task");
	if (dir == NULL)
		return (0);
	pid = 0;
	file = readdir(dir);
	while (file != NULL && pid == 0)
	{
		pid = ft_atoi(file->d_name);
		file = readdir(dir);
	}
	closedir(dir);
	return (pid);
}
