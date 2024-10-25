/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_modified.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 22:26:02 by iguliyev          #+#    #+#             */
/*   Updated: 2024/05/29 18:50:22 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static int	ft_count_word(char const *s, char c, char h)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i])
	{
		while (s[i] == c || s[i] == h)
			i++;
		if (s[i] != c && s[i] != h && s[i])
			word++;
		while (s[i] != c && s[i] != h && s[i])
			i++;
	}
	return (word);
}

static int	ft_size_word(char const *s, char c, char h, int i)
{
	int	size;

	size = 0;
	while (s[i] != c && s[i] != h && s[i])
	{
		size++;
		i++;
	}
	return (size);
}

static void	ft_free(char **strs, int j)
{
	while (j--)
		free(strs[j]);
	free(strs);
}

static char	**ft_allocate_and_split(char const *s, char c, char h, int word)
{
	char	**strs;
	int		size;
	int		j;
	int		i;

	i = 0;
	j = -1;
	strs = (char **)malloc((word + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	while (++j < word)
	{
		while (s[i] == c || s[i] == h)
			i++;
		size = ft_size_word(s, c, h, i);
		strs[j] = ft_substr(s, i, size);
		if (!strs[j])
		{
			ft_free(strs, j);
			return (NULL);
		}
		i += size;
	}
	strs[j] = NULL;
	return (strs);
}

char	**ft_split_modified(char const *s, char c, char h)
{
	int	word;

	word = ft_count_word(s, c, h);
	return (ft_allocate_and_split(s, c, h, word));
}
