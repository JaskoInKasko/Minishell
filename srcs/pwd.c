/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:53:28 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 18:53:30 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_update_pwd(t_shell *shell)
{
	char	cwd[1024];
	char	*pwd;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return ;
	}
	pwd = ft_strjoin("PWD=", cwd);
	ft_malloc_check(shell, pwd, NULL, NULL);
	ft_add_env(shell, pwd);
	free(pwd);
}

void	ft_update_oldpwd_if_exist(t_shell *shell)
{
	char	cwd[1024];
	char	*oldpwd;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return ;
	}
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	ft_malloc_check(shell, oldpwd, NULL, NULL);
	ft_add_env_if_exist(shell, oldpwd);
	free(oldpwd);
}

void	ft_update_oldpwd(t_shell *shell)
{
	char	cwd[1024];
	char	*oldpwd;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return ;
	}
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	ft_malloc_check(shell, oldpwd, NULL, NULL);
	ft_add_env(shell, oldpwd);
	free(oldpwd);
}

void	ft_pwd(t_shell *shell)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return ;
	}
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
	shell->exit_code = 0;
}

// void	ft_pwd(t_shell *shell)
// {
// 	char	cwd[1024];
//     char    *str;

// 	if (getcwd(cwd, sizeof(cwd)) == NULL)
//     {
//         str = ft_find_in_env(shell, "OLDPWD=", 7);
// 		if(!str)
// 		{
// 			perror("getcwd");
// 			return ;
// 		}
//         if (chdir(str) != 0)
//         {
//             perror("cd");
//             shell->exit_code = 1;
//             return ;
//         }
//         ft_putstr_fd(str, 1);
//         ft_putstr_fd("\n", 1);
//         free(str);
//         shell->exit_code = 0;
//         return ;
//     }
// 	ft_putstr_fd(cwd, 1);
// 	ft_putstr_fd("\n", 1);
// 	shell->exit_code = 0;
// }
