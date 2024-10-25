/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 22:26:14 by iguliyev          #+#    #+#             */
/*   Updated: 2023/09/26 17:56:00 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*p1;
	char	p2;

	i = 0;
	p1 = (char *)s;
	p2 = (char)c;
	while (s[i])
	{
		if (s[i] == p2)
			return (p1);
		i++;
		p1++;
	}
	if (s[i] == p2)
		return (p1);
	return (NULL);
}
