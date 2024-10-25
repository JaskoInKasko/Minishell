/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 22:28:37 by iguliyev          #+#    #+#             */
/*   Updated: 2023/09/26 17:55:12 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*p;
	char	uc;

	p = (char *)s;
	uc = (char)c;
	i = 0;
	while (p[i])
		i++;
	while (i >= 0)
	{
		if (p[i] == uc)
			return (p + i);
		i--;
	}
	return (NULL);
}

/*#include <stdio.h>
int main ()
{
    char a[] = "asssbcdd";
    char b = 'b';
    printf("%s", ft_strrchr(a, b));
}*/
