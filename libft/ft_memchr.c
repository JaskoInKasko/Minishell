/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 22:23:14 by iguliyev          #+#    #+#             */
/*   Updated: 2023/09/13 22:23:18 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	while (n--)
	{
		if (*(unsigned char *)s == (unsigned char)c)
			return ((void *)s);
		s++;
	}
	return (0);
}
/*#include <stdio.h>

int main() {
    const char *str = "Hello, world!";
    char search_char = 'e';
    size_t n = strlen(str);

    void *result = ft_memchr(str, search_char, n);

    printf( "%s\n", (char *)result);

    return 0;
}*/
