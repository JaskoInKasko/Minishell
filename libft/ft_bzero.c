/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 22:18:35 by iguliyev          #+#    #+#             */
/*   Updated: 2023/09/13 22:18:46 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;
	size_t			i;

	i = 0;
	p = s;
	while (n > i)
	{
		p[i] = 0;
		i++;
	}
}
/*#include<stdio.h>
int main ()
{
    char a [30];
    ft_bzero(a, 20);
    printf("%s", a);
    return (0);
}*/
