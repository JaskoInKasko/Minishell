/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 23:39:54 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 19:17:11 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*ft_lstnew_exp(t_shell *shell, char *env, int i, int flag)
{
	char	*remove;

	shell->exp_j = 0;
	remove = malloc((ft_strlen(env) + 3) * sizeof(char));
	if (!remove)
		return (NULL);
	while (env[i])
	{
		remove[shell->exp_j] = env[i];
		if (env[i] == '=' && flag == 1)
		{
			flag = 0;
			shell->exp_j++;
			remove[shell->exp_j] = '"';
		}
		i++;
		shell->exp_j++;
		if (!env[i])
		{
			remove[shell->exp_j] = '"';
			shell->exp_j++;
		}
	}
	remove[shell->exp_j] = '\0';
	return (remove);
}

t_env	*ft_lstnew_env(t_shell *shell, char *env_str)
{
	t_env	*new;
	char	*remove;
	int		i;
	int		flag;

	i = 0;
	flag = 1;
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		ft_exit(shell, "\nError: Malloc failed\n\n");
	new->env = ft_strdup(env_str);
	if (!new->env)
		ft_malloc_env(shell, NULL, NULL, new);
	remove = ft_lstnew_exp(shell, new->env, i, flag);
	if (!remove)
		ft_malloc_env(shell, new->env, NULL, new);
	new->exp = ft_strjoin("declare -x ", remove);
	if (!new->exp)
		ft_malloc_env(shell, new->env, remove, new);
	free(remove);
	remove = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_env	*ft_lstlast_modified(t_env *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_modified(t_env **lst, t_env *node)
{
	t_env	*tmp;

	tmp = ft_lstlast_modified(*lst);
	if (!tmp)
		*lst = node;
	else
	{
		tmp->next = node;
		node->prev = tmp;
	}
}
