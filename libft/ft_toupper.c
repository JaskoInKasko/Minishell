/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 22:29:27 by iguliyev          #+#    #+#             */
/*   Updated: 2023/09/13 22:29:29 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c = c - 'a' + 'A';
	return (c);
}
/*#include<stdio.h>
#include <ctype.h>

int main()
{
    char ch = 's';

    printf("%c\n", toupper(ch));
    printf("%c\n", ft_toupper(ch));
}*/
