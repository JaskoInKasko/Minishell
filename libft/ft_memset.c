/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 22:24:41 by iguliyev          #+#    #+#             */
/*   Updated: 2023/09/13 22:24:43 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	uc;
	size_t			i;

	i = 0;
	p = s;
	uc = (unsigned char)c;
	while (n > i)
	{
		p[i] = uc;
		i++;
	}
	return (s);
}
/*#include<stdio.h>
int main ()
{
    char a [30];
    ft_memset(a, 'a', 20);
    printf("%s", a);
    return (0);
}*/
