/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsakanov <jsakanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:05:17 by jsakanov          #+#    #+#             */
/*   Updated: 2023/10/13 13:05:20 by jsakanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../headers/minishell.h"

char	*ft_strjoin_jasmin(char *s1, char *s2, int len)
{
	size_t	i;
	size_t	j;
	char	*s3;

	if (s1 == NULL || s2 == NULL)
		return (free(s1), NULL);
	len = (ft_strlen_jasmin(s1) + ft_strlen_jasmin(s2));
	i = 0;
	j = 0;
	s3 = (char *)malloc((len + 1) * sizeof(char));
	if (s3 == NULL)
	{
		free(s1);
		return (NULL);
	}
	while (s1[i] != '\0')
		s3[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		s3[j++] = s2[i++];
	s3[j] = '\0';
	free(s1);
	return (s3);
}

size_t	ft_strlen_jasmin(const char *str)
{
	int	c;

	c = 0;
	if (str == NULL)
		return (0);
	while (str[c] != '\0')
		c++;
	return (c);
}

char	*ft_strchr_jasmin(char *s, int c)
{
	if (s == NULL)
		return (0);
	while (*s != '\0')
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (0);
}

char	*ft_strdup_jasmin(const char *s)
{
	size_t	i;
	size_t	size;
	char	*s1;

	i = 0;
	if (s == NULL)
		return (NULL);
	size = ft_strlen_jasmin(s);
	s1 = (char *)malloc((size + 1) * sizeof(char));
	if (s1 == NULL)
		return (NULL);
	while (i < size)
	{
		s1[i] = s[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
