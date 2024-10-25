/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 22:25:47 by iguliyev          #+#    #+#             */
/*   Updated: 2023/09/13 22:25:49 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	long	i;

	i = 0;
	if (s == NULL)
		return ((void) NULL);
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
/*#include<stdio.h>

int main ()
{
    char a[] = "abc";
    ft_putstr_fd(a, 1);
    return (0);
}*/
